/**
 * Created by Fredia Huya-Kouadio.
 */

#ifndef OVRMOBILE_OVR_MOBILE_CONTROLLER_H
#define OVRMOBILE_OVR_MOBILE_CONTROLLER_H

#include "VrApi.h"
#include "VrApi_Input.h"
#include "VrApi_Types.h"
#include "common.h"
#include <map>

namespace ovrmobile {

namespace {
const int kInvalidGodotControllerId = 0;

const int kPrimaryControllerId = -1;
} // namespace

class OvrMobileController {
 public:
    struct ControllerState {
        bool connected = false;
        // Shows which controller is primary or most 'active'. See VRAPI_ACTIVE_INPUT_DEVICE_ID for
        // reference.
        bool primary = false;
        int godot_controller_id = 0;
        union {
            ovrInputCapabilityHeader capability_header;
            ovrInputTrackedRemoteCapabilities remote_capabilities;
            ovrInputHandCapabilities hand_capabilities;
        };
        union {
            ovrInputStateHeader input_header;
            ovrInputStateHand input_hand;
            ovrInputStateTrackedRemote input_tracked_remote;
        };
        ovrTracking tracking_state;
        ovrHandPose hand_pose;
    };

    enum ControllerHand { LEFT_HAND, RIGHT_HAND, MAX_HANDS };

    OvrMobileController();

    ~OvrMobileController();

    void process(ovrMobile *ovr, ovrJava *java, double predicted_display_time);

    const ControllerState *get_controller_state_by_id(int controller_id) const {
        controller_id =
                controller_id == kPrimaryControllerId ? get_active_controller_id() : controller_id;

        for (int hand = 0; hand < MAX_HANDS; hand++) {
            auto *controller = &controllers[hand];
            if (controller->connected && controller->godot_controller_id == controller_id) {
                return controller;
            }
        }
        return nullptr;
    }

    static inline bool
    supports_haptic_vibration(const ovrInputTrackedRemoteCapabilities &capabilities) {
        return check_bit(capabilities.ControllerCapabilities,
                         ovrControllerCaps_HasSimpleHapticVibration);
    }

    void vibrate_controller(int controller_id, int duration_in_ms, float intensity) {
        controller_id =
                controller_id == kPrimaryControllerId ? get_active_controller_id() : controller_id;
        // Update the controller vibration state. Actual vibration will start in the next frame via
        // OvrMobileController::update_controller_vibration(...).
        if (duration_in_ms > 0 && intensity > 0.0f) {
            ControllerVibration vibration = { .is_vibrating = false,
                                              .end_time_in_ms = get_time_in_ms() + duration_in_ms,
                                              .intensity = intensity };
            controllers_vibrations[controller_id] = vibration;
        }
    }

    int get_active_controller_id() const {
        for (int hand = 0; hand < MAX_HANDS; hand++) {
            auto *controller = &controllers[hand];
            if (controller->connected && controller->primary) {
                return controller->godot_controller_id;
            }
        }
        return kInvalidGodotControllerId;
    }

    int get_controller_id(ControllerHand hand) {
        if (LEFT_HAND <= hand && hand < MAX_HANDS) {
            auto *controller = &controllers[hand];
            if (controller->connected) {
                return controller->godot_controller_id;
            }
        }
        return kInvalidGodotControllerId;
    }

 private:
    struct ControllerVibration {
        float intensity;
        double end_time_in_ms;
        bool is_vibrating;
    };

    ControllerState controllers[MAX_HANDS];
    std::map<int, ControllerVibration> controllers_vibrations;

    inline bool
    has_analog_grip_trigger(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities,
                         ovrControllerCaps_HasAnalogGripTrigger);
    }

    inline bool
    has_analog_index_trigger(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities,
                         ovrControllerCaps_HasAnalogIndexTrigger);
    }

    inline bool has_joystick(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasJoystick);
    }

    inline bool
    has_orientation_tracking(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities,
                         ovrControllerCaps_HasOrientationTracking);
    }

    inline bool has_position_tracking(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities,
                         ovrControllerCaps_HasPositionTracking);
    }

    inline bool has_trackpad(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasTrackpad);
    }

    inline bool is_gear_vr_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelGearVR);
    }

    inline bool
    is_oculus_go_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelOculusGo);
    }

    inline bool
    is_oculus_touch_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelOculusTouch);
    }

    inline bool
    is_left_touch_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_LeftHand);
    }

    inline bool is_left_hand_controller(const ovrInputHandCapabilities &capabilities) const {
        return check_bit(capabilities.HandCapabilities, ovrHandCaps_LeftHand);
    }

    inline bool
    is_right_touch_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_RightHand);
    }

    inline bool is_right_hand_controller(const ovrInputHandCapabilities &capabilities) const {
        return check_bit(capabilities.HandCapabilities, ovrHandCaps_RightHand);
    }

    inline ControllerHand
    get_controller_handedness(const ovrInputHandCapabilities &capabilities) const {
        return is_left_hand_controller(capabilities) ? LEFT_HAND : RIGHT_HAND;
    }

    inline ControllerHand
    get_controller_handedness(const ovrInputTrackedRemoteCapabilities &capabilities) const {
        return is_left_touch_controller(capabilities) ? LEFT_HAND : RIGHT_HAND;
    }

    inline int get_godot_hand(ControllerHand hand) {
        return hand == LEFT_HAND ? /* TRACKER_LEFT_HAND */ 1 : /* TRACKER_RIGHT_HAND */ 2;
    }

    const char *get_controller_model_name(const ControllerState &controller_state);

    void update_controllers_connection_state(ovrMobile *ovr, ovrJava *java);

    void update_controller_tracking_state(ovrMobile *ovr,
                                          ControllerState &controller_state,
                                          double predicted_display_time);
    void update_controller_tracking_state_tracked_remote(ovrMobile *ovr,
                                                         ControllerState &controller_state,
                                                         double predicted_display_time);
    void update_controller_tracking_state_hand(ovrMobile *ovr,
                                               ControllerState &controller_state,
                                               double predicted_display_time);

    void update_controller_input_state(ovrMobile *ovr, ControllerState &controller_state);
    void update_controller_input_state_tracked_remote(ovrMobile *ovr,
                                                      ControllerState &controller_state);
    void update_controller_input_state_hand(ovrMobile *ovr, ControllerState &controller_state);

    void update_controller_vibration(ovrMobile *ovr, ControllerState &controller_state);
};

} // namespace ovrmobile

#endif // OVRMOBILE_OVR_MOBILE_CONTROLLER_H
