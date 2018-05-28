////////////////////////////////////////////////////////////////////////////
// GearVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij, 
// with loads of help from Thomas "Karroffel" Herzog

// Note, even though this is pure C code, we're using the C++ compiler as
// Microsoft never updated their C compiler to understand more modern dialects
// and openvr uses pesky things such as namespaces

#include "godot_gearvr.h"

////////////////////////////////////////////////////////////////////////
// gdnative init

void GDN_EXPORT godot_gearvr_gdnative_init(godot_gdnative_init_options *p_options) {
	// get our main API struct
	api = p_options->api_struct;

	// now find our arvr extension
	for (int i = 0; i < api->num_extensions; i++) {
		// todo: add version checks
		switch (api->extensions[i]->type) {
			case GDNATIVE_EXT_ARVR: {
				arvr_api = (godot_gdnative_ext_arvr_api_struct *)api->extensions[i];
			}; break;
			case GDNATIVE_EXT_NATIVESCRIPT: {
				nativescript_api = (godot_gdnative_ext_nativescript_api_struct *)api->extensions[i];
			}; break;
			default: break;
		};
	};

//	if (!gladLoadGL()) {
//		printf("Error initializing GLAD\n");
//	}
}

void GDN_EXPORT godot_gearvr_gdnative_terminate(godot_gdnative_terminate_options *p_options) {
	api = NULL;
}

void GDN_EXPORT godot_gearvr_gdnative_singleton() {
	arvr_api->godot_arvr_register_interface(&interface_struct);
}

void GDN_EXPORT godot_gearvr_nativescript_init(void *p_handle) {
}
