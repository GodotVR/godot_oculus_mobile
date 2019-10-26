////////////////////////////////////////////////////////////////////////////////////////////////
// Vrapi utility functions

#ifndef OVR_UTILITIES_H
#define OVR_UTILITIES_H

#include "ovr_mobile_session.h"

namespace ovrmobile {

// uses the internal left and right view matrix to compute the IPD. Returns a float
    float get_ipd(OvrMobileSession *session);

// Sets the color multiplier for the default layer used by the VrAPI compositor
    bool set_default_layer_color_scale(OvrMobileSession *session,
                                       float red,
                                       float green,
                                       float blue,
                                       float alpha);

} // namespace ovrmobile

#endif // OVR_UTILITIES_H
