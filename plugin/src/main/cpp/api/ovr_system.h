#ifndef GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H
#define GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H

#include "ovr_mobile_session.h"

namespace ovrmobile {
namespace {
using namespace godot;
} // namespace

/// Return true if the current device is a Quest 1.
bool is_oculus_quest_1_device(OvrMobileSession *session);

/// Return true if the current device is a Quest 2.
bool is_oculus_quest_2_device(OvrMobileSession *session);

/// Return the current device type.
ovrDeviceType get_device_type(OvrMobileSession *session);

/// Return the version of the vrapi driver.
String get_driver_version();

class OvrSystem : public Reference {
    GODOT_CLASS(OvrSystem, Reference)

 public:
    OvrSystem();

    ~OvrSystem();

    static void _register_methods();

    void _init();

    inline int get_device_type() {
        return ovrmobile::get_device_type(OvrMobileSession::get_singleton_instance());
    }

    inline bool is_oculus_quest_1_device() {
        return ovrmobile::is_oculus_quest_1_device(OvrMobileSession::get_singleton_instance());
    }

    inline bool is_oculus_quest_2_device() {
        return ovrmobile::is_oculus_quest_2_device(OvrMobileSession::get_singleton_instance());
    }

    inline String get_driver_version() { return ovrmobile::get_driver_version(); }
};
} // namespace ovrmobile

#endif // GODOT_OCULUS_MOBILE_PLUGIN_OVR_SYSTEM_H
