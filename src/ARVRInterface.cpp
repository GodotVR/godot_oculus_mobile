////////////////////////////////////////////////////////////////////////////////////////////////
// Our main ARVRInterface code for our OVR GDNative module
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "ARVRInterface.h"

///////////////////////////////////////////////////////////////////////////////////////////
// our ARVR interface
godot_string godot_arvr_get_name(const void *p_data) {
	godot_string ret;

	char name[] = "OVR";
	api->godot_string_new(&ret);
	api->godot_string_parse_utf8(&ret, name);

	return ret;
}

godot_int godot_arvr_get_capabilities(const void *p_data) {
	godot_int ret;

	ret = 2; // 2 = ARVR_STEREO

	return ret;
}

godot_bool godot_arvr_get_anchor_detection_is_enabled(const void *p_data) {
	godot_bool ret;

	ret = false; // does not apply here

	return ret;
}

void godot_arvr_set_anchor_detection_is_enabled(void *p_data, bool p_enable) {
	// we ignore this, not supported in this interface!
}

godot_bool godot_arvr_is_stereo(const void *p_data) {
	godot_bool ret;

	ret = true;

	return ret;
}

godot_bool godot_arvr_is_initialized(const void *p_data) {
	godot_bool ret;
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	ret = arvr_data->ovr_is_initialized;

	return ret;
}

godot_vector3 getLocalPosition(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	godot_vector3 pos;
	if (!arvr_data->ovr_is_initialized) {
		api->godot_vector3_new(&pos, 0.0, 0.0, 0.0);
	} else {
		api->godot_vector3_new(&pos, arvr_data->headTracker.HeadPose.Pose.Position.x,
				arvr_data->headTracker.HeadPose.Pose.Position.y,
				arvr_data->headTracker.HeadPose.Pose.Position.z);
	}
	return pos;
}

/*
godot_transform getLocalRotation(void *p_data, float p_world_scale) {
  arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

  godot_transform rotMat;
  if (!arvr_data->ovr_is_initialized) {
    api->godot_transform_new_identity(&rotMat);
  } else {
    auto rot = arvr_data->headTracker.HeadPose.Pose.Orientation;
    godot_quat q;
    godot_basis basis;
    godot_vector3 origin;
    api->godot_quat_new(&q, rot.x, rot.y, rot.z, rot.w);
    api->godot_basis_new_with_euler_quat(&basis, &q);
    api->godot_vector3_operator_multiply_scalar(getLocalPosition(arvr_data), p_world_scale);
    api->godot_transform_new(&rotMat, &basis, &origin);
  }
  return rotMat;
}
*/

void applyTracking(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (!arvr_data->ovr_is_initialized) {
		return;
	}

	const double predictedDisplayTime = vrapi_GetPredictedDisplayTime(arvr_data->ovr, arvr_data->frameIndex);

	arvr_data->headTracker = vrapi_GetPredictedTracking2(arvr_data->ovr, predictedDisplayTime);
}

godot_bool godot_arvr_initialize(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (!arvr_data->ovr_is_initialized) {
		printf("OVR - initializing...\n");

		// Get some info about our JAVA environment
		JNIEnv *env = android_api->godot_android_get_env();
		arvr_data->java.ActivityObject = env->NewGlobalRef(android_api->godot_android_get_activity());
		arvr_data->java.Env = env;
		env->GetJavaVM(&arvr_data->java.Vm);

		// Working on this
		// arvr_data->Surface = android_api->godot_android_get_surface();

		// These we'll get later
		arvr_data->NativeWindow = NULL;
		arvr_data->Display = 0;
		arvr_data->Context = EGL_NO_CONTEXT;

		// We are currently in our main thread so
		// arvr_data->MainThreadTid = gettid();

		// Initializes VrApi and GearVR
		const ovrInitParms initParms = vrapi_DefaultInitParms(&arvr_data->java);
		int32_t initResult = vrapi_Initialize(&initParms);
		if (vrapi_Initialize(&initParms) != VRAPI_INITIALIZE_SUCCESS) {
			printf("Failed to initialize VrApi!");
			abort();
		}

		// init our extensions container
		OVR::OpenGLExtensions::initExtensions();

		// Get the suggested resolution to create eye texture swap chains.
		arvr_data->width = vrapi_GetSystemPropertyInt(&arvr_data->java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH);
		arvr_data->height = vrapi_GetSystemPropertyInt(&arvr_data->java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_HEIGHT);

		// Create Frame buffers for each eye
		bool success = true;
		bool useMultiview = false; // false for now...
		for (int eye = 0; eye < VRAPI_EYE_COUNT; eye++) {
			arvr_data->frameBuffer[eye] = new OVR::frameBuffer(
					useMultiview,
					GL_RGBA8,
					arvr_data->width,
					arvr_data->height,
					NUM_MULTI_SAMPLES);
		}

		arvr_data->ovr_is_initialized = true;
	}

	// and return our result
	return arvr_data->ovr_is_initialized;
}

