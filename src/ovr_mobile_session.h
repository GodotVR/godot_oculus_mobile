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
	static OvrMobileSession* get_singleton_instance();
	static void delete_singleton_instance();

	void commit_for_eye(godot_int godot_eye);

	void fill_projection_for_eye(godot_real *projection, godot_int godot_eye, godot_real aspect, godot_real z_near,
			godot_real z_far);

	int get_render_target_height() {
		return height;
	}

	int get_render_target_width() {
		return width;
	}

	void set_render_target_size_multiplier(double multiplier) {
		this->render_target_size_multiplier = multiplier;
	}

	void set_swap_interval(unsigned int swap_interval) {
	    this->swap_interval = swap_interval;
	}

	void set_default_layer_color_scale(float r, float g, float b, float a);

	int get_texture_for_eye(godot_int godot_eye);

	godot_transform get_transform_for_eye(godot_int godot_eye, godot_transform *cam_transform);

	// Initializes the Oculus VrApi and enters VR mode. This is required to be able to access
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

	ovrMobile* get_ovr_mobile_context() {return ovr;};

	ovrTracking2 get_head_tracker() {return head_tracker;};

	const OvrMobileController* get_ovr_mobile_controller() const {return ovr_mobile_controller;};

	const ovrJava *get_ovr_java() {
		return &java;
	}

	double get_predicted_display_time() const {return predicted_display_time;};


private:

	OvrMobileSession();
	~OvrMobileSession();

	bool enter_vr_mode();

	void exit_vr_mode();

	inline int get_ovr_eye_from_godot_eye(godot_int godot_eye) {
		return godot_eye == /* EYE_RIGHT */ 2 ? static_cast<int>(ovrEye::VRAPI_EYE_RIGHT) : static_cast<int>(ovrEye::VRAPI_EYE_LEFT);
	}

	static OvrMobileSession* singleton_instance;

	bool initialized = false;
	int width;
	int height;
	double render_target_size_multiplier;
	unsigned int swap_interval;
	uint64_t frame_index = 1;
	double predicted_display_time = 0;

	ovrVector4f default_layer_color_scale;

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
