#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_PERFORMANCE_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_PERFORMANCE_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
namespace {
using namespace godot;
}

/// Implements VrApi.h: ovrResult vrapi_SetClockLevels( ovrMobile * ovr, const int32_t cpuLevel,
/// const int32_t gpuLevel );
bool set_clock_levels(OvrMobileSession *session, int cpu_level, int gpu_level);

/// Implements VrApi.h ovrResult vrapi_SetExtraLatencyMode( ovrMobile * ovr, const
/// ovrExtraLatencyMode mode ); Valid int values for the latency mode are defined by
/// ovrExtraLatencyMode enum in VrApi_Types.h
bool set_extra_latency_mode(OvrMobileSession *session, ovrExtraLatencyMode latency_mode);

/// Set the fixed foveated rendering level if it's available.
/// Returns true if it's available and the given level is valid, false otherwise.
/// For additional information, check the following docs:
/// https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
bool set_foveation_level(OvrMobileSession *session, int foveation_level);

/// Sets the swap interval to control the application frame timing.
/// See
/// https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-vrapi#frame-timing
bool set_swap_interval(OvrMobileSession *session, unsigned int swap_interval);

/// Enable dynamic foveation.
/// See https://developer.oculus.com/documentation/native/android/mobile-ffr/
bool set_enable_dynamic_foveation(OvrMobileSession *session, bool enable);

/// Implements the <Performance> section of the Oculus runtime api.
class OvrPerformance : public Reference {
    GODOT_CLASS(OvrPerformance, Reference)

 public:
    OvrPerformance();

    ~OvrPerformance();

    static void _register_methods();

    void _init();

 private:
    inline bool set_clock_levels(int cpu_level, int gpu_level) {
        return ovrmobile::set_clock_levels(
                OvrMobileSession::get_singleton_instance(), cpu_level, gpu_level);
    }

    inline bool set_extra_latency_mode(int latency_mode) {
        return ovrmobile::set_extra_latency_mode(OvrMobileSession::get_singleton_instance(),
                                                 static_cast<ovrExtraLatencyMode>(latency_mode));
    }

    inline bool set_foveation_level(int foveation_level) {
        return ovrmobile::set_foveation_level(OvrMobileSession::get_singleton_instance(),
                                              foveation_level);
    }

    inline bool set_swap_interval(unsigned int swap_interval) {
        return ovrmobile::set_swap_interval(OvrMobileSession::get_singleton_instance(),
                                            swap_interval);
    }

    inline bool set_enable_dynamic_foveation(bool enable) {
        return ovrmobile::set_enable_dynamic_foveation(OvrMobileSession::get_singleton_instance(),
                                                       enable);
    }
};

} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_PERFORMANCE_H
