#include "ovr_runtime_config.h"
#include "config_common.h"
#include <vector>

/*
    To avoid code duplication and have consistent error handling this define is used in each function to check
    for use data and instance in each function the inner _codeblock_ contains the actual implementation and
    needs to set the variable 'ret' correctly on success
*/
#undef CHECK_OVR
#define CHECK_OVR(_codeblock_) \
	godot_variant ret; \
	 if (p_user_data != NULL) { \
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data; \
		ovrmobile::OvrMobileSession *ovr_mobile_session = ovr_config_data->ovr_mobile_session; \
		if (ovr_mobile_session && ovr_mobile_session->is_initialized()) { \
			ovrMobile* ovr = ovr_mobile_session->get_ovr_mobile_context(); \
			const ovrJava* ovr_java = ovr_mobile_session->get_ovr_java(); \
			_codeblock_ \
		} \
	 } \
	 return ret;


static const char *kClassName = "OvrRuntimeConfig";

void register_gdnative_runtime_config(void *handle) {
    // register the constructor and destructor of the OvrRuntimeConfig class for use in GDScript
    godot_instance_create_func create = {nullptr, nullptr, nullptr};
    create.create_func = &ovr_runtime_config_constructor;

    godot_instance_destroy_func destroy = {nullptr, nullptr, nullptr};
    destroy.destroy_func = &ovr_runtime_config_destructor;

    nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

    // Register all the functions that we want to expose via the OvrRuntimeConfig class in GDScript
    godot_instance_method method = { nullptr, nullptr, nullptr };
    godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

    // Display refresh rates
    method.method = &get_supported_display_refresh_rates;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "get_supported_display_refresh_rates", attributes, method);

    method.method = &set_display_refresh_rate;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_display_refresh_rate", attributes, method);

    // Guardian System
    method.method = &request_boundary_visible;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "request_boundary_visible", attributes, method);

    method.method = &get_boundary_visible;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "get_boundary_visible", attributes, method);

    method.method = &get_boundary_oriented_bounding_box;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "get_boundary_oriented_bounding_box", attributes, method);

    // Tracking transform
    method.method = &get_tracking_space;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "get_tracking_space", attributes, method);

    method.method = &set_tracking_space;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_tracking_space", attributes, method);

    // Performance
    method.method = &set_clock_levels;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_clock_levels", attributes, method);

    method.method = &set_extra_latency_mode;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_extra_latency_mode", attributes, method);

    method.method = &set_foveation_level;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_foveation_level", attributes, method);

    method.method = &set_swap_interval;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_swap_interval", attributes, method);
}

GDCALLINGCONV void *ovr_runtime_config_constructor(godot_object*, void*) {
    return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_runtime_config_destructor(godot_object*, void*, void *user_data) {
    if (user_data) {
        reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
    }
}

//-----------------------------------------------------------------
// Display Refresh Rate
//-----------------------------------------------------------------

GDCALLINGCONV godot_variant get_supported_display_refresh_rates(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args) {
    CHECK_OVR(
            const int refresh_rates_count = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_NUM_SUPPORTED_DISPLAY_REFRESH_RATES);
            std::vector<float> supported_refresh_rates(refresh_rates_count, 0.0F);
            vrapi_GetSystemPropertyFloatArray(ovr_java, VRAPI_SYS_PROP_SUPPORTED_DISPLAY_REFRESH_RATES, supported_refresh_rates.data(), refresh_rates_count);

            godot_array gd_return_array;
            api->godot_array_new(&gd_return_array);

            for (int i = 0; i < refresh_rates_count; i++) {
                godot_variant refresh_rate;
                api->godot_variant_new_real(&refresh_rate, supported_refresh_rates[i]);
                api->godot_array_push_back(&gd_return_array, &refresh_rate);
                api->godot_variant_destroy(&refresh_rate);
            }

            api->godot_variant_new_array(&ret, &gd_return_array);
            api->godot_array_destroy(&gd_return_array);

    )
}

GDCALLINGCONV godot_variant set_display_refresh_rate(godot_object *instance, void *method_data, void *p_user_data, int num_args, godot_variant **args) {
    CHECK_OVR(
            const double refresh_rate = api->godot_variant_as_real(args[0]);
            ovrResult result = vrapi_SetDisplayRefreshRate(ovr, refresh_rate);
            if (result == ovrSuccess) {
                api->godot_variant_new_bool(&ret, true);
            }

    )
}

//-----------------------------------------------------------------
// Guardian System
//
//-----------------------------------------------------------------

GDCALLINGCONV godot_variant request_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
            bool visible = api->godot_variant_as_bool(p_args[0]);
            ovrResult result = vrapi_RequestBoundaryVisible(ovr, visible);
            if (result == ovrSuccess) api->godot_variant_new_bool(&ret, true); // set the return value to true if vrapi was called successfully
    )
}

