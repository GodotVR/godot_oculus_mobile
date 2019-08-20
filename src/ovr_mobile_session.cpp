/**
* Created by Fredia Huya-Kouadio.
*/

#include "ovr_mobile_session.h"
#include "common.h"
#include <unistd.h>

namespace ovrmobile {

namespace {
const int kDefaultCpuLevel = 1;
const int kDefaultGpuLevel = 1;
const int kSwapInterval = 1;
const bool kDefaultEnableMultiview = false;
const int kDefaultRenderTargetHeight = 1024;
const int kDefaultRenderTargetWidth = 1024;
} // namespace


OvrMobileSession* OvrMobileSession::singleton_instance = NULL;

OvrMobileSession* OvrMobileSession::get_singleton_instance() {
	if (singleton_instance == NULL) {
		singleton_instance = new OvrMobileSession();
	}
	return singleton_instance;
}

void OvrMobileSession::delete_singleton_instance() {
	delete singleton_instance;
	singleton_instance = NULL;
}


OvrMobileSession::OvrMobileSession() :
		width(
				kDefaultRenderTargetWidth),
		height(kDefaultRenderTargetHeight),
		cpu_level(
				kDefaultCpuLevel),
		gpu_level(kDefaultGpuLevel) {
	JNIEnv *env = android_api->godot_android_get_env();
	java.ActivityObject = env->NewGlobalRef(android_api->godot_android_get_activity());
	java.Env = env;
	env->GetJavaVM(&java.Vm);

	ovr_mobile_controller = new OvrMobileController();
}

OvrMobileSession::~OvrMobileSession() {
	delete ovr_mobile_controller;

	// Exit vr mode if necessary.
	exit_vr_mode();

	// Uninitialize the session if necessary.
	uninitialize();
}

bool OvrMobileSession::initialize() {
	if (initialized) {
		return initialized;
	}

	ALOGV("OvrMobileSession::initialize() called");

	const ovrInitParms init_parms = vrapi_DefaultInitParms(&java);
	ovrInitializeStatus init_status = vrapi_Initialize(&init_parms);
	if (init_status != VRAPI_INITIALIZE_SUCCESS) {
		ALOGE("Failed to initialize VrApi.");
		return false;
	}

	// init our extensions container
	ovrmobile::OpenGLExtensions::initExtensions();

	// Get the suggested resolution to create eye texture swap chains.
	width = vrapi_GetSystemPropertyInt(&java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_WIDTH);
	height = vrapi_GetSystemPropertyInt(&java, VRAPI_SYS_PROP_SUGGESTED_EYE_TEXTURE_HEIGHT);
	ALOGV("  vrapi Render target size: w %i / h %i", width, height);

	// Create Frame buffers for each eye
	for (auto &eye_frame_buffer : frame_buffers) {
		eye_frame_buffer = new ovrmobile::FrameBuffer(
				kDefaultEnableMultiview,
				GL_RGBA8,
				width,
				height,
				NUM_MULTI_SAMPLES);
	}

	initialized = true;
	return initialized;
}

int OvrMobileSession::get_texture_for_eye(godot_int godot_eye) {
	if (!initialized) {
		return 0;
	}

	int ovr_eye = get_ovr_eye_from_godot_eye(godot_eye);
	return frame_buffers[ovr_eye]->getFrameBufferTexture();
}

void godot_transform_from_ovrMatrix(godot_transform *p_dest, const ovrMatrix4f *p_matrix, godot_real p_world_scale) {
	godot_basis basis;
	godot_vector3 origin;
	godot_real *basis_ptr = (godot_real *)&basis; 

	ovrMatrix4f _matrix = ovrMatrix4f_Inverse(p_matrix);

	// extract the rotation 3x3 part from the full ovrMatrix4f
	int k = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			basis_ptr[k++] = _matrix.M[i][j];
		};
	};

	// get the translation part from the ovrMatrix4f
	api->godot_vector3_new(&origin, _matrix.M[0][3] * p_world_scale, _matrix.M[1][3] * p_world_scale, _matrix.M[2][3] * p_world_scale);

	api->godot_transform_new(p_dest, &basis, &origin);
};

