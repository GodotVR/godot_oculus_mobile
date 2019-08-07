////////////////////////////////////////////////////////////////
// Common includes for OVR code, mostly copied from samples
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVRMOBILE_COMMON_H
#define OVRMOBILE_COMMON_H

// Some android includes
#include <android/log.h>

// Include OpenGL ES 3 headers
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#if !defined(EGL_OPENGL_ES3_BIT_KHR)
#define EGL_OPENGL_ES3_BIT_KHR 0x0040
#endif

// EXT_texture_border_clamp
#ifndef GL_CLAMP_TO_BORDER
#define GL_CLAMP_TO_BORDER 0x812D
#endif

#ifndef GL_TEXTURE_BORDER_COLOR
#define GL_TEXTURE_BORDER_COLOR 0x1004
#endif

#if !defined(GL_EXT_multisampled_render_to_texture)
typedef void(GL_APIENTRY *PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height);
typedef void(GL_APIENTRY *PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLsizei samples);
#endif

#if !defined(GL_OVR_multiview)
static const int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_NUM_VIEWS_OVR = 0x9630;
static const int GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_BASE_VIEW_INDEX_OVR = 0x9632;
static const int GL_MAX_VIEWS_OVR = 0x9631;
typedef void(GL_APIENTRY *PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint baseViewIndex, GLsizei numViews);
#endif

#if !defined(GL_OVR_multiview_multisampled_render_to_texture)
typedef void(GL_APIENTRY *PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC)(GLenum target, GLenum attachment, GLuint texture, GLint level, GLsizei samples, GLint baseViewIndex, GLsizei numViews);
#endif

#include "godot_calls.h"

// Include the OVR SDK
#include "VrApi.h"

// Include the OVR SDK Helper
#include "VrApi_Helpers.h"

#define DEBUG 1
#define LOG_TAG "GodotOVRMobile"

#define ALOG_ASSERT(_cond, ...) \
	if (!(_cond)) __android_log_assert("conditional", LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

#define MULTI_THREADED 0

namespace ovrmobile {

static const int CPU_LEVEL = 2;
static const int GPU_LEVEL = 3;
static const int NUM_MULTI_SAMPLES = 4;

inline bool check_bit(uint32_t in, uint32_t bits) {
	return (in & bits) != 0;
}

void godot_transform_from_ovr_pose(godot_transform *dest, const ovrPosef &pose, const float world_scale);

class OpenGLExtensions {
public:
	// Must use EGLSyncKHR because the VrApi still supports OpenGL ES 2.0
	// EGL_KHR_reusable_sync
	static PFNEGLCREATESYNCKHRPROC eglCreateSyncKHR;
	static PFNEGLDESTROYSYNCKHRPROC eglDestroySyncKHR;
	static PFNEGLCLIENTWAITSYNCKHRPROC eglClientWaitSyncKHR;
	static PFNEGLSIGNALSYNCKHRPROC eglSignalSyncKHR;
	static PFNEGLGETSYNCATTRIBKHRPROC eglGetSyncAttribKHR;

	static bool multi_view; // GL_OVR_multiview, GL_OVR_multiview2
	static bool EXT_texture_border_clamp; // GL_EXT_texture_border_clamp, GL_OES_texture_border_clamp

	static void initExtensions();
	static const char *errorString(const EGLint error);
	static const char *GlFrameBufferStatusString(GLenum status);
	static const char *GlErrorString(GLenum error);
	static void GLCheckErrors(int line, const char* filename, const char* func);
};

} // namespace ovrmobile

#define GL(func) \
	func;        \
	ovrmobile::OpenGLExtensions::GLCheckErrors(__LINE__, __FILE__, #func);

#endif // OVRMOBILE_COMMON_H