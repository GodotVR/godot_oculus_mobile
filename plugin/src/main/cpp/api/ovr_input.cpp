#include "ovr_input.h"
#include "api_common.h"

namespace ovrmobile {

OvrInput::OvrInput() {}

OvrInput::~OvrInput() {}

void OvrInput::_init() {}

void OvrInput::_register_methods() {
    register_method("get_primary_controller_id", &OvrInput::get_primary_controller_id);
}

int OvrInput::get_primary_controller_id() {
    return ovrmobile::get_primary_controller_id(OvrMobileSession::get_singleton_instance());
}

bool vibrate_controller(OvrMobileSession *session,
                        int controller_id,
                        int duration_in_ms,
                        float intensity) {
    return check_session_initialized<bool>(
            session,
            [&]() {
                bool result = false;
                OvrMobileController *controller = session->get_ovr_mobile_controller();
                if (controller) {
                    controller->vibrate_controller(controller_id, duration_in_ms, intensity);
                    result = true;
                }
                return result;
            },
            []() { return false; });
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
} // namespace ovrmobile
