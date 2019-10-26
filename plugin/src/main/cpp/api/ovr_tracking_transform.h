////////////////////////////////////////////////////////////////////////////////////////////////
// This implements the <Tracking Transform> section of the Oculus api.

#ifndef OVR_TRACKING_TRANSFORM_H
#define OVR_TRACKING_TRANSFORM_H

#include "ovr_mobile_session.h"

namespace ovrmobile {

    constexpr int kInvalidOvrTrackingSpace = -1;

    // implements VrApi.h: ovrTrackingSpace vrapi_GetTrackingSpace( ovrMobile * ovr );
    int get_tracking_space(OvrMobileSession *session);

    // implements VrApi.h: ovrResult vrapi_SetTrackingSpace( ovrMobile * ovr, ovrTrackingSpace whichSpace );
    bool set_tracking_space(OvrMobileSession *session, int tracking_space);

// implements VrApi.h: ovrPosef vrapi_LocateTrackingSpace( ovrMobile * ovr, ovrTrackingSpace target );
// not yet implemented

} // namespace ovrmobile

#endif // OVR_TRACKING_TRANSFORM_H
