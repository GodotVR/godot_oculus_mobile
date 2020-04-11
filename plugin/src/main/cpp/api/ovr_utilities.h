////////////////////////////////////////////////////////////////////////////////////////////////
// Vrapi utility functions

#ifndef OVR_UTILITIES_H
#define OVR_UTILITIES_H

#include <gen/Node.hpp>
#include <gen/Spatial.hpp>
#include <core/String.hpp>
#include "ovr_mobile_session.h"

namespace ovrmobile {

// uses the internal left and right view matrix to compute the IPD. Returns a float
    float get_ipd(OvrMobileSession *session);

    float get_distance_from_head(const godot::String& head_node_path,
                             const godot::String& to_node_path);

    godot::Node* get_node(const godot::String &node_path);

    godot::Spatial* get_spatial_node(const godot::String &node_path);

// Sets the color multiplier for the default layer used by the VrAPI compositor
    bool set_default_layer_color_scale(OvrMobileSession *session,
                                       float red,
                                       float green,
                                       float blue,
                                       float alpha);

    ovrVector3f get_controller_angular_velocity(OvrMobileSession *session, int controller_id);
    ovrVector3f get_controller_linear_velocity(OvrMobileSession* session, int controller_id);
    ovrVector3f get_controller_angular_acceleration(OvrMobileSession* session, int controller_id);
    ovrVector3f get_controller_linear_acceleration(OvrMobileSession* session, int controller_id);

    ovrVector3f get_head_angular_velocity(OvrMobileSession *session);
    ovrVector3f get_head_linear_velocity(OvrMobileSession *session);
    ovrVector3f get_head_angular_acceleration(OvrMobileSession *session);
    ovrVector3f get_head_linear_acceleration(OvrMobileSession *session);

} // namespace ovrmobile

#endif // OVR_UTILITIES_H
