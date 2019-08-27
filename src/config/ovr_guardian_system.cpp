#include "config_common.h"
#include "ovr_guardian_system.h"


void register_gdnative_guardian_system(void *p_handle) {
    { // register the constructor and destructor of the OvrGuardianSystem class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_guardian_system_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_guardian_system_destructor;

		nativescript_api->godot_nativescript_register_class(p_handle, "OvrGuardianSystem", "Reference", create, destroy);
	}

	{ // now we register all the functions that we want to expose via OvrGuardianSystem class in GDScript; we use as method names the same names as in VrApi.h but without prefix
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &request_boundary_visible;
		nativescript_api->godot_nativescript_register_method(p_handle, "OvrGuardianSystem", "request_boundary_visible", attributes, method);

		method.method = &get_boundary_visible;
		nativescript_api->godot_nativescript_register_method(p_handle, "OvrGuardianSystem", "get_boundary_visible", attributes, method);

		method.method = &get_boundary_oriented_bounding_box;
		nativescript_api->godot_nativescript_register_method(p_handle, "OvrGuardianSystem", "get_boundary_oriented_bounding_box", attributes, method);
	}
}


GDCALLINGCONV void *ovr_guardian_system_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)api->godot_alloc(sizeof(ovr_config_data_struct));
	if (ovr_config_data != NULL) {
		ovr_config_data->ovr_mobile_session = ovrmobile::OvrMobileSession::get_singleton_instance();
	}

	return ovr_config_data;
}


GDCALLINGCONV void ovr_guardian_system_destructor(godot_object *p_instance, void *p_method_data, void *p_user_data) {
	if (p_user_data != NULL) {
		ovr_config_data_struct *ovr_config_data = (ovr_config_data_struct *) p_user_data;
		if (ovr_config_data->ovr_mobile_session != NULL) {
			ovr_config_data->ovr_mobile_session = NULL;
		}
	}
}


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
