////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include <core/Godot.hpp>
#include <core/GodotGlobal.hpp>
#include "godot_ovrmobile.h"

#include "arvr_interface.h"

#include "api/ovr_display.h"
#include "api/ovr_input.h"
#include "gdnative/nativescript/ovr_display_refresh_rate_ns.h"
#include "gdnative/nativescript/ovr_guardian_system_ns.h"
#include "gdnative/nativescript/ovr_init_config_ns.h"
#include "gdnative/nativescript/ovr_performance_ns.h"
#include "gdnative/nativescript/ovr_tracking_transform_ns.h"
#include "gdnative/nativescript/ovr_utilities_ns.h"
#include "gdnative/nativescript/ovr_hand_tracking_ns.h"

// experimental low-level VrApi access
#include "gdnative/nativescript/ovr_vr_api_proxy_ns.h"

void GDN_EXPORT godot_ovrmobile_gdnative_init(godot_gdnative_init_options *options) {
	godot::Godot::gdnative_init(options);
}

void GDN_EXPORT godot_ovrmobile_gdnative_singleton() {
	if (godot::arvr_api != nullptr) {
		godot::arvr_api->godot_arvr_register_interface(&interface_struct);
	}
}

void GDN_EXPORT godot_ovrmobile_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	register_gdnative_display_refresh_rate(handle);
	register_gdnative_guardian_system(handle);
	register_gdnative_init_config(handle);
	register_gdnative_performance(handle);
	register_gdnative_tracking_transform(handle);
	register_gdnative_utilities(handle);
	register_gdnative_hand_tracking(handle);
	register_gdnative_vr_api_proxy(handle);

	godot::register_class<ovrmobile::OvrDisplay>();
	godot::register_class<ovrmobile::OvrInput>();
}

void GDN_EXPORT godot_ovrmobile_nativescript_terminate(void *handle) {
	godot::Godot::nativescript_terminate(handle);
}

void GDN_EXPORT godot_ovrmobile_gdnative_terminate(godot_gdnative_terminate_options *options) {
	godot::Godot::gdnative_terminate(options);
}