godot_transform OvrMobileSession::get_transform_for_eye(godot_int godot_eye, godot_transform *cam_transform) {
	godot_transform ret;

	godot_transform transform_for_eye;
	godot_transform reference_frame = arvr_api->godot_arvr_get_reference_frame();
	godot_real world_scale = arvr_api->godot_arvr_get_worldscale();

	if (in_vr_mode()) {
		if (godot_eye == 1 || godot_eye == 2) { // check if we have the left(1) or right(2) eye
			ovrMatrix4f* ovrEyeMatrix = &head_tracker.Eye[godot_eye - 1].ViewMatrix;
			godot_transform_from_ovrMatrix(&transform_for_eye, ovrEyeMatrix, world_scale);
		} else { // mono eye (godot_eye == 0); used by godot to set the ARVRCamera matrix
			godot_transform_from_ovr_pose(&transform_for_eye, head_tracker.HeadPose.Pose, world_scale);
		}
	} else { 
		api->godot_transform_new_identity(&transform_for_eye);
	}

	ret = *cam_transform;
	ret = api->godot_transform_operator_multiply(&ret, &reference_frame);
	ret = api->godot_transform_operator_multiply(&ret, &transform_for_eye);

	return ret;
}

void OvrMobileSession::commit_for_eye(godot_int godot_eye) {
	if (!in_vr_mode()) {
		return;
	}

	int ovr_eye = get_ovr_eye_from_godot_eye(godot_eye);

	// Godot iterates first through the left eye, followed by the right eye in order
	// to submit the frame to the vrapi. So we perform initialization while on the left eye,
	// and submit our frame while on the right eye.
	if (ovr_eye == static_cast<int>(ovrEye::VRAPI_EYE_LEFT)) {
		layer = vrapi_DefaultLayerProjection2();
		layer.HeadPose = head_tracker.HeadPose;
		layer.Header.Flags |= VRAPI_FRAME_LAYER_FLAG_CHROMATIC_ABERRATION_CORRECTION;
	}

	// Set the layer's texture properties.
	layer.Textures[ovr_eye].ColorSwapChain = frame_buffers[ovr_eye]->mColorTextureSwapChain;
	layer.Textures[ovr_eye].SwapChainIndex = frame_buffers[ovr_eye]->mTextureSwapChainIndex;
	layer.Textures[ovr_eye].TexCoordsFromTanAngles = ovrMatrix4f_TanAngleMatrixFromProjection(
			&head_tracker.Eye[ovr_eye].ProjectionMatrix);

	frame_buffers[ovr_eye]->advance();

	if (ovr_eye == static_cast<int>(ovrEye::VRAPI_EYE_RIGHT)) {

		// Submit the frame.
		const ovrLayerHeader2 *layers[] = { &layer.Header };

		ovrSubmitFrameDescription2 frameDesc = {};
		frameDesc.Flags = 0;
		frameDesc.SwapInterval = kSwapInterval;
		frameDesc.FrameIndex = frame_index;
		frameDesc.DisplayTime = predicted_display_time;
		frameDesc.LayerCount = 1;
		frameDesc.Layers = layers;

		// Hand over the eye images to the time warp.
		vrapi_SubmitFrame2(ovr, &frameDesc);

		frame_index++;
	}
}

void OvrMobileSession::fill_projection_for_eye(godot_real *projection, godot_int godot_eye, godot_real aspect,
		godot_real z_near, godot_real z_far) {
	if (!in_vr_mode()) {
		ALOGW("Not in VR mode. Unable to fill projection for eye.");
		return;
	}

	// Not sure
	const ovrTracking2 tracking_state = head_tracker;
	ovrMatrix4f matrix;
	switch (godot_eye) {
		case 0: // EYE_MONO -- This corresponds to the hmd projection.
		case 1: // EYE_LEFT -- We're using the left eye as default for the hmd projection.
		default:
			matrix = tracking_state.Eye[0].ProjectionMatrix;
			break;

		case 2: // EYE_RIGHT
			matrix = tracking_state.Eye[1].ProjectionMatrix;
			break;
	}

	matrix.M[2][2] = -(z_far + z_near) / (z_far - z_near);
	matrix.M[2][3] = -(2.0f * z_far * z_near) / (z_far - z_near);
	
	int k = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			projection[k++] = matrix.M[j][i];
		}
	}
}

