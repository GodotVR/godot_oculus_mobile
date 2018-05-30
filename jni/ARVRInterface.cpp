////////////////////////////////////////////////////////////////////////////////////////////////
// Our main ARVRInterface code for our GearVR GDNative module

// Note, even though this is pure C code, we're using the C++ compiler as
// Microsoft never updated their C compiler to understand more modern dialects
// and openvr uses pesky things such as namespaces

#include "ARVRInterface.h"

///////////////////////////////////////////////////////////////////////////////////////////
// our ARVR interface
godot_string godot_arvr_get_name(const void *p_data) {
	godot_string ret;

	char name[] = "GearVR";
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

void godot_arvr_set_anchor_detection_is_enabled(void *p_data,
		bool p_enable){
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

	ret = arvr_data->gearvr_is_initialized;

	return ret;
}

godot_bool godot_arvr_initialize(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
    
    JNIEnv *jniEnv = api->godot_android_get_env();
    
    jclass activityThread = jniEnv->FindClass("android/app/ActivityThread");
    jmethodID currentActivityThread = jniEnv->GetStaticMethodID(activityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject at = jniEnv->CallStaticObjectMethod(activityThread, currentActivityThread);
    jmethodID getApplication = jniEnv->GetMethodID(activityThread, "getApplication", "()Landroid/app/Application;");
    jobject context = jniEnv->CallObjectMethod(at, getApplication);
    
    jobject activityObject = context;
    EGLDisplay eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    ANativeWindow *nativeWindow;

	if (!arvr_data->gearvr_is_initialized) {
		
        arvr_data->java.Env = jniEnv;
		arvr_data->java.ActivityObject = activityObject;

		// Initialize the API.
		const ovrInitParms initParms = vrapi_DefaultInitParms( &arvr_data->java );
		if (vrapi_Initialize(&initParms) != VRAPI_INITIALIZE_SUCCESS)
        {
			printf("Failed to initialize VrApi!");
            abort();
		}
		
		// Create an EGLContext for the application.
		EGLContext eglContext;
        
        // Get the suggested resolution to create eye texture swap chains.
        arvr_data->width = vrapi_GetSystemPropertyInt(&arvr_data->java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH);
        arvr_data->height = vrapi_GetSystemPropertyInt(&arvr_data->java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_HEIGHT);
        
        // Allocate a texture swap chain for each eye with the application's EGLContext current.
        //ovrTextureSwapChain * colorTextureSwapChain[VRAPI_FRAME_LAYER_EYE_MAX];        
        for ( int eye = 0; eye < VRAPI_FRAME_LAYER_EYE_MAX; eye++ )
        {
				arvr_data->colorTextureSwapChain[eye] = vrapi_CreateTextureSwapChain( 
				VRAPI_TEXTURE_TYPE_2D, 
				VRAPI_TEXTURE_FORMAT_8888,
				arvr_data->width,
				arvr_data->height,
				1, true);
        }

		// This next bit may need to move into our process to deal with our game being paused.
		// We could check for ovr being NULL for this and setting it to NULL whenever we exit VrMode
		// For now we just do it here..

		// Enter VR mode once the Android Activity is in the resumed state with a valid ANativeWindow.
		ovrModeParms modeParms = vrapi_DefaultModeParms( &arvr_data->java );
		modeParms.Flags |= VRAPI_MODE_FLAG_NATIVE_WINDOW;
		modeParms.Display = (size_t)eglDisplay;
		modeParms.WindowSurface = (size_t)nativeWindow;
		modeParms.ShareContext = (size_t)eglContext;
		arvr_data->ovr = vrapi_EnterVrMode( &modeParms );

		// Set the tracking transform to use, by default this is eye level.
		vrapi_SetTrackingTransform(arvr_data->ovr, vrapi_GetTrackingTransform(arvr_data->ovr, VRAPI_TRACKING_TRANSFORM_SYSTEM_CENTER_EYE_LEVEL));

		arvr_data->frameIndex = 1;
		arvr_data->gearvr_is_initialized = true;
		
	}

	// and return our result
	return arvr_data->gearvr_is_initialized;
}

void godot_arvr_uninitialize(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (arvr_data->gearvr_is_initialized) {
		if (arvr_data->ovr != NULL) {
			// Must leave VR mode when the Android Activity is paused or the Android Surface
			// is destroyed or changed.
			vrapi_LeaveVrMode(arvr_data->ovr);
			arvr_data->ovr = NULL;
		}

		// Destroy the texture swap chains.
		// Make sure to delete the swapchains before the application's EGLContext is destroyed.
		for ( int eye = 0; eye < VRAPI_FRAME_LAYER_EYE_MAX; eye++ ) {
			vrapi_DestroyTextureSwapChain(arvr_data->colorTextureSwapChain[eye]);
		}

		// Shut down the API.
		vrapi_Shutdown();

		arvr_data->gearvr_is_initialized = false;
	}
}

godot_vector2 godot_arvr_get_render_targetsize(const void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
	godot_vector2 size;

	api->godot_vector2_new(&size, arvr_data->width, arvr_data->height);

	return size;
}

godot_transform godot_arvr_get_transform_for_eye(void *p_data, godot_int p_eye, godot_transform *p_cam_transform) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
	godot_transform transform_for_eye;
	godot_transform reference_frame = arvr_api->godot_arvr_get_reference_frame();
	godot_transform ret;
	godot_vector3 offset;
	godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
    
//	if (p_eye == 0) {
		// ok, we actually get our left and right eye position from tracking data, not our head center with eye offsets
		// so lets find the center :)
//		oculus_transform_from_poses(&transform_for_eye, &arvr_data->EyeRenderPose[0], &arvr_data->EyeRenderPose[1], world_scale);		
//	} else if (arvr_data->oculus_is_initialized) {
//		oculus_transform_from_pose(&transform_for_eye, &arvr_data->EyeRenderPose[p_eye == 2 ? 1 : 0], world_scale);
//	} else {
		// really not needed, just being paranoid..
		//godot_vector3 offset;
		api->godot_transform_new_identity(&transform_for_eye);
		if (p_eye == 1) {
			api->godot_vector3_new(&offset, -0.035 * world_scale, 0.0, 0.0);
		} else {
			api->godot_vector3_new(&offset, 0.035 * world_scale, 0.0, 0.0);
		};
		api->godot_transform_translated(&transform_for_eye, &offset);
//	};

	// Now construct our full transform, the order may be in reverse, have to test
	// :)
	ret = *p_cam_transform;
	ret = api->godot_transform_operator_multiply(&ret, &reference_frame);
//	ret = api->godot_transform_operator_multiply(&ret, &arvr_data->hmd_transform);
	ret = api->godot_transform_operator_multiply(&ret, &transform_for_eye);

	return ret;
};

void godot_arvr_fill_projection_for_eye(void *p_data, godot_real *p_projection, godot_int p_eye, godot_real p_aspect, godot_real p_z_near, godot_real p_z_far) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	if (arvr_data->gearvr_is_initialized) {
		// need to implement, use arvr_data->tracking.Eye[eye].ProjectionMatrix
	} else {
		// uhm, should do something here really..
	};
};

