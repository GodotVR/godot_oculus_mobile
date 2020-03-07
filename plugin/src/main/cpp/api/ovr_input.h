#ifndef OVR_INPUT_H
#define OVR_INPUT_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
// Vibrate the controller matching the given controller ID.
// Returns true if the controller was vibrated, false otherwise.
bool vibrate_controller(OvrMobileSession *session, int controller_id, float intensity);
} // namespace ovrmobile

#endif // OVR_INPUT_H
