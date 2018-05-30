////////////////////////////////////////////////////////////////////////////
// GearVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij, 
// with loads of help from Thomas "Karroffel" Herzog

#ifndef GODOT_GEARVR_H
#define GODOT_GEARVR_H

#include "GodotCalls.h"
	
#include "ARVRInterface.h"

// declare our public functions for our ARVR Interface
#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_gearvr_gdnative_singleton();
void GDN_EXPORT godot_gearvr_nativescript_init(void *p_handle);

#ifdef __cplusplus
}
#endif


#endif /* !GODOT_GEARVR_H */