void OvrMobileSession::process() {
	if (should_exit_vr_mode()) {
		exit_vr_mode();
		return;
	}

	if (should_enter_vr_mode() && !enter_vr_mode()) {
		// We're not able to enter vr mode, so let's return early.
		return;
	}

	// If we get here, then we're successfully in vr mode.

	// Get the HMD pose, predicted for the middle of the time period during
	// which the new eye images will be displayed. The number of frames
	// predicted ahead depends on the pipeline depth of the engine and the
	// synthesis rate. The better the prediction, the less black will be pulled
	// in at the edges.
	predicted_display_time = vrapi_GetPredictedDisplayTime(ovr, frame_index);
	head_tracker = vrapi_GetPredictedTracking2(ovr, predicted_display_time);

	// Update the oculus controllers state.
	ovr_mobile_controller->process(ovr, &java);
}

bool OvrMobileSession::enter_vr_mode() {
	if (ovr == nullptr) {
		if (native_window == nullptr) {
			jobject surface = android_api->godot_android_get_surface();
			native_window = ANativeWindow_fromSurface(java.Env, surface);
		}

		ovrModeParms mode_parms = vrapi_DefaultModeParms(&java);
		mode_parms.Flags |= VRAPI_MODE_FLAG_RESET_WINDOW_FULLSCREEN;
		mode_parms.Flags |= VRAPI_MODE_FLAG_NATIVE_WINDOW;
		mode_parms.WindowSurface = reinterpret_cast<size_t>(native_window);
		mode_parms.Display = reinterpret_cast<size_t>(eglGetCurrentDisplay());
		mode_parms.ShareContext = reinterpret_cast<size_t>(eglGetCurrentContext());

		ovr = vrapi_EnterVrMode(&mode_parms);
		if (ovr == nullptr) {
			ALOGE("Unable to enter Oculus Mobile VR mode.");
			return false;
		}

		ALOGV("Entered Oculus Mobile VR mode.");

		vrapi_SetClockLevels(ovr, cpu_level, gpu_level);
		ALOGV("		vrapi_SetClockLevels( %d, %d )", cpu_level, gpu_level);

		vrapi_SetPerfThread(ovr, VRAPI_PERF_THREAD_TYPE_RENDERER, gettid());
		ALOGV("		vrapi_SetPerfThread( RENDERER, %d )", gettid());

		// From the doc: If VRAPI_EXTRA_LATENCY_MODE_ON specified, adds an extra frame of latency
		// for full GPU utilization.
		// It seems that nearly all apps on the Oculus Quest use this - except Youtube.
		vrapi_SetExtraLatencyMode(ovr, ovrExtraLatencyMode::VRAPI_EXTRA_LATENCY_MODE_ON);

		// Set the tracking transform to use, by default this is eye level.
		vrapi_SetTrackingSpace(ovr, ovrTrackingSpace::VRAPI_TRACKING_SPACE_LOCAL_FLOOR);

		vrapi_SetPropertyInt(&java, VRAPI_REORIENT_HMD_ON_CONTROLLER_RECENTER,
				VRAPI_TRUE);
	}

	return true;
}

void OvrMobileSession::on_pause() {
	// Attempt to exit vr mode.
	exit_vr_mode();
}

void OvrMobileSession::on_resume() {
	// Attempt to enter vr mode if we can.
	if (should_enter_vr_mode()) {
		enter_vr_mode();
	}
}

void OvrMobileSession::exit_vr_mode() {
	if (ovr != nullptr) {
		vrapi_LeaveVrMode(ovr);
		ovr = nullptr;
		ALOGV("Left Oculus Mobile VR mode.");
	}

	if (native_window != nullptr) {
		ANativeWindow_release(native_window);
		native_window = nullptr;
	}
}

void OvrMobileSession::uninitialize() {
	if (!initialized) {
		return;
	}

	// Exit vr mode if necessary.
	exit_vr_mode();

	for (auto &eye_frame_buffer : frame_buffers) {
		delete eye_frame_buffer;
		eye_frame_buffer = nullptr;
	}

	vrapi_Shutdown();
	initialized = false;
}

/*
void OvrMobileSession::apply_tracking() {
    if (!is_initialized()) {
        return;
    }

    const double predictedDisplayTime = vrapi_GetPredictedDisplayTime(ovr, frame_index);

    head_tracker = vrapi_GetPredictedTracking2(ovr, predictedDisplayTime);
}


godot_vector3 getLocalPosition(void *p_data) {
    auto *arvr_data = (arvr_data_struct *) p_data;

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

} // namespace ovrmobile
