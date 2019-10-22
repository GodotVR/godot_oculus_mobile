#include "ovr_input.h"
#include "api_common.h"

namespace ovrmobile {
    bool vibrate_controller(OvrMobileSession *session, int controller_id, float intensity) {
        return check_session_initialized<bool>(session, [&]() {
            bool result = false;
            const OvrMobileController *controller = session->get_ovr_mobile_controller();
            if (controller) {
                const OvrMobileController::ControllerState *state = controller->get_controller_state_by_id(
                        controller_id);
                if (state &&
                    OvrMobileController::supports_haptic_vibration(state->remote_capabilities)) {
                    result = vrapi_SetHapticVibrationSimple(session->get_ovr_mobile_context(),
                                                            state->remote_capabilities.Header.DeviceID,
                                                            intensity) == ovrSuccess;
                }
            }
            return result;
        }, []() { return false; });
    }
} // namespace ovrmobile