#include "api/ovr_init_config.h"
#include "ovr_init_config_ns.h"

static const char *kClassName = "OvrInitConfig";

void register_gdnative_init_config(void *handle) {
    // register the constructor and destructor of the OvrInitConfig class for use in GDScript
    godot_instance_create_func create = { nullptr, nullptr, nullptr};
    create.create_func = &ovr_init_config_constructor;

    godot_instance_destroy_func destroy = {nullptr, nullptr, nullptr};
    destroy.destroy_func = &ovr_init_config_destructor;

    godot::nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

    // register all the functions that we want to expose via the OvrInitConfig class in GDScript
    godot_instance_method method = {nullptr, nullptr, nullptr};
    godot_method_attributes attributes = {GODOT_METHOD_RPC_MODE_DISABLED};

    method.method = &set_render_target_size_multiplier;
    godot::nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_render_target_size_multiplier", attributes, method);
}

GDCALLINGCONV void *ovr_init_config_constructor(godot_object *instance, void *method_data) {
    return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_init_config_destructor(godot_object *instance, void *method_data, void *user_data) {
    if (user_data) {
        reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
    }
}

GDCALLINGCONV godot_variant
set_render_target_size_multiplier(godot_object *, void *, void *p_user_data, int num_args,
                                  godot_variant **args) {
    CHECK_USER_DATA(
            double multiplier = godot::api->godot_variant_as_real(args[0]);
        godot::api->godot_variant_new_bool(&ret, ovrmobile::set_render_target_size_multiplier(
                    ovr_mobile_session, multiplier));
    )
}