void godot_arvr_commit_for_eye(void *p_data, godot_int p_eye, godot_rid *p_render_target, godot_rect2 *p_screen_rect) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;
    ovrTracking2 tracking;
    unsigned long long fence;

	godot_rect2 screen_rect = *p_screen_rect;
	godot_vector2 render_size = godot_arvr_get_render_targetsize(p_data);

	if (arvr_data->gearvr_is_initialized) {
		uint32_t texid = arvr_api->godot_arvr_get_texid(p_render_target);
		int eye = p_eye == 2 ? 1 : 0;

		if (eye == 0) {
			arvr_data->layer = vrapi_DefaultLayerProjection2();
			arvr_data->layer.HeadPose = tracking.HeadPose;
		}

		const int colorTextureSwapChainIndex = arvr_data->frameIndex % vrapi_GetTextureSwapChainLength( arvr_data->colorTextureSwapChain[eye] );
		const unsigned int textureId = vrapi_GetTextureSwapChainHandle( arvr_data->colorTextureSwapChain[eye], colorTextureSwapChainIndex );

		// Blit to 'textureId' using the 'ProjectionMatrix' from 'ovrTracking2'.
/*
		// blit to OVRs buffers
		// Switch to eye render target
		arvr_data->eyeRenderTexture[eye]->SetRenderSurface();

		// copy our buffer...Unfortunately, at this time Godot can't render directly into Oculus'
		// buffers. Something to discuss with Juan some day but I think this is posing serious 
		// problem with the way our forward renderer handles several effects...
		// Worth further investigation though as this is wasteful...
		blit_render(&arvr_data->shader, texid);

		// Avoids an error when calling SetAndClearRenderSurface during next iteration.
		// Without this, during the next while loop iteration SetAndClearRenderSurface
		// would bind a framebuffer with an invalid COLOR_ATTACHMENT0 because the texture ID
		// associated with COLOR_ATTACHMENT0 had been unlocked by calling wglDXUnlockObjectsNV.
		arvr_data->eyeRenderTexture[eye]->UnsetRenderSurface();

		// Commit changes to the textures so they get picked up frame
		arvr_data->eyeRenderTexture[eye]->Commit();
*/

		arvr_data->layer.Textures[eye].ColorSwapChain = arvr_data->colorTextureSwapChain[eye];
		arvr_data->layer.Textures[eye].SwapChainIndex = colorTextureSwapChainIndex;
		arvr_data->layer.Textures[eye].TexCoordsFromTanAngles = ovrMatrix4f_TanAngleMatrixFromProjection( &arvr_data->tracking.Eye[eye].ProjectionMatrix );

		if (eye == 1) {
			// Insert 'fence' using eglCreateSyncKHR.

			const ovrLayerHeader2 * layers[] = {
				&arvr_data->layer.Header
			};

			ovrSubmitFrameDescription2 frameDesc = {};
			frameDesc.FrameIndex = arvr_data->frameIndex;
			frameDesc.DisplayTime = arvr_data->predictedDisplayTime;
			frameDesc.CompletionFence = fence;
			frameDesc.LayerCount = 1;
			frameDesc.Layers = layers;

			// Hand over the eye images to the time warp.
			vrapi_SubmitFrame2(arvr_data->ovr, &frameDesc );

			arvr_data->frameIndex++;
		}
	}
}

