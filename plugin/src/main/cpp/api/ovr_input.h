#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
namespace {
using namespace godot;
}

/// Vibrate the controller matching the given controller ID.
/// Returns true if the controller was vibrated, false otherwise.
bool vibrate_controller(OvrMobileSession *session,
                        int controller_id,
                        int duration_in_ms,
                        float intensity);

/// Return the id for the primary controller.
int get_primary_controller_id(OvrMobileSession *session);

/// Return the type for the primary controller.
ovrControllerType get_primary_controller_type(OvrMobileSession *session);

class OvrInput : public Reference {
    GODOT_CLASS(OvrInput, Reference)

 public:
    OvrInput();

    ~OvrInput();

    static void _register_methods();

    void _init();

    inline int get_primary_controller_id() {
        return ovrmobile::get_primary_controller_id(OvrMobileSession::get_singleton_instance());
    }

    inline int get_primary_controller_type() {
        return ovrmobile::get_primary_controller_type(OvrMobileSession::get_singleton_instance());
    }
};
} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_INPUT_H
