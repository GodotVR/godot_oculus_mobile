#include "api/ovr_guardian_system.h"
#include "ovr_guardian_system_ns.h"

static const char *kClassName = "OvrGuardianSystem";

void register_gdnative_guardian_system(void *p_handle) {
    { // register the constructor and destructor of the OvrGuardianSystem class for use in GDScript
		godot_instance_create_func create = { NULL, NULL, NULL };
		create.create_func = &ovr_guardian_system_constructor;

		godot_instance_destroy_func destroy = { NULL, NULL, NULL };
		destroy.destroy_func = &ovr_guardian_system_destructor;

		godot::nativescript_api->godot_nativescript_register_class(p_handle, kClassName, "Reference", create, destroy);
	}

	{ // now we register all the functions that we want to expose via OvrGuardianSystem class in GDScript; we use as method names the same names as in VrApi.h but without prefix
		godot_instance_method method = { NULL, NULL, NULL };
		godot_method_attributes attributes = { GODOT_METHOD_RPC_MODE_DISABLED };

		method.method = &request_boundary_visible;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "request_boundary_visible", attributes, method);

		method.method = &get_boundary_visible;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_boundary_visible", attributes, method);

		method.method = &get_boundary_geometry;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_boundary_geometry", attributes, method);

		method.method = &get_boundary_oriented_bounding_box;
		godot::nativescript_api->godot_nativescript_register_method(p_handle, kClassName, "get_boundary_oriented_bounding_box", attributes, method);
	}
}


GDCALLINGCONV void *ovr_guardian_system_constructor(godot_object *p_instance, void *p_method_data) {
	ovr_config_data_struct *ovr_config_data;

	ovr_config_data = (ovr_config_data_struct *)godot::api->godot_alloc(sizeof(ovr_config_data_struct));
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
	CHECK_USER_DATA(
	    bool visible = godot::api->godot_variant_as_bool(p_args[0]);
		godot::api->godot_variant_new_bool(&ret, ovrmobile::request_boundary_visible(ovr_mobile_session, visible)); // set the return value to true if vrapi was called successfully
	)
}

GDCALLINGCONV godot_variant get_boundary_visible(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_USER_DATA(
		godot::api->godot_variant_new_bool(&ret, ovrmobile::get_boundary_visible(ovr_mobile_session));
	)	
}

GDCALLINGCONV godot_variant get_boundary_geometry(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		uint32_t pointsCountInput = 0;
		uint32_t pointsCountOutput = 0;

		// Get number of points in geometry
		if (vrapi_GetBoundaryGeometry(ovr, 0, &pointsCountInput, NULL) == ovrSuccess) {
			ovrVector3f* boundaryPoints = (ovrVector3f*)godot::api->godot_alloc(sizeof(ovrVector3f) * pointsCountInput);
			if (vrapi_GetBoundaryGeometry(ovr, pointsCountInput, &pointsCountOutput, boundaryPoints) == ovrSuccess) {
				godot_array gd_returnArray;
				godot::api->godot_array_new(&gd_returnArray);

				godot_real world_scale = godot::arvr_api->godot_arvr_get_worldscale();

				for (uint32_t i = 0; i < pointsCountOutput; i++) {
					godot_vector3 gd_point;
					godot_variant vPoint;
					godot::api->godot_vector3_new(&gd_point, boundaryPoints[i].x * world_scale, boundaryPoints[i].y * world_scale, boundaryPoints[i].z * world_scale);
					godot::api->godot_variant_new_vector3(&vPoint, &gd_point);
					godot::api->godot_array_push_back(&gd_returnArray, &vPoint);
				}

				godot::api->godot_free(boundaryPoints);

				godot::api->godot_variant_new_array(&ret, &gd_returnArray);
			}
		}
	)	
}

GDCALLINGCONV godot_variant get_boundary_oriented_bounding_box(godot_object *p_instance, void *p_method_data, void *p_user_data, int p_num_args, godot_variant **p_args) {
	CHECK_OVR(
		ovrPosef pose;
		ovrVector3f scale;
		if (vrapi_GetBoundaryOrientedBoundingBox(ovr, &pose, &scale) == ovrSuccess) {
			godot_real world_scale = godot::arvr_api->godot_arvr_get_worldscale();
			godot_transform gd_transform;
			godot_vector3 gd_scale;
			ovrmobile::godot_transform_from_ovr_pose(&gd_transform, pose, world_scale);
			godot::api->godot_vector3_new(&gd_scale, scale.x * world_scale, scale.y * world_scale, scale.z * world_scale);

			godot_variant vTransform;
			godot_variant vScale;
			godot::api->godot_variant_new_transform(&vTransform, &gd_transform);
			godot::api->godot_variant_new_vector3(&vScale, &gd_scale);
			
			godot_array gd_returnArray; // for now we return the transform and scale in a godot array; maybe and Area with a BoxShape would be nice?
			godot::api->godot_array_new(&gd_returnArray);

			godot::api->godot_array_push_back(&gd_returnArray, &vTransform);
			godot::api->godot_array_push_back(&gd_returnArray, &vScale);
			godot::api->godot_variant_destroy(&vTransform);
			godot::api->godot_variant_destroy(&vScale);

			godot::api->godot_variant_new_array(&ret, &gd_returnArray); // set the return value to be the constructed array
			godot::api->godot_array_destroy(&gd_returnArray);
		}
	)
}
