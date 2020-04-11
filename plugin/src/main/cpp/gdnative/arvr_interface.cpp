////////////////////////////////////////////////////////////////////////////////////////////////
// Our main ARVRInterface code for our OVR Mobile GDNative module
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "arvr_interface.h"

namespace {
const char *kName = "OVRMobile";
} // namespace

godot_string godot_arvr_get_name(const void *p_data) {
	godot_string ret;

	godot::api->godot_string_new(&ret);
	godot::api->godot_string_parse_utf8(&ret, kName);

	return ret;
}

godot_int godot_arvr_get_capabilities(const void *p_data) {
	return 2 + 8; // 2 = ARVR_STEREO, 8 = ARVR_EXTERNAL
}

godot_bool godot_arvr_get_anchor_detection_is_enabled(const void *p_data) {
	// does not apply here
	return false;
}

void godot_arvr_set_anchor_detection_is_enabled(void *p_data, bool p_enable) {
	// we ignore this, not supported in this interface!
}

void godot_arvr_notification(void *p_data, godot_int p_what) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	switch (p_what) {
		case 1014: // NOTIFICATION_APP_RESUMED - The Android activity is resumed.
			arvr_data->ovr_mobile_session->on_resume();
			break;
		case 1015: // NOTIFICATION_APP_PAUSED - The Android activity is paused.
			arvr_data->ovr_mobile_session->on_pause();
			break;

		default:
			break;
	}
}

godot_bool godot_arvr_is_stereo(const void *p_data) {
	return true;
}

godot_bool godot_arvr_is_initialized(const void *p_data) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	return arvr_data->ovr_mobile_session->is_initialized();
}

godot_bool godot_arvr_initialize(void *p_data) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	return arvr_data->ovr_mobile_session->initialize();
}

void godot_arvr_uninitialize(void *p_data) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	arvr_data->ovr_mobile_session->uninitialize();
}

godot_vector2 godot_arvr_get_render_targetsize(const void *p_data) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	godot_vector2 size;

	godot::api->godot_vector2_new(&size, arvr_data->ovr_mobile_session->get_render_target_width(),
			arvr_data->ovr_mobile_session->get_render_target_height());
	return size;
}

godot_transform godot_arvr_get_transform_for_eye(void *p_data, godot_int p_eye, godot_transform *p_cam_transform) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	ALOG_ASSERT(arvr_data != nullptr, "Invalid arvr data");

	return arvr_data->ovr_mobile_session->get_transform_for_eye(p_eye, p_cam_transform);
}

void godot_arvr_fill_projection_for_eye(void *p_data, godot_real *p_projection,
		godot_int p_eye, godot_real p_aspect,
		godot_real p_z_near,
		godot_real p_z_far) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	ALOG_ASSERT(arvr_data != nullptr, "Invalid arvr data");

	arvr_data->ovr_mobile_session->fill_projection_for_eye(p_projection, p_eye, p_aspect, p_z_near, p_z_far);
}

godot_int godot_arvr_get_external_texture_for_eye(void *p_data, godot_int p_eye) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	ALOG_ASSERT(arvr_data != nullptr, "Invalid arvr data.");
	return arvr_data->ovr_mobile_session->get_texture_for_eye(p_eye);
}

void godot_arvr_commit_for_eye(void *p_data, godot_int p_eye,
		godot_rid *p_render_target,
		godot_rect2 *p_screen_rect) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	ALOG_ASSERT(arvr_data != nullptr, "Invalid arvr data.");
	ALOG_ASSERT(p_eye != /* EYE_MONO */ 0, "Mono rendering is not supported.");

	arvr_data->ovr_mobile_session->commit_for_eye(p_eye);
}

void godot_arvr_process(void *p_data) {
	auto *arvr_data = (arvr_data_struct *)p_data;
	ALOG_ASSERT(arvr_data != nullptr, "Invalid arvr data.");
	arvr_data->ovr_mobile_session->process();
}

void *godot_arvr_constructor(godot_object *p_instance) {
	auto *arvr_data =
			(arvr_data_struct *)godot::api->godot_alloc(sizeof(arvr_data_struct));

	ALOGV("Creating OVR Mobile session.");

	arvr_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();

	return arvr_data;
};

void godot_arvr_destructor(void *p_data) {
	if (p_data != nullptr) {
		auto *arvr_data = (arvr_data_struct *)p_data;
		ovrmobile::OvrMobileSession::delete_singleton_instance();
		godot::api->godot_free(p_data);
	}
}
