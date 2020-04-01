////////////////////////////////////////////////////////////////////////////////////////////////
// Implements the <Display refresh rate> section of the Oculus runtime api.

#ifndef OVR_DISPLAY_REFRESH_RATE_H
#define OVR_DISPLAY_REFRESH_RATE_H

#include <vector>

#include "VrApi_Types.h"
#include "ovr_mobile_session.h"

namespace ovrmobile {
    // Implements VrApi.h: ovrResult vrapi_SetDisplayRefreshRate(ovrMobile * ovr, const float refreshRate);
    bool set_display_refresh_rate(OvrMobileSession *session, float refresh_rate);

    // Utility method to access the display refresh rates supported by the device.
    std::vector<float> get_supported_display_refresh_rates(OvrMobileSession *session);

}  // namespace ovrmobile

#endif // OVR_DISPLAY_REFRESH_RATE_H