void godot_arvr_uninitialize(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (arvr_data->ovr_is_initialized) {
		for (int eye = 0; eye < VRAPI_EYE_COUNT; eye++) {
			delete arvr_data->frameBuffer[eye];
			arvr_data->frameBuffer[eye] = NULL;
		}
		vrapi_Shutdown();
		arvr_data->ovr_is_initialized = false;
	}
}

godot_vector2 godot_arvr_get_render_targetsize(const void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
	godot_vector2 size;

	if (arvr_data->ovr_is_initialized) {
		api->godot_vector2_new(&size, arvr_data->width, arvr_data->height);
	} else {
		api->godot_vector2_new(&size, 500, 500);
	}

	return size;
}

void ovr_transform_from_pose(godot_transform *p_dest, ovrPosef *p_pose, float p_world_scale) {
	godot_quat q;
	godot_basis basis;
	godot_vector3 origin;

	api->godot_quat_new(&q, p_pose->Orientation.x, p_pose->Orientation.y, p_pose->Orientation.z, p_pose->Orientation.w);
	api->godot_basis_new_with_euler_quat(&basis, &q);

	api->godot_vector3_new(&origin, p_pose->Position.x * p_world_scale, p_pose->Position.y * p_world_scale, p_pose->Position.z * p_world_scale);
	api->godot_transform_new(p_dest, &basis, &origin);
}

godot_transform godot_arvr_get_transform_for_eye(void *p_data, godot_int p_eye, godot_transform *p_cam_transform) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
	godot_transform transform_for_eye;
	godot_transform reference_frame = arvr_api->godot_arvr_get_reference_frame();
	godot_transform ret;
	godot_vector3 offset;
	godot_real world_scale = arvr_api->godot_arvr_get_worldscale();

	if (arvr_data != NULL && arvr_data->ovr != NULL) {
		if (p_eye == 0) {
			// must retrieve the center matrix between our two eyes
		} else {
			// TODO This needs to be altered depending on which eye we're getting the position for.
			ovrPosef tracking_transform = vrapi_GetTrackingTransform(arvr_data->ovr, VRAPI_TRACKING_TRANSFORM_CURRENT);
			ovr_transform_from_pose(&transform_for_eye, &tracking_transform, world_scale);
		}
	} else {
		// do something here? shouldn't ever be called.
	}

	// Now construct our full transform, the order may be in reverse, have to test
	// :)
	ret = *p_cam_transform;
	ret = api->godot_transform_operator_multiply(&ret, &reference_frame);
	//	ret = api->godot_transform_operator_multiply(&ret,
	//&arvr_data->hmd_transform);
	ret = api->godot_transform_operator_multiply(&ret, &transform_for_eye);

	return ret;
};

void godot_arvr_fill_projection_for_eye(void *p_data, godot_real *p_projection,
		godot_int p_eye, godot_real p_aspect,
		godot_real p_z_near,
		godot_real p_z_far) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (arvr_data->ovr_is_initialized) {

		// Not sure
		ovrMatrix4f matrix = arvr_data->headTracker.Eye[p_eye == 2 ? 1 : 0].ProjectionMatrix;

		int k = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				p_projection[k++] = matrix.M[j][i];
			}
		};

	} else {
		// uhm, should do something here really..
	};
};

