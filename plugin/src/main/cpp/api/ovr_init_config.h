////////////////////////////////////////////////////////////////////////////////////////////////
// Used to access and setup the init parameters for the plugin.
// The methods defined in this class must be invoked prior to initializing the Oculus mobile plugin.

#ifndef OVR_INIT_CONFIG_H
#define OVR_INIT_CONFIG_H

#include "ovr_mobile_session.h"

namespace ovrmobile {

    // Set the factor by which to multiply the recommended render target size for the app.
    bool set_render_target_size_multiplier(OvrMobileSession *ovr_mobile_session, double multiplier);

} // namespace ovrmobile

#endif // OVR_INIT_CONFIG_H
