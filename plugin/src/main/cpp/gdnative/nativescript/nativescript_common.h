////////////////////////////////////////////////////////////////
// Common helpers for the config classes implemented in this folder
// to expose part of Oculus VrAPI.h via GDScript classes

#ifndef NATIVESCRIPT_COMMON_H
#define NATIVESCRIPT_COMMON_H

#include "ovr_mobile_session.h"
#include "common.h"

typedef struct ovr_config_data_struct {
	ovrmobile::OvrMobileSession *ovr_mobile_session;
} ovr_config_data_struct;

void *init_ovr_config_data_struct();

void reset_ovr_config_data_struct(ovr_config_data_struct *ovr_config_data);

/*
    To avoid code duplication and have consistent error handling this define is used to check
    for user data. In each function the inner _codeblock_ contains the actual implementation and
    needs to set the variable 'ret' correctly on success
*/
#undef CHECK_USER_DATA
#define CHECK_USER_DATA(_codeblock_) \
	godot_variant ret; \
	godot::api->godot_variant_new_nil(&ret); \
	if (p_user_data != NULL) { \
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data; \
		ovrmobile::OvrMobileSession *ovr_mobile_session = ovr_config_data->ovr_mobile_session; \
		_codeblock_ \
	} \
	return ret;

/*
    To avoid code duplication and have consistent error handling this define is used to check
    for user data and OvrMobileSession instance init status. In each function the inner _codeblock_
    contains the actual implementation and needs to set the variable 'ret' correctly on success
*/
#undef CHECK_OVR
#define CHECK_OVR(_codeblock_) \
	godot_variant ret; \
	godot::api->godot_variant_new_nil(&ret); \
	if (p_user_data != NULL) { \
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data; \
		ovrmobile::OvrMobileSession *ovr_mobile_session = ovr_config_data->ovr_mobile_session; \
		if (ovr_mobile_session && ovr_mobile_session->is_initialized()) { \
			ovrMobile* ovr = ovr_mobile_session->get_ovr_mobile_context(); \
			const ovrJava* ovr_java = ovr_mobile_session->get_ovr_java(); \
			if (ovr && ovr_java) { \
			  _codeblock_ \
			} \
		} \
	} \
	return ret;

#endif // NATIVESCRIPT_COMMON_H