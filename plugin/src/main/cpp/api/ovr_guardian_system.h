////////////////////////////////////////////////////////////////////////////////////////////////
// This implements the <Guardian System> section of the Oculus runtime api.

#ifndef OVR_GUARDIAN_SYSTEM_H
#define OVR_GUARDIAN_SYSTEM_H

#include "ovr_mobile_session.h"

namespace ovrmobile {

// implements VrApi.h: ovrResult vrapi_GetBoundaryGeometry( ovrMobile * ovr, const uint32_t pointsCountInput, uint32_t * pointsCountOutput, ovrVector3f * points );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryOrientedBoundingBox( ovrMobile * ovr, ovrPosef * pose, ovrVector3f * scale );
// TODO(m4gr3d): Resolve before submitting.
// godot_variant get_boundary_oriented_bounding_box(OvrMobileSession* ovr_mobile_session);

// implements VrApi.h: ovrResult vrapi_TestPointIsInBoundary( ovrMobile * ovr, const ovrVector3f point, bool * pointInsideBoundary, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_GetBoundaryTriggerState( ovrMobile * ovr, const ovrTrackedDeviceTypeId deviceId, ovrBoundaryTriggerResult * result );
// not yet implemented

// implements VrApi.h: ovrResult vrapi_RequestBoundaryVisible( ovrMobile * ovr, const bool visible );
    bool request_boundary_visible(OvrMobileSession *ovr_mobile_session, bool visible);

//ovrResult vrapi_GetBoundaryVisible( ovrMobile * ovr, bool * visible );
    bool get_boundary_visible(OvrMobileSession *ovr_mobile_session);

} // namespace ovrmobile

#endif // OVR_GUARDIAN_SYSTEM_H
