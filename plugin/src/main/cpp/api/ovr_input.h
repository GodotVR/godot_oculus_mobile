#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
namespace {
using namespace godot;
}

class OvrInput : public Reference {
    GODOT_CLASS(OvrInput, Reference)

 public:
    OvrInput();

    ~OvrInput();

    static void _register_methods();

    void _init();

    int get_primary_controller_id();
};

/// Vibrate the controller matching the given controller ID.
/// Returns true if the controller was vibrated, false otherwise.
bool vibrate_controller(OvrMobileSession *session,
                        int controller_id,
                        int duration_in_ms,
                        float intensity);

/// Return the id for the primary controller.
int get_primary_controller_id(OvrMobileSession *session);
} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H