void godot_arvr_commit_for_eye(void *p_data, godot_int p_eye,
		godot_rid *p_render_target,
		godot_rect2 *p_screen_rect) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
	ovrTracking2 tracking;
	unsigned long long fence;

	godot_rect2 screen_rect = *p_screen_rect;
	godot_vector2 render_size = godot_arvr_get_render_targetsize(p_data);

	// @TODO BIG ONE, seeing this module will only work with Godot 3.2 onwards we know that we have our new
	// texture logic available. We should not be doing the copy here but instead implement godot_arvr_get_external_texture_for_eye
	// I will do this shortly.

	if (arvr_data->ovr_is_initialized && arvr_data->ovr) {
		uint32_t texid = arvr_api->godot_arvr_get_texid(p_render_target);
		int eye = p_eye == 2 ? 1 : 0;

		if (eye == 0) {
			arvr_data->layer = vrapi_DefaultLayerProjection2();
			arvr_data->layer.HeadPose = tracking.HeadPose;
		}

		const int colorTextureSwapChainIndex =
				arvr_data->frameIndex %
				vrapi_GetTextureSwapChainLength(arvr_data->frameBuffer[eye]->mColorTextureSwapChain);
		const unsigned int textureId = vrapi_GetTextureSwapChainHandle(
				arvr_data->frameBuffer[eye]->mColorTextureSwapChain, colorTextureSwapChainIndex);

		// Blit to 'textureId' using the 'ProjectionMatrix' from 'ovrTracking2'.
		/*
    // blit to OVRs buffers
    // Switch to eye render target
    arvr_data->eyeRenderTexture[eye]->SetRenderSurface();

    // copy our buffer...Unfortunately, at this time Godot can't render directly
    into Oculus'
    // buffers. Something to discuss with Juan some day but I think this is
    posing serious
    // problem with the way our forward renderer handles several effects...
    // Worth further investigation though as this is wasteful...
    blit_render(&arvr_data->shader, texid);

    // Avoids an error when calling SetAndClearRenderSurface during next
    iteration.
    // Without this, during the next while loop iteration
    SetAndClearRenderSurface
    // would bind a framebuffer with an invalid COLOR_ATTACHMENT0 because the
    texture ID
    // associated with COLOR_ATTACHMENT0 had been unlocked by calling
    wglDXUnlockObjectsNV.
    arvr_data->eyeRenderTexture[eye]->UnsetRenderSurface();

    // Commit changes to the textures so they get picked up frame
    arvr_data->eyeRenderTexture[eye]->Commit();
    */

		arvr_data->layer.Textures[eye].ColorSwapChain =
				arvr_data->frameBuffer[eye]->mColorTextureSwapChain;
		arvr_data->layer.Textures[eye].SwapChainIndex = colorTextureSwapChainIndex;
		arvr_data->layer.Textures[eye].TexCoordsFromTanAngles =
				ovrMatrix4f_TanAngleMatrixFromProjection(
						&arvr_data->headTracker.Eye[eye].ProjectionMatrix);

		if (eye == 1) {
			// Insert 'fence' using eglCreateSyncKHR.

			const ovrLayerHeader2 *layers[] = { &arvr_data->layer.Header };

			ovrSubmitFrameDescription2 frameDesc = {};
			frameDesc.FrameIndex = arvr_data->frameIndex;
			frameDesc.DisplayTime = arvr_data->predictedDisplayTime;
			//      frameDesc.CompletionFence = fence;
			frameDesc.LayerCount = 1;
			frameDesc.Layers = layers;

			// Hand over the eye images to the time warp.
			vrapi_SubmitFrame2(arvr_data->ovr, &frameDesc);

			arvr_data->frameIndex++;
		}
	}
}

void _on_surface_changed(arvr_data_struct *arvr_data) {
	if (arvr_data != NULL && arvr_data->ovr_is_initialized) {
		/* must make this work
		ANativeWindow *newNativeWindow = ANativeWindow_fromSurface(arvr_data->java.Env, arvr_data->Surface);
		if (arvr_data->NativeWindow != newNativeWindow) {
			if (arvr_data->NativeWindow != NULL) {
				// out with the old
				ANativeWindow_release(arvr_data->NativeWindow);
				arvr_data->NativeWindow = NULL;
			}

			if (newNativeWindow != NULL) {
				// In with the new
				arvr_data->NativeWindow = newNativeWindow;
			}
		} else if (newNativeWindow != NULL) {
			// release our hold on this
			ANativeWindow_release(newNativeWindow);
		}
*/
	}
}

