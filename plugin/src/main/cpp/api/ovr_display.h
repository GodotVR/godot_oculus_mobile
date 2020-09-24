#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H

#include "ovr_mobile_session.h"
#include <vector>

namespace ovrmobile {
namespace {
using namespace godot;
}

bool set_display_refresh_rate(OvrMobileSession *session, float refresh_rate);

std::vector<float> get_supported_display_refresh_rates(OvrMobileSession *session);

class OvrDisplay : public Reference {
    GODOT_CLASS(OvrDisplay, Reference)

 public:
    OvrDisplay();

    ~OvrDisplay();

    static void _register_methods();

    void _init();

    /// Utility method to update the device display refresh rate.
    inline bool set_display_refresh_rate(float refresh_rate) {
        return ovrmobile::set_display_refresh_rate(OvrMobileSession::get_singleton_instance(),
                                                   refresh_rate);
    }

    /// Utility method to access the display refresh rates supported by the device.
    inline std::vector<float> get_supported_display_refresh_rates() {
        return ovrmobile::get_supported_display_refresh_rates(
                OvrMobileSession::get_singleton_instance());
    }
};
} // namespace ovrmobile
#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H
