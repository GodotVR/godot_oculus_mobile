#include "ovr_tracking_transform.h"
#include "api_common.h"

namespace ovrmobile {

    int get_tracking_space(OvrMobileSession *session) {
        return check_session_initialized<int>(session, [&]() {
            int tracking_space = vrapi_GetTrackingSpace(session->get_ovr_mobile_context());
            return tracking_space;
        }, []() { return kInvalidOvrTrackingSpace; });
    }

    bool set_tracking_space(OvrMobileSession *session, int tracking_space) {
        return check_session_initialized<bool>(session, [&]() {
            auto space = static_cast<ovrTrackingSpace>(tracking_space);
            return vrapi_SetTrackingSpace(session->get_ovr_mobile_context(), space) == ovrSuccess;
        }, []() { return false; });

    }

}