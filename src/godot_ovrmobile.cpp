////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "godot_ovrmobile.h"

#include "arvr_interface.h"

#include "config/ovr_display_refresh_rate.h"
#include "config/ovr_guardian_system.h"
#include "config/ovr_init_config.h"
#include "config/ovr_performance.h"
#include "config/ovr_tracking_transform.h"
#include "config/ovr_utilities.h"

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
}
