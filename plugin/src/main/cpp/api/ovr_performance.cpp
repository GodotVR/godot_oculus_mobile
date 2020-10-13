#include "ovr_performance.h"
#include "api_common.h"
#include <vector>

namespace ovrmobile {

OvrPerformance::OvrPerformance() = default;

OvrPerformance::~OvrPerformance() = default;

void OvrPerformance::_init() {}

void OvrPerformance::_register_methods() {
    register_method("set_clock_levels", &OvrPerformance::set_clock_levels);
    register_method("set_extra_latency_mode", &OvrPerformance::set_extra_latency_mode);
    register_method("set_foveation_level", &OvrPerformance::set_foveation_level);
    register_method("set_swap_interval", &OvrPerformance::set_swap_interval);
    register_method("set_enable_dynamic_foveation", &OvrPerformance::set_enable_dynamic_foveation);
}

bool set_clock_levels(OvrMobileSession *session, int cpu_level, int gpu_level) {
    return check_session_initialized<bool>(session, [&]() {
        return vrapi_SetClockLevels(session->get_ovr_mobile_context(), cpu_level, gpu_level) ==
               ovrSuccess;
    });
}

bool set_extra_latency_mode(OvrMobileSession *session, ovrExtraLatencyMode latency_mode) {
    return check_session_initialized<bool>(session, [&]() {
        return vrapi_SetExtraLatencyMode(session->get_ovr_mobile_context(), latency_mode) ==
               ovrSuccess;
    });
}

bool set_foveation_level(OvrMobileSession *session, int foveation_level) {
    return check_session_initialized<bool>(session, [&]() {
        const ovrJava *ovr_java = session->get_ovr_java();
        // Check if foveation is available.
        int foveation_available =
                vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
        if (foveation_available == VRAPI_TRUE) {
            // Foveation level for the Oculus Quest ranges from 0 to 4
            // See https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
            bool foveation_valid = foveation_level >= 0 && foveation_level <= 4;

            if (foveation_valid) {
                vrapi_SetPropertyInt(ovr_java, VRAPI_FOVEATION_LEVEL, foveation_level);
            }
            return foveation_valid;
        }
        return false;
    });
}

bool set_swap_interval(OvrMobileSession *session, unsigned int swap_interval) {
    return check_session_initialized<bool>(session, [&]() {
        if (swap_interval == 1 || swap_interval == 2) {
            session->set_swap_interval(swap_interval);
            return true;
        }
        return false;
    });
}

bool set_enable_dynamic_foveation(OvrMobileSession *session, bool enable) {
    return check_session_initialized<bool>(session, [&]() {
        const ovrJava *ovr_java = session->get_ovr_java();
        // Check if foveation is available.
        int foveation_available =
                vrapi_GetSystemPropertyInt(ovr_java, VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
        if (foveation_available == VRAPI_TRUE) {
            vrapi_SetPropertyInt(ovr_java, VRAPI_DYNAMIC_FOVEATION_ENABLED, enable);
            return true;
        }
        return false;
    });
}

} // namespace ovrmobile
