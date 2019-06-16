/**
* Created by Fredia Huya-Kouadio. 
*/

#ifndef OVRMOBILE_OVR_MOBILE_CONTROLLER_H
#define OVRMOBILE_OVR_MOBILE_CONTROLLER_H

#include "VrApi.h"
#include "VrApi_Input.h"
#include "VrApi_Types.h"
#include "common.h"

namespace ovrmobile {

class OvrMobileController {
public:
	OvrMobileController();

	~OvrMobileController();

	void process(ovrMobile *ovr, ovrJava *java);

private:
	enum ControllerHand {
		LEFT_HAND,
		RIGHT_HAND,
		MAX_HANDS
	};

	struct ControllerState {
		bool connected = false;
		int godot_controller_id = 0;
		ovrInputTrackedRemoteCapabilities remote_capabilities;
	};

	inline bool has_analog_grip_trigger(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasAnalogGripTrigger);
	}

	inline bool has_analog_index_trigger(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasAnalogIndexTrigger);
	}

	inline bool has_joystick(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasJoystick);
	}

	inline bool has_orientation_tracking(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasOrientationTracking);
	}

	inline bool has_position_tracking(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasPositionTracking);
	}

	inline bool has_trackpad(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasTrackpad);
	}

	inline bool is_gear_vr_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelGearVR);
	}

	inline bool is_oculus_go_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelOculusGo);
	}

	inline bool is_oculus_touch_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_ModelOculusTouch);
	}

	inline bool is_left_hand_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_LeftHand);
	}

	inline bool is_right_hand_controller(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_RightHand);
	}

	inline ControllerHand get_controller_handedness(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return is_left_hand_controller(capabilities) ? LEFT_HAND : RIGHT_HAND;
	}

	inline ControllerHand get_controller_handedness(const ovrHandedness &dominant_hand) const {
		return dominant_hand == VRAPI_HAND_LEFT ? LEFT_HAND : RIGHT_HAND;
	}

	inline int get_godot_hand(ControllerHand hand) {
		return hand == LEFT_HAND ? /* TRACKER_LEFT_HAND */ 1 : /* TRACKER_RIGHT_HAND */ 2;
	}

	inline bool supports_haptic_vibration(const ovrInputTrackedRemoteCapabilities &capabilities) const {
		return check_bit(capabilities.ControllerCapabilities, ovrControllerCaps_HasSimpleHapticVibration);
	}

	const char *get_controller_model_name(const ovrInputTrackedRemoteCapabilities &capabilities);

	void update_controllers_connection_state(ovrMobile *ovr, ovrJava *java);

	void update_controller_tracking_state(ovrMobile *ovr, ControllerState controller_state);

	void update_controller_input_state(ovrMobile *ovr, ControllerState controller_state);

	void update_controller_vibration(ovrMobile *ovr, ControllerState controller_state);

	ControllerState controllers[MAX_HANDS];
};

} // namespace ovrmobile

#endif // OVRMOBILE_OVR_MOBILE_CONTROLLER_H
