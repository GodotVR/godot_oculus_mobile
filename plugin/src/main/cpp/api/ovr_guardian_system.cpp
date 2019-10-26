#include "ovr_guardian_system.h"
#include "api_common.h"

namespace ovrmobile {

    bool request_boundary_visible(OvrMobileSession *ovr_mobile_session, bool visible) {
        return check_session_initialized<bool>(ovr_mobile_session, [&]() {
            return vrapi_RequestBoundaryVisible(ovr_mobile_session->get_ovr_mobile_context(),
                                                visible) == ovrSuccess;
        }, []() {return false; });

    }

    bool get_boundary_visible(OvrMobileSession *ovr_mobile_session) {
        return check_session_initialized<bool>(ovr_mobile_session, [&]() {
            bool visible = false;
            vrapi_GetBoundaryVisible(ovr_mobile_session->get_ovr_mobile_context(), &visible);
            return visible;
        }, [] () { return false; });
    }


    /*godot_variant get_boundary_oriented_bounding_box(OvrMobileSession *ovr_mobile_session) {
        ovrPosef pose;
        ovrVector3f scale;
        if (vrapi_GetBoundaryOrientedBoundingBox(ovr_mobile_session->get_ovr_mobile_context(),
                                                 &pose, &scale) == ovrSuccess) {
            godot_real world_scale = arvr_api->godot_arvr_get_worldscale();
            godot_transform gd_transform;
            godot_vector3 gd_scale;
            ovrmobile::godot_transform_from_ovr_pose(&gd_transform, pose, world_scale);
            api->godot_vector3_new(&gd_scale, scale.x * world_scale, scale.y * world_scale,
                                   scale.z * world_scale);

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

            api->godot_variant_new_array(&ret,
                                         &gd_returnArray); // set the return value to be the constructed array
            api->godot_array_destroy(&gd_returnArray);
        }
    }*/
} // namespace ovrmobile

