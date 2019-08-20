////////////////////////////////////////////////////////////////////////////
// OVR GDNative module for Godot
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef GODOT_OVRMOBILE_H
#define GODOT_OVRMOBILE_H

#include "godot_calls.h"

// declare our public functions for our ARVR Interface
#ifdef __cplusplus
extern "C" {
#endif

void GDN_EXPORT godot_ovrmobile_gdnative_singleton();
void GDN_EXPORT godot_ovrmobile_nativescript_init(void *p_handle);

#ifdef __cplusplus
}
#endif

#endif /* !GODOT_OVRMOBILE_H */
