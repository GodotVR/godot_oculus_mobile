/**
* Created by Fredia Huya-Kouadio.
*/

#ifndef OVRMOBILE_OVR_MOBILE_SESSION_H
#define OVRMOBILE_OVR_MOBILE_SESSION_H

#include "VrApi_Types.h"
#include "framebuffer.h"
#include "ovr_mobile_controller.h"
#include <android/native_window_jni.h>

namespace ovrmobile {

class OvrMobileSession {
public:
	OvrMobileSession();

	~OvrMobileSession();

	void commit_for_eye(godot_int godot_eye);

	void fill_projection_for_eye(godot_real *projection, godot_int godot_eye, godot_real aspect, godot_real z_near,
			godot_real z_far);

	int get_render_target_height() {
		return height;
	}

	int get_render_target_width() {
		return width;
	}

	int get_texture_for_eye(godot_int godot_eye);

	godot_transform get_transform_for_eye(godot_int godot_eye, godot_transform *cam_transform);

	// Initializes the Oculus VrApi. This is required to be able to enter VR mode and access
	// the api functionality.
	bool initialize();

	bool in_vr_mode() {
		return initialized && ovr != nullptr;
	}

	bool is_initialized() { return initialized; }

	// Notifies that the interface should be paused. For ovrmobile, this means we should leave vr mode if it's active.
	void on_pause();

	// Notifies that the interface should be resumed. For ovrmobile, this means we should attempt to enter vr mode.
	void on_resume();

	// This method gets called before every frame is rendered..
	void process();

	// Shuts down the Oculus VrApi.
	void uninitialize();

private:
	bool should_enter_vr_mode() {
		return initialized && ovr == nullptr && android_api->godot_android_is_activity_resumed();
	}

	bool enter_vr_mode();

	bool should_exit_vr_mode() {
		return ovr != nullptr && (!initialized || !android_api->godot_android_is_activity_resumed());
	}

	void exit_vr_mode();

	inline int get_ovr_eye_from_godot_eye(godot_int godot_eye) {
		return godot_eye == /* EYE_RIGHT */ 2 ? static_cast<int>(ovrEye::VRAPI_EYE_RIGHT) : static_cast<int>(ovrEye::VRAPI_EYE_LEFT);
	}

	bool initialized = false;
	int width;
	int height;
	int cpu_level;
	int gpu_level;
	uint64_t frame_index = 1;
	double predicted_display_time = 0;

	ovrJava java;
	ovrLayerProjection2 layer;
	ovrMobile *ovr = nullptr;
	ovrTracking2 head_tracker;

	ANativeWindow *native_window = nullptr;
	FrameBuffer *frame_buffers[VRAPI_EYE_COUNT];

	OvrMobileController *ovr_mobile_controller = nullptr;
};

} // namespace ovrmobile

#endif // OVRMOBILE_OVR_MOBILE_SESSION_H
