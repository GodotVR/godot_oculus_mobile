////////////////////////////////////////////////////////////////////////////////////////////////
// Implements the <Performance> section of the Oculus runtime api.

#ifndef OVR_PERFORMANCE_H
#define OVR_PERFORMANCE_H

#include "ovr_mobile_session.h"

namespace ovrmobile {

    // implements VrApi.h: ovrResult vrapi_SetClockLevels( ovrMobile * ovr, const int32_t cpuLevel, const int32_t gpuLevel );
    bool set_clock_levels(OvrMobileSession *session, int cpu_level, int gpu_level);

// implements VrApi.h ovrResult vrapi_SetExtraLatencyMode( ovrMobile * ovr, const ovrExtraLatencyMode mode );
// Valid int values for the latency mode are defined by ovrExtraLatencyMode enum in VrApi_Types.h
    bool set_extra_latency_mode(OvrMobileSession *session, int latency_mode);

// Set the fixed foveated rendering level if it's available.
// Returns true if it's available and the given level is valid, false otherwise.
// For additional information, check the following docs:
// - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
// - Oculus Go: https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/
    bool set_foveation_level(OvrMobileSession *session, int foveation_level);

// Sets the swap interval to control the application frame timing.
// See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing for additional background.
    bool set_swap_interval(OvrMobileSession *session, unsigned int swap_interval);

} // namespace ovrmobile

#endif // OVR_PERFORMANCE_H
