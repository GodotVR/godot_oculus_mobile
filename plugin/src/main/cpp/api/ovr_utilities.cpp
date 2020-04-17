#include <gen/Engine.hpp>
#include <gen/MainLoop.hpp>
#include <gen/SceneTree.hpp>
#include <gen/Object.hpp>
#include <core/NodePath.hpp>
#include <gen/Viewport.hpp>
#include <core/Vector3.hpp>
#include "ovr_utilities.h"
#include "api_common.h"
#include "common.h"

namespace ovrmobile {

    float get_ipd(OvrMobileSession *session) {
        return check_session_initialized<float>(session, [&]() {
            ovrTracking2 head_tracker = session->get_head_tracker();

            // here we compute the vector from the origin of the left eye to the right eye by using the transform part of the view matrix
            float dx = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[0][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[0][3];
            float dy = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[1][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[1][3];
            float dz = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[2][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[2][3];

            // the IPD is then just the length of this vector
            float ipd = sqrtf(dx * dx + dy * dy + dz * dz);
            return ipd;
        }, []() { return 0.0F; });
    }

    godot::Node* get_node(const godot::String& node_path) {
        if (node_path.empty()) {
            ALOGE("Invalid node path argument: %s", node_path.utf8().get_data());
            return nullptr;
        }

        godot::NodePath node_path_obj(node_path);
        godot::MainLoop
            * main_loop = godot::Engine::get_singleton()->get_main_loop();
        if (!main_loop || !main_loop->is_class("SceneTree")) {
            ALOGW("Unable to retrieve main loop.");
            return nullptr;
        }

        auto* scene_tree = godot::Object::cast_to<godot::SceneTree>(main_loop);
        godot::Node
            * node = scene_tree->get_root()->get_node_or_null(node_path_obj);
        return node;
    }

    godot::Spatial* get_spatial_node(const godot::String& node_path) {
        godot::Node* node = get_node(node_path);
        if (!node || !node->is_class("Spatial")) {
            ALOGW("Unable to find a Spatial node with path %s",
                  node_path.utf8().get_data());
            return nullptr;
        }

        auto* spatial_node = godot::Object::cast_to<godot::Spatial>(node);
        return spatial_node;
    }

    float get_distance_from_head(const godot::String& head_node_path,
                                 const godot::String& to_node_path) {
        float distance = -1.0f;
        godot::Spatial* head_node = get_spatial_node(head_node_path);
        if (!head_node) {
            ALOGW("Unable to retrieve head with path %s", head_node_path.utf8().get_data());
            return distance;
        }

        godot::Spatial* to_node = get_spatial_node(to_node_path);
        if (!to_node) {
            ALOGW("Unable to retrieve node with path %s", to_node_path.utf8().get_data());
            return distance;
        }

        godot::Vector3 head_global_translation = head_node->to_global(head_node->get_translation());
        godot::Vector3 to_global_translation = to_node->to_global(to_node->get_translation());
        return head_global_translation.distance_to(to_global_translation);
    }

    bool set_default_layer_color_scale(OvrMobileSession *session,
                                       float red,
                                       float green,
                                       float blue,
                                       float alpha) {
        return check_session_initialized<bool>(session, [&]() {
            session->set_default_layer_color_scale(red, green, blue, alpha);
            return true;
        }, []() { return false; });
    }

    typedef ovrVector3f (*get_pose_properties)(const ovrRigidBodyPosef&);

    ovrVector3f get_controller_pose_properties(OvrMobileSession *session, int controller_id,
                                               get_pose_properties get_func) {
        return check_session_initialized<ovrVector3f>(session, [&]() {
            ovrVector3f scaled_property = {};
            const OvrMobileController* controller = session->get_ovr_mobile_controller();
            if (controller) {
                const OvrMobileController::ControllerState *state = controller->get_controller_state_by_id(
                        controller_id);
                if (state) {
                    float world_scale = godot::arvr_api->godot_arvr_get_worldscale();
                    ovrVector3f property = get_func(state->tracking_state.HeadPose);
                    scaled_property = {property.x * world_scale,
                                       property.y * world_scale,
                                       property.z * world_scale};
                }
            }
            return scaled_property;
        }, []() { return ovrVector3f(); });
    }

    ovrVector3f get_head_pose_properties(OvrMobileSession* session, get_pose_properties get_func) {
        return check_session_initialized<ovrVector3f>(session, [&]() {
            ovrTracking2 head_tracker = session->get_head_tracker();
            float world_scale = godot::arvr_api->godot_arvr_get_worldscale();
            ovrVector3f property = get_func(head_tracker.HeadPose);
            ovrVector3f scaled_property = {property.x * world_scale,
                                           property.y * world_scale,
                                           property.z * world_scale};
            return scaled_property;
        }, []() { return ovrVector3f(); });
    }

    ovrVector3f get_controller_angular_velocity(OvrMobileSession *session, int controller_id) {
        return get_controller_pose_properties(session, controller_id,
                                              [](const ovrRigidBodyPosef &head_pose) {
                                                  return head_pose.AngularVelocity;
                                              });
    }

    ovrVector3f get_controller_linear_velocity(OvrMobileSession *session, int controller_id) {
        return get_controller_pose_properties(session, controller_id,
                                              [](const ovrRigidBodyPosef &head_pose) {
                                                  return head_pose.LinearVelocity;
                                              });
    }

    ovrVector3f get_controller_angular_acceleration(OvrMobileSession* session, int controller_id) {
        return get_controller_pose_properties(session, controller_id,
                                              [](const ovrRigidBodyPosef &head_pose) {
                                                  return head_pose.AngularAcceleration;
                                              });
    }

    ovrVector3f get_controller_linear_acceleration(OvrMobileSession* session, int controller_id) {
        return get_controller_pose_properties(session, controller_id,
                                              [](const ovrRigidBodyPosef &head_pose) {
                                                  return head_pose.LinearAcceleration;
                                              });
    }

    ovrVector3f get_head_angular_acceleration(OvrMobileSession *session) {
        return get_head_pose_properties(session, [](const ovrRigidBodyPosef &head_pose) {
            return head_pose.AngularAcceleration;
        });
    }

    ovrVector3f get_head_angular_velocity(OvrMobileSession *session) {
        return get_head_pose_properties(session, [](const ovrRigidBodyPosef &head_pose) {
            return head_pose.AngularVelocity;
        });
    }

    ovrVector3f get_head_linear_acceleration(OvrMobileSession *session) {
        return get_head_pose_properties(session, [](const ovrRigidBodyPosef &head_pose) {
            return head_pose.LinearAcceleration;
        });
    }

    ovrVector3f get_head_linear_velocity(OvrMobileSession *session) {
        return get_head_pose_properties(session, [](const ovrRigidBodyPosef &head_pose) {
            return head_pose.LinearVelocity;
        });
    }

} // namespace ovrmobile
