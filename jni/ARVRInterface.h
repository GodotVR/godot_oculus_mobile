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

#include <GLES2/gl.h>

extern const godot_arvr_interface_gdnative interface_struct;

typedef struct
{
	uint32_t width;
	uint32_t height;
	uint32_t multisamples;
	uint32_t textureSwapChainLength;
	uint32_t textureSwapChainIndex;
	ovrTextureSwapChain * colorTextureSwapChain;
	GLuint * depthBuffers;
	GLuint * frameBuffers;
} ovrFramebuffer;

typedef struct
{
	ovrMobile * ovr;
	ovrTracking2 tracking;
} ovrHeadTracker;

typedef struct arvr_data_struct {
	uint32_t width;
	uint32_t height;

	bool gearvr_is_initialized;
	ovrFramebuffer frameBuffer[EYE_NUM];
	ovrJava java;
	ovrMobile * ovr;
	uint64_t frameIndex;
	ovrHeadTracker * headTracker;
} arvr_data_struct;

#endif /* !GEARVR_ARVR_INTERFACE_H */
