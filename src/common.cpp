////////////////////////////////////////////////////////////////
// Common includes for OVR code, mostly copied from samples
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "common.h"
#include <vector>

namespace ovrmobile {

void godot_transform_from_ovr_pose(godot_transform *dest, const ovrPosef &pose, const float world_scale) {
	godot_quat q;
	godot_basis basis;
	godot_vector3 origin;

	api->godot_quat_new(&q, pose.Orientation.x, pose.Orientation.y, pose.Orientation.z, pose.Orientation.w);
	api->godot_basis_new_with_euler_quat(&basis, &q);

	api->godot_vector3_new(&origin, pose.Position.x * world_scale, pose.Position.y * world_scale,
			pose.Position.z * world_scale);
	api->godot_transform_new(dest, &basis, &origin);
}

// Must use EGLSyncKHR because the VrApi still supports OpenGL ES 2.0
// EGL_KHR_reusable_sync
PFNEGLCREATESYNCKHRPROC OpenGLExtensions::eglCreateSyncKHR;
PFNEGLDESTROYSYNCKHRPROC OpenGLExtensions::eglDestroySyncKHR;
PFNEGLCLIENTWAITSYNCKHRPROC OpenGLExtensions::eglClientWaitSyncKHR;
PFNEGLSIGNALSYNCKHRPROC OpenGLExtensions::eglSignalSyncKHR;
PFNEGLGETSYNCATTRIBKHRPROC OpenGLExtensions::eglGetSyncAttribKHR;

bool OpenGLExtensions::multi_view;
bool OpenGLExtensions::EXT_texture_border_clamp;

void OpenGLExtensions::initExtensions() {
	eglCreateSyncKHR = (PFNEGLCREATESYNCKHRPROC)eglGetProcAddress("eglCreateSyncKHR");
	eglDestroySyncKHR = (PFNEGLDESTROYSYNCKHRPROC)eglGetProcAddress("eglDestroySyncKHR");
	eglClientWaitSyncKHR = (PFNEGLCLIENTWAITSYNCKHRPROC)eglGetProcAddress("eglClientWaitSyncKHR");
	eglSignalSyncKHR = (PFNEGLSIGNALSYNCKHRPROC)eglGetProcAddress("eglSignalSyncKHR");
	eglGetSyncAttribKHR = (PFNEGLGETSYNCATTRIBKHRPROC)eglGetProcAddress("eglGetSyncAttribKHR");

	const char *allExtensions = (const char *)glGetString(GL_EXTENSIONS);
	if (allExtensions != NULL) {
		multi_view = strstr(allExtensions, "GL_OVR_multiview2") && strstr(allExtensions, "GL_OVR_multiview_multisampled_render_to_texture");

		EXT_texture_border_clamp = strstr(allExtensions, "GL_EXT_texture_border_clamp") || strstr(allExtensions, "GL_OES_texture_border_clamp");
	}
}

const char *OpenGLExtensions::errorString(const EGLint error) {
	switch (error) {
		case EGL_SUCCESS: return "EGL_SUCCESS";
		case EGL_NOT_INITIALIZED: return "EGL_NOT_INITIALIZED";
		case EGL_BAD_ACCESS: return "EGL_BAD_ACCESS";
		case EGL_BAD_ALLOC: return "EGL_BAD_ALLOC";
		case EGL_BAD_ATTRIBUTE: return "EGL_BAD_ATTRIBUTE";
		case EGL_BAD_CONTEXT: return "EGL_BAD_CONTEXT";
		case EGL_BAD_CONFIG: return "EGL_BAD_CONFIG";
		case EGL_BAD_CURRENT_SURFACE: return "EGL_BAD_CURRENT_SURFACE";
		case EGL_BAD_DISPLAY: return "EGL_BAD_DISPLAY";
		case EGL_BAD_SURFACE: return "EGL_BAD_SURFACE";
		case EGL_BAD_MATCH: return "EGL_BAD_MATCH";
		case EGL_BAD_PARAMETER: return "EGL_BAD_PARAMETER";
		case EGL_BAD_NATIVE_PIXMAP: return "EGL_BAD_NATIVE_PIXMAP";
		case EGL_BAD_NATIVE_WINDOW: return "EGL_BAD_NATIVE_WINDOW";
		case EGL_CONTEXT_LOST: return "EGL_CONTEXT_LOST";
		default: return "unknown";
	}
}

const char *OpenGLExtensions::GlFrameBufferStatusString(GLenum status) {
	switch (status) {
		case GL_FRAMEBUFFER_UNDEFINED: return "GL_FRAMEBUFFER_UNDEFINED";
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
		case GL_FRAMEBUFFER_UNSUPPORTED: return "GL_FRAMEBUFFER_UNSUPPORTED";
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
		default: return "unknown";
	}
}

const char *OpenGLExtensions::GlErrorString(GLenum error) {
	switch (error) {
		case GL_NO_ERROR: return "GL_NO_ERROR";
		case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
		default: return "unknown";
	}
}

void OpenGLExtensions::GLCheckErrors(int line, const char* filename, const char* func) {
	for (int i = 0; i < 10; i++) {
		const GLenum error = glGetError();
		if (error == GL_NO_ERROR) {
			break;
		}
		ALOGE("GL error on line %d: %s (%s: %s)", line, GlErrorString(error), filename, func);
	}
}

} // namespace ovrmobile
