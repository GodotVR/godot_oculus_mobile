#include "ovr_utilities.h"
#include "api_common.h"

namespace ovrmobile {

    float get_ipd(OvrMobileSession *session) {
        return check_session_initialized<float>(session, [&]() {
            ovrTracking2 head_tracker = session->get_head_tracker();

            // here we compute the vector from the origin of the left eye to the right eye by using the transform part of the view matrix
            float dx = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[0][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[0][3];
            float dy = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[1][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[1][3];
            float dz = head_tracker.Eye[VRAPI_EYE_RIGHT].ViewMatrix.M[2][3] -
                       head_tracker.Eye[VRAPI_EYE_LEFT].ViewMatrix.M[2][3];

            // the IPD is then just the length of this vector
            float ipd = sqrtf(dx * dx + dy * dy + dz * dz);
            return ipd;
        }, []() { return 0.0F; });
    }

    bool set_default_layer_color_scale(OvrMobileSession *session,
                                       float red,
                                       float green,
                                       float blue,
                                       float alpha) {
        return check_session_initialized<bool>(session, [&]() {
            session->set_default_layer_color_scale(red, green, blue, alpha);
            return true;
        }, []() { return false; });
    }

} // namespace ovrmobile