GDCALLINGCONV godot_variant get_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
            bool visible = false;
            vrapi_GetBoundaryVisible(ovr, &visible);
            api->godot_variant_new_bool(&ret, visible);
    )
}


GDCALLINGCONV godot_variant get_boundary_oriented_bounding_box(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
            ovrPosef pose;
            ovrVector3f scale;
            if (vrapi_GetBoundaryOrientedBoundingBox(ovr, &pose, &scale) == ovrSuccess) {
                godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
                godot_transform gd_transform;
                godot_vector3 gd_scale;
                ovrmobile::godot_transform_from_ovr_pose(&gd_transform, pose, world_scale);
                api->godot_vector3_new(&gd_scale, scale.x * world_scale, scale.y * world_scale, scale.z * world_scale);

                godot_variant vTransform;
                godot_variant vScale;
                api->godot_variant_new_transform(&vTransform, &gd_transform);
                api->godot_variant_new_vector3(&vScale, &gd_scale);

                godot_array gd_returnArray; // for now we return the transform and scale in a godot array; maybe and Area with a BoxShape would be nice?
                api->godot_array_new(&gd_returnArray);

                api->godot_array_push_back(&gd_returnArray, &vTransform);
                api->godot_array_push_back(&gd_returnArray, &vScale);
                api->godot_variant_destroy(&vTransform);
                api->godot_variant_destroy(&vScale);

                api->godot_variant_new_array(&ret, &gd_returnArray); // set the return value to be the constructed array
                api->godot_array_destroy(&gd_returnArray);
            }
    )
}

//-----------------------------------------------------------------
// Tracking Transform
//
//-----------------------------------------------------------------

GDCALLINGCONV godot_variant get_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
            ovrTrackingSpace space = vrapi_GetTrackingSpace(ovr);
            api->godot_variant_new_int(&ret, space);
    )
}

GDCALLINGCONV godot_variant set_tracking_space(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
    CHECK_OVR(
            ovrTrackingSpace space = (ovrTrackingSpace)api->godot_variant_as_int(p_args[0]); // note that ovrTrackingSpace is an enum in VrApi.h
            ovrResult result = vrapi_SetTrackingSpace(ovr, space);
            if (result == ovrSuccess) api->godot_variant_new_bool(&ret, true); // set the return value to true if vrapi was called successfully
    )
}

//-----------------------------------------------------------------
// Performance
//-----------------------------------------------------------------

GDCALLINGCONV godot_variant set_clock_levels(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	        int cpu_level = api->godot_variant_as_int(p_args[0]);
	        int gpu_level = api->godot_variant_as_int(p_args[1]);
	        ovrResult result = vrapi_SetClockLevels(ovr, cpu_level, gpu_level);
	        if (result == ovrSuccess) {
	            api->godot_variant_new_bool(&ret, true);
	        }

	)
}

GDCALLINGCONV godot_variant set_extra_latency_mode(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	       int latency_mode = api->godot_variant_as_int(p_args[0]);
	       ovrResult result = vrapi_SetExtraLatencyMode(ovr,
	               static_cast<ovrExtraLatencyMode>(latency_mode));
	       if (result == ovrSuccess) {
	           api->godot_variant_new_bool(&ret, true);
	       }

	)
}

GDCALLINGCONV godot_variant set_foveation_level(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
			// Check if foveation is available.
			int foveation_available = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
			if (foveation_available == VRAPI_TRUE) {
				// Retrieve the foveation level
				int foveation_level = api->godot_variant_as_int(p_args[0]);

				// Validate the foveation level.
				bool foveation_valid = false;
				if (ovrmobile::is_oculus_go_device(ovr_java)) {
				    // Foveation level for the Oculus Go ranges from 0 to 3
				    // See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/
				    foveation_valid = foveation_level >= 0 && foveation_level <= 3;
				} else if (ovrmobile::is_oculus_quest_device(ovr_java)) {
				    // Foveation level for the Oculus Quest ranges from 0 to 4
				    // See // - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
				    foveation_valid = foveation_level >= 0 && foveation_level <= 4;
				}

				if (foveation_valid) {
				    vrapi_SetPropertyInt(ovr_java, VRAPI_FOVEATION_LEVEL, foveation_level);
				}
                api->godot_variant_new_bool(&ret, foveation_valid);
			}

	)
}

GDCALLINGCONV godot_variant set_swap_interval(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_OVR(
	        unsigned int swap_interval = api->godot_variant_as_uint(p_args[0]);
	        if (swap_interval == 1 || swap_interval == 2) {
                ovr_mobile_session->set_swap_interval(swap_interval);
                api->godot_variant_new_bool(&ret, true);
            }

	)
}