#include "ovr_display_refresh_rate.h"
#include "config_common.h"
#include <vector>

static const char *kClassName = "OvrDisplayRefreshRate";

void register_gdnative_display_refresh_rate(void *handle) {
	// register the constructor and destructor of the OvrDisplayRefreshRate class for use in GDScript
	godot_instance_create_func create = { NULL, NULL, NULL };
	create.create_func = &ovr_display_refresh_rate_constructor;

	godot_instance_destroy_func destroy = { NULL, NULL, NULL };
	destroy.destroy_func = &ovr_display_refresh_rate_destructor;

	nativescript_api->godot_nativescript_register_class(handle, kClassName, "Reference", create, destroy);

	// register all the functions that we want to expose via the OvrDisplayRefreshRate class in GDScript
	godot_instance_method method = { NULL, NULL, NULL };
	godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

	method.method = &get_supported_display_refresh_rates;
	nativescript_api->godot_nativescript_register_method(handle, kClassName, "get_supported_display_refresh_rates", attributes, method);

	method.method = &set_display_refresh_rate;
	nativescript_api->godot_nativescript_register_method(handle, kClassName, "set_display_refresh_rate", attributes, method);
}

GDCALLINGCONV void *ovr_display_refresh_rate_constructor(godot_object *instance, void *method_data) {
	return init_ovr_config_data_struct();
}

GDCALLINGCONV void ovr_display_refresh_rate_destructor(godot_object *instance, void *method_data, void *user_data) {
	if (user_data) {
		reset_ovr_config_data_struct(static_cast<ovr_config_data_struct *>(user_data));
	}
}

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