void _check_ovr(arvr_data_struct *arvr_data) {
	if (arvr_data != NULL && arvr_data->ovr_is_initialized) {
		if (arvr_data->Resumed && arvr_data->NativeWindow != NULL) {
			if (arvr_data->ovr == NULL) {
				// Enter VR mode once the Android Activity is in the resumed state with a
				// valid ANativeWindow.
				ovrModeParms modeParms = vrapi_DefaultModeParms(&arvr_data->java);

				// No need to reset the FLAG_FULLSCREEN window flag when using a View
				modeParms.Flags &= ~VRAPI_MODE_FLAG_RESET_WINDOW_FULLSCREEN;

				modeParms.Flags |= VRAPI_MODE_FLAG_NATIVE_WINDOW;
				modeParms.Display = (size_t)arvr_data->Display;
				modeParms.WindowSurface = (size_t)arvr_data->NativeWindow;
				modeParms.ShareContext = (size_t)arvr_data->Context;

				// we are currently in our render thread so we can do this, but this may change
				// arvr_data->RenderThreadTid = gettid();

				arvr_data->ovr = vrapi_EnterVrMode(&modeParms);
				if (arvr_data->ovr == NULL) {
					ALOGE("Invalid ANativeWindow!");
					arvr_data->NativeWindow = NULL;
				} else {
					vrapi_SetClockLevels(arvr_data->ovr, arvr_data->CpuLevel, arvr_data->GpuLevel);
					ALOGV("		vrapi_SetClockLevels( %d, %d )", arvr_data->CpuLevel, arvr_data->GpuLevel);

					vrapi_SetPerfThread(arvr_data->ovr, VRAPI_PERF_THREAD_TYPE_MAIN, arvr_data->MainThreadTid);
					ALOGV("		vrapi_SetPerfThread( MAIN, %d )", arvr_data->MainThreadTid);

					vrapi_SetPerfThread(arvr_data->ovr, VRAPI_PERF_THREAD_TYPE_RENDERER, arvr_data->RenderThreadTid);
					ALOGV("		vrapi_SetPerfThread( RENDERER, %d )", arvr_data->RenderThreadTid);

					// Set the tracking transform to use, by default this is eye level.
					vrapi_SetTrackingTransform(arvr_data->ovr, vrapi_GetTrackingTransform(arvr_data->ovr, VRAPI_TRACKING_TRANSFORM_SYSTEM_CENTER_EYE_LEVEL));

					// reset this back to 1...
					arvr_data->frameIndex = 1;
				}
			}
		} else if (arvr_data->ovr != NULL) {
			// may need to sync up with the render thread...

			ALOGV("        eglGetCurrentSurface( EGL_DRAW ) = %p", eglGetCurrentSurface(EGL_DRAW));

			ALOGV("        vrapi_LeaveVrMode()");
			vrapi_LeaveVrMode(arvr_data->ovr);
			arvr_data->ovr = NULL;

			ALOGV("        eglGetCurrentSurface( EGL_DRAW ) = %p", eglGetCurrentSurface(EGL_DRAW));
		}
	}
}

void godot_arvr_process(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	// this method gets called before every frame is rendered, here is where you
	// should update tracking data, update controllers, etc.

	if (arvr_data != NULL && arvr_data->ovr_is_initialized) {

		// First check if our nativewindow has changed.
		// Not sure if this is the right place for this or
		// if we should be getting a message in our main thread somehow about this.
		_on_surface_changed(arvr_data);

		// now make sure our ovr structure is set, again this may have to move elsewhere
		_check_ovr(arvr_data);

		// now that we know whether we're still alive or not, let's update our tracking....
		if (arvr_data->ovr != NULL) {
			// Get the HMD pose, predicted for the middle of the time period during
			// which the new eye images will be displayed. The number of frames
			// predicted ahead depends on the pipeline depth of the engine and the
			// synthesis rate. The better the prediction, the less black will be pulled
			// in at the edges.
			arvr_data->predictedDisplayTime = vrapi_GetPredictedDisplayTime(arvr_data->ovr, arvr_data->frameIndex);
			arvr_data->headTracker = vrapi_GetPredictedTracking2(arvr_data->ovr, arvr_data->predictedDisplayTime);

			// anything else we need to update?
		}
	}
}

void *godot_arvr_constructor(godot_object *p_instance) {
	godot_string ret;

	arvr_data_struct *arvr_data =
			(arvr_data_struct *)api->godot_alloc(sizeof(arvr_data_struct));

	arvr_data->ovr_is_initialized = false;
	arvr_data->CpuLevel = 2;
	arvr_data->GpuLevel = 2;
	arvr_data->ovr = NULL;
	arvr_data->NativeWindow = NULL;
	// arvr_data->Resumed = false;
	arvr_data->Resumed = true; // true for now until we find a way to query this
	arvr_data->frameIndex = 0;
	arvr_data->Display = 0;
	arvr_data->Context = EGL_NO_CONTEXT;

	return arvr_data;
};

void godot_arvr_destructor(void *p_data) {
	if (p_data != NULL) {
		arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

		if (arvr_data->ovr_is_initialized) {
			// this should have already been called... But just in case...
			godot_arvr_uninitialize(p_data);
		}

		api->godot_free(p_data);
	};
};

const godot_arvr_interface_gdnative interface_struct = {
	GODOTVR_API_MAJOR,
	GODOTVR_API_MINOR,
	godot_arvr_constructor,
	godot_arvr_destructor,
	godot_arvr_get_name,
	godot_arvr_get_capabilities,
	godot_arvr_get_anchor_detection_is_enabled,
	godot_arvr_set_anchor_detection_is_enabled,
	godot_arvr_is_stereo,
	godot_arvr_is_initialized,
	godot_arvr_initialize,
	godot_arvr_uninitialize,
	godot_arvr_get_render_targetsize,
	godot_arvr_get_transform_for_eye,
	godot_arvr_fill_projection_for_eye,
	godot_arvr_commit_for_eye,
	godot_arvr_process
};
