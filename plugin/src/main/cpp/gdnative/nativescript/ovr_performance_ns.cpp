#include "ovr_performance_ns.h"
#include "nativescript_common.h"
#include <vector>
#include "api/ovr_performance.h"

static const char *kClassName = "OvrPerformance";

void register_gdnative_performance(void *handle) {
    // register the constructor and destructor of the OvrRuntimeConfig class for use in GDScript
    godot_instance_create_func create = {nullptr, nullptr, nullptr};
    create.create_func = &ovr_performance_constructor;

    godot_instance_destroy_func destroy = {nullptr, nullptr, nullptr};
    destroy.destroy_func = &ovr_performance_destructor;

    nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

    // Register all the functions that we want to expose via the OvrRuntimeConfig class in GDScript
    godot_instance_method method = { nullptr, nullptr, nullptr };
    godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

    // Performance
    method.method = &set_clock_levels;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_clock_levels", attributes, method);

    method.method = &set_extra_latency_mode;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_extra_latency_mode", attributes, method);

    method.method = &set_foveation_level;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_foveation_level", attributes, method);

	method.method = &set_enable_dynamic_foveation;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_enable_dynamic_foveation", attributes, method);

    method.method = &set_swap_interval;
    nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_swap_interval", attributes, method);
}

GDCALLINGCONV void *ovr_performance_constructor(godot_object *instance, void *method_data) {
    return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_performance_destructor(godot_object *instance, void *method_data,
											  void *user_data) {
    if (user_data) {
        reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
    }
}

GDCALLINGCONV godot_variant set_clock_levels(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_USER_DATA(
	        int cpu_level = api->godot_variant_as_int(p_args[0]);
	        int gpu_level = api->godot_variant_as_int(p_args[1]);
	        api->godot_variant_new_bool(&ret, ovrmobile::set_clock_levels(ovr_mobile_session, cpu_level, gpu_level));
	)
}

GDCALLINGCONV godot_variant set_extra_latency_mode(godot_object*, void*, void *p_user_data, int, godot_variant **p_args) {
	CHECK_USER_DATA(
	       int latency_mode = api->godot_variant_as_int(p_args[0]);
	       api->godot_variant_new_bool(&ret, ovrmobile::set_extra_latency_mode(ovr_mobile_session, latency_mode));
	)
}

GDCALLINGCONV godot_variant set_foveation_level(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_USER_DATA(
			int foveation_level = api->godot_variant_as_int(p_args[0]);
			api->godot_variant_new_bool(&ret, ovrmobile::set_foveation_level(ovr_mobile_session, foveation_level));
	)
}

GDCALLINGCONV godot_variant set_enable_dynamic_foveation(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		if (p_num_args != 1) {
			ALOGW("set_enable_dynamic_foveation(enabled) requires 1 parameter; got %d", p_num_args);
		} else {
			// Check if foveation is available.
			int foveation_available = vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
			if (foveation_available == VRAPI_TRUE) {
				// Retrieve if set enable or disable
				bool enable_dynamic_foveation = api->godot_variant_as_bool(p_args[0]);
				bool dynamic_foveation_valid = false;
				if (ovrmobile::is_oculus_go_device(ovr_java)) {
					dynamic_foveation_valid = false;
				} else if (ovrmobile::is_oculus_quest_device(ovr_java)) {
					dynamic_foveation_valid = true;
				}

				if (dynamic_foveation_valid) {
					vrapi_SetPropertyInt(ovr_java, VRAPI_DYNAMIC_FOVEATION_ENABLED, enable_dynamic_foveation);
				}
				api->godot_variant_new_bool(&ret, dynamic_foveation_valid);
			}
		}
	)
}

GDCALLINGCONV godot_variant set_swap_interval(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_USER_DATA(
	        unsigned int swap_interval = api->godot_variant_as_uint(p_args[0]);
	        api->godot_variant_new_bool(&ret, ovrmobile::set_swap_interval(ovr_mobile_session, swap_interval));
	)
}