void godot_arvr_process(void *p_data) {
	arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

	// this method gets called before every frame is rendered, here is where you
	// should update tracking data, update controllers, etc.

	if (arvr_data->gearvr_is_initialized) {
		// Get the HMD pose, predicted for the middle of the time period during which
		// the new eye images will be displayed. The number of frames predicted ahead
		// depends on the pipeline depth of the engine and the synthesis rate.
		// The better the prediction, the less black will be pulled in at the edges.
		arvr_data->predictedDisplayTime = vrapi_GetPredictedDisplayTime(arvr_data->ovr, arvr_data->frameIndex);
		arvr_data->tracking = vrapi_GetPredictedTracking2(arvr_data->ovr, arvr_data->predictedDisplayTime);
	}
}

void *godot_arvr_constructor(godot_object *p_instance) {
	godot_string ret;

	arvr_data_struct *arvr_data = (arvr_data_struct *)api->godot_alloc(sizeof(arvr_data_struct));

	arvr_data->gearvr_is_initialized = false;
	arvr_data->ovr = NULL;
	arvr_data->width = 500;
	arvr_data->height = 500;

	return arvr_data;
};

void godot_arvr_destructor(void *p_data) {
	if (p_data != NULL) {
		arvr_data_struct *arvr_data = (arvr_data_struct *)p_data;

		// JIC this hasn't been called yet, it should do nothing if it has...
		godot_arvr_uninitialize(p_data);

		api->godot_free(p_data);
	};
};

const godot_arvr_interface_gdnative interface_struct = {
    GODOTVR_API_MAJOR, GODOTVR_API_MINOR,
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
