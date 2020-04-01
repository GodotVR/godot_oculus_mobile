#include "ovr_performance.h"
#include <vector>

#include "api_common.h"

namespace ovrmobile {

    bool set_clock_levels(OvrMobileSession *session, int cpu_level, int gpu_level) {
        return check_session_initialized<bool>(session, [&]() {
            return vrapi_SetClockLevels(session->get_ovr_mobile_context(), cpu_level, gpu_level) ==
                   ovrSuccess;
        }, []() { return false; });
    }

    bool set_extra_latency_mode(OvrMobileSession *session, int latency_mode) {
        return check_session_initialized<bool>(session, [&]() {
            return vrapi_SetExtraLatencyMode(session->get_ovr_mobile_context(),
                                             static_cast<ovrExtraLatencyMode>(latency_mode)) ==
                   ovrSuccess;
        }, []() { return false; });
    }

    bool set_foveation_level(OvrMobileSession *session, int foveation_level) {
        return check_session_initialized<bool>(session, [&]() {
            const ovrJava *ovr_java = session->get_ovr_java();
            // Check if foveation is available.
            int foveation_available = vrapi_GetSystemPropertyInt(ovr_java,
                                                                 VRAPI_SYS_PROP_FOVEATION_AVAILABLE);
            if (foveation_available == VRAPI_TRUE) {
                // Validate the foveation level.
                bool foveation_valid = false;
                if (ovrmobile::is_oculus_go_device(ovr_java)) {
                    // Foveation level for the Oculus Go ranges from 0 to 3
                    // See https://developer.oculus.com/documentation/mobilesdk/latest/concepts/mobile-ffr/
                    foveation_valid = foveation_level >= 0 && foveation_level <= 3;
                } else if (ovrmobile::is_oculus_quest_device(ovr_java)) {
                    // Foveation level for the Oculus Quest ranges from 0 to 4
                    // See // - Oculus Quest: https://developer.oculus.com/documentation/quest/latest/concepts/mobile-ffr/
                    foveation_valid = foveation_level >= 0 && foveation_level <= 4;
                }

                if (foveation_valid) {
                    vrapi_SetPropertyInt(ovr_java, VRAPI_FOVEATION_LEVEL, foveation_level);
                }
                return foveation_valid;
            }
            return false;
        }, []() { return false; });
    }

    bool set_swap_interval(OvrMobileSession *session, unsigned int swap_interval) {
        return check_session_initialized<bool>(session, [&]() {
            if (swap_interval == 1 || swap_interval == 2) {
                session->set_swap_interval(swap_interval);
                return true;
            }
            return false;
        }, []() { return false; });
    }

} // namespace ovrmobile