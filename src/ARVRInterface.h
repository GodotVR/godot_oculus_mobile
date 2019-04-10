////////////////////////////////////////////////////////////////////////////////////////////////
// Our main ARVRInterface code for our OVR GDNative module
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVR_ARVR_INTERFACE_H
#define OVR_ARVR_INTERFACE_H

#include "GodotCalls.h"
#include "OS.h"

// Include some OVR stuff
#include "ovrFramebuffer.h"

extern const godot_arvr_interface_gdnative interface_struct;

typedef struct arvr_data_struct {
	uint32_t width;
	uint32_t height;

	// some initialisation stuff
	bool ovr_is_initialized;
	int CpuLevel;
	int GpuLevel;

	// some status stuff
	int MainThreadTid;
	int RenderThreadTid;

	// interface state
	ovrJava java;
	EGLDisplay Display;
	EGLContext Context;
	jobject Surface;
	ANativeWindow *NativeWindow;
	bool Resumed;

	// our main VrAPI state
	ovrMobile *ovr;

	// tracking
	ovrTracking2 headTracker;

	// for rendering
	uint64_t frameIndex;
	OVR::frameBuffer *frameBuffer[VRAPI_EYE_COUNT];
	ovrTextureSwapChain *colorTextureSwapChain[VRAPI_EYE_COUNT];
	double predictedDisplayTime;
	ovrLayerProjection2 layer;
} arvr_data_struct;

#endif /* !OVR_ARVR_INTERFACE_H */
