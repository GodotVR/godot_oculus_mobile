////////////////////////////////////////////////////////////////////////////////////////////////
// Our main ARVRInterface code for our GearVR GDNative module

#ifndef GEARVR_ARVR_INTERFACE_H
#define GEARVR_ARVR_INTERFACE_H

#include "GodotCalls.h"
#include "OS.h"

// Include the GearVR SDK
#include "VrApi.h"

// Include the GearVR SDK Helper
#include "VrApi_Helpers.h"

#include <EGL/egl.h>

extern const godot_arvr_interface_gdnative interface_struct;

typedef struct arvr_data_struct {
	bool gearvr_is_initialized;
	ovrJava java;
	ovrMobile * ovr;
	ovrTextureSwapChain * colorTextureSwapChain[VRAPI_FRAME_LAYER_EYE_MAX];
	long long frameIndex;
	double predictedDisplayTime;
	ovrTracking2 tracking;
	ovrLayerProjection2 layer;

	uint32_t width;
	uint32_t height;

} arvr_data_struct;

#endif /* !GEARVR_ARVR_INTERFACE_H */
