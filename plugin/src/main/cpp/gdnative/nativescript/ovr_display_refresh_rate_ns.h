////////////////////////////////////////////////////////////////////////////////////////////////
// GDNative module that exposes part of the oculus runtime api.
// Each exported class implements one section of the VrApi.h.
// This implements the <Display refresh rate> section.

#ifndef OVR_DISPLAY_REFRESH_RATE_NS_H
#define OVR_DISPLAY_REFRESH_RATE_NS_H

#include "nativescript_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Registers the OvrDisplayRefreshRate class and functions to GDNative.
// This method should be called from godot_ovrmobile_nativescript_init.
void register_gdnative_display_refresh_rate(void *handle);

GDCALLINGCONV void *ovr_display_refresh_rate_constructor(godot_object *instance, void *method_data);
GDCALLINGCONV void ovr_display_refresh_rate_destructor(godot_object *instance, void *method_data, void *user_data);

// implements VrApi.h: ovrResult vrapi_SetDisplayRefreshRate(ovrMobile * ovr, const float refreshRate);
GDCALLINGCONV godot_variant set_display_refresh_rate(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

// Utility method to access the display refresh rates supported by the device.
GDCALLINGCONV godot_variant get_supported_display_refresh_rates(godot_object *instance, void *method_data, void *user_data, int num_args, godot_variant **args);

#ifdef __cplusplus
}
#endif

#endif // OVR_DISPLAY_REFRESH_RATE_NS_H
