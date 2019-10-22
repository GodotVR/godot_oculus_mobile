#ifndef OVR_INPUT_H
#define OVR_INPUT_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
    bool vibrate_controller(OvrMobileSession *session, int controller_id, float intensity);
} // namespace ovrmobile

#endif // OVR_INPUT_H
