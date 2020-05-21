#include "ovr_input.h"
#include "api_common.h"

namespace ovrmobile {
bool vibrate_controller(OvrMobileSession* session,
                        int controller_id,
                        int duration_in_ms,
                        float intensity) {
    return check_session_initialized<bool>(session, [&]() {
      bool result = false;
      OvrMobileController* controller = session->get_ovr_mobile_controller();
      if (controller) {
          controller->vibrate_controller(controller_id, duration_in_ms, intensity);
          result = true;
      }
      return result;
    }, []() { return false; });
}
} // namespace ovrmobile
