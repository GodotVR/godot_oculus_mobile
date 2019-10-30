////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrmobile.h"

#include "arvr_interface.h"

#include "gdnative/nativescript/ovr_display_refresh_rate_ns.h"
#include "gdnative/nativescript/ovr_guardian_system_ns.h"
#include "gdnative/nativescript/ovr_init_config_ns.h"
#include "gdnative/nativescript/ovr_performance_ns.h"
#include "gdnative/nativescript/ovr_tracking_transform_ns.h"
#include "gdnative/nativescript/ovr_utilities_ns.h"

// experimental low-level VrApi access
#include "gdnative/nativescript/ovr_vr_api_proxy_ns.h"

void GDN_EXPORT godot_ovrmobile_gdnative_singleton() {
	if (arvr_api != NULL) {
		arvr_api->godot_arvr_register_interface(&interface_struct);
	}
}

void GDN_EXPORT godot_ovrmobile_nativescript_init(void *p_handle) {
	if (nativescript_api == NULL) {
		return;
	}

	register_gdnative_display_refresh_rate(p_handle);
	register_gdnative_guardian_system(p_handle);
	register_gdnative_init_config(p_handle);
	register_gdnative_performance(p_handle);
	register_gdnative_tracking_transform(p_handle);
	register_gdnative_utilities(p_handle);
	register_gdnative_vr_api_proxy(p_handle);
}
