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

GDCALLINGCONV godot_variant set_swap_interval(godot_object *, void *, void *p_user_data, int, godot_variant **p_args) {
	CHECK_USER_DATA(
	        unsigned int swap_interval = api->godot_variant_as_uint(p_args[0]);
	        api->godot_variant_new_bool(&ret, ovrmobile::set_swap_interval(ovr_mobile_session, swap_interval));
	)
}
