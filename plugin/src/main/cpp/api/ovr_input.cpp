#include "ovr_input.h"
#include "api_common.h"

namespace ovrmobile {

OvrInput::OvrInput() {}

OvrInput::~OvrInput() {}

void OvrInput::_init() {}

void OvrInput::_register_methods() {
    register_method("get_primary_controller_id", &OvrInput::get_primary_controller_id);
    register_method("get_primary_controller_type", &OvrInput::get_primary_controller_type);
    register_method("get_controller_type", &OvrInput::get_controller_type);
}

bool vibrate_controller(OvrMobileSession *session,
                        int controller_id,
                        int duration_in_ms,
                        float intensity) {
    return check_session_initialized<bool>(session, [&]() {
        bool result = false;
        OvrMobileController *controller = session->get_ovr_mobile_controller();
        if (controller) {
            controller->vibrate_controller(controller_id, duration_in_ms, intensity);
            result = true;
        }
        return result;
    });
}

int get_primary_controller_id(OvrMobileSession *session) {
    return check_session_initialized<int>(
            session,
            [&]() {
                int controller_id = kInvalidGodotControllerId;
                OvrMobileController *controller = session->get_ovr_mobile_controller();
                if (controller) {
                    controller_id = controller->get_active_controller_id();
                }
                return controller_id;
            },
            []() { return kInvalidGodotControllerId; });
}

int get_controller_id(OvrMobileSession *session,
                      OvrMobileController::ControllerHand controller_hand) {
    return check_session_initialized<int>(
            session,
            [&]() {
                int controller_id = kInvalidGodotControllerId;
                OvrMobileController *controller = session->get_ovr_mobile_controller();
                if (controller) {
                    controller_id = controller->get_controller_id(controller_hand);
                }
                return controller_id;
            },
            []() { return kInvalidGodotControllerId; });
}

ovrControllerType get_primary_controller_type(OvrMobileSession *session) {
    return check_session_initialized<ovrControllerType>(session, [&]() {
        OvrMobileController *controller = session->get_ovr_mobile_controller();
        if (controller) {
            const OvrMobileController::ControllerState *controller_state =
                    controller->get_controller_state_by_id(kPrimaryControllerId);
            if (controller_state) {
                return controller_state->capability_header.Type;
            }
        }
        return ovrControllerType::ovrControllerType_None;
    });
}

ovrControllerType get_controller_type(OvrMobileSession *session, int controller_id) {
    return check_session_initialized<ovrControllerType>(session, [&]() {
        OvrMobileController *controller = session->get_ovr_mobile_controller();
        if (controller) {
            const OvrMobileController::ControllerState *controller_state =
                    controller->get_controller_state_by_id(controller_id);
            if (controller_state) {
                return controller_state->capability_header.Type;
            }
        }
        return ovrControllerType::ovrControllerType_None;
    });
}
} // namespace ovrmobile
