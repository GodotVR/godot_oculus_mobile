#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H

#include "ovr_mobile_session.h"
#include <core/Array.hpp>
#include <vector>

namespace ovrmobile {
namespace {
using namespace godot;
}

/// Utility method to update the device color space
/// For more info, see https://developer.oculus.com/documentation/native/android/mobile-colorspace/
bool set_color_space(OvrMobileSession *session, ovrColorSpace color_space);

/// Utility method to retrieve the device color space.
/// This is a constant for each device type.
/// See https://developer.oculus.com/documentation/native/android/mobile-colorspace/
ovrColorSpace get_color_space(OvrMobileSession *session);

/// Utility method to update the device display refresh rate.
bool set_display_refresh_rate(OvrMobileSession *session, float refresh_rate);

/// Utility method to access the display refresh rates supported by the device.
std::vector<float> get_supported_display_refresh_rates(OvrMobileSession *session);

class OvrDisplay : public Reference {
    GODOT_CLASS(OvrDisplay, Reference)

 public:
    OvrDisplay();

    ~OvrDisplay();

    static void _register_methods();

    void _init();

 private:
    inline bool set_color_space(uint color_space) {
        return ovrmobile::set_color_space(OvrMobileSession::get_singleton_instance(),
                                          static_cast<ovrColorSpace>(color_space));
    }

    inline uint get_color_space() {
        return ovrmobile::get_color_space(OvrMobileSession::get_singleton_instance());
    }

    inline bool set_display_refresh_rate(float refresh_rate) {
        return ovrmobile::set_display_refresh_rate(OvrMobileSession::get_singleton_instance(),
                                                   refresh_rate);
    }

    inline Array get_supported_display_refresh_rates() {
        std::vector<float> refresh_rates = ovrmobile::get_supported_display_refresh_rates(
                OvrMobileSession::get_singleton_instance());
        Array refresh_rates_array;
        for (int i = 0; i < refresh_rates.size(); i++) {
            refresh_rates_array.append(refresh_rates[i]);
        }
        return refresh_rates_array;
    }
};
} // namespace ovrmobile
#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_DISPLAY_H
