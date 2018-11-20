////////////////////////////////////////////////////////////////
// Oculus OVR framebuffer helper functions
// Copied from Oculus sample projects but wrapped into a class
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "ovrFramebuffer.h"

namespace OVR {

frameBuffer::frameBuffer(const bool useMultiview, const GLenum colorFormat, const int width, const int height, const int multisamples) {
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC glRenderbufferStorageMultisampleEXT =
			(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEEXTPROC)eglGetProcAddress("glRenderbufferStorageMultisampleEXT");
	PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC glFramebufferTexture2DMultisampleEXT =
			(PFNGLFRAMEBUFFERTEXTURE2DMULTISAMPLEEXTPROC)eglGetProcAddress("glFramebufferTexture2DMultisampleEXT");

	PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC glFramebufferTextureMultiviewOVR =
			(PFNGLFRAMEBUFFERTEXTUREMULTIVIEWOVRPROC)eglGetProcAddress("glFramebufferTextureMultiviewOVR");
	PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC glFramebufferTextureMultisampleMultiviewOVR =
			(PFNGLFRAMEBUFFERTEXTUREMULTISAMPLEMULTIVIEWOVRPROC)eglGetProcAddress("glFramebufferTextureMultisampleMultiviewOVR");

	mWidth = width;
	mHeight = height;
	mMultisamples = multisamples;
	mUseMultiview = (useMultiview && (glFramebufferTextureMultiviewOVR != NULL)) ? true : false;

	mColorTextureSwapChain = vrapi_CreateTextureSwapChain3(mUseMultiview ? VRAPI_TEXTURE_TYPE_2D_ARRAY : VRAPI_TEXTURE_TYPE_2D, colorFormat, width, height, 1, 3);
	mTextureSwapChainLength = vrapi_GetTextureSwapChainLength(mColorTextureSwapChain);
	mTextureSwapChainIndex = 0;
	mDepthBuffers = (GLuint *)malloc(mTextureSwapChainLength * sizeof(GLuint));
	mFrameBuffers = (GLuint *)malloc(mTextureSwapChainLength * sizeof(GLuint));

	ALOGV("        mUseMultiview = %d", mUseMultiview);

	for (int i = 0; i < mTextureSwapChainLength; i++) {
		// Create the color buffer texture.
		const GLuint colorTexture = vrapi_GetTextureSwapChainHandle(mColorTextureSwapChain, i);
		GLenum colorTextureTarget = mUseMultiview ? GL_TEXTURE_2D_ARRAY : GL_TEXTURE_2D;
		GL(glBindTexture(colorTextureTarget, colorTexture));
		if (OpenGLExtensions::EXT_texture_border_clamp) {
			GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER));
			GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER));
			GLfloat borderColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
			GL(glTexParameterfv(colorTextureTarget, GL_TEXTURE_BORDER_COLOR, borderColor));
		} else {
			// Just clamp to edge. However, this requires manually clearing the border
			// around the layer to clear the edge texels.
			GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		}
		GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL(glTexParameteri(colorTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GL(glBindTexture(colorTextureTarget, 0));

		if (mUseMultiview) {
			// Create the depth buffer texture.
			GL(glGenTextures(1, &mDepthBuffers[i]));
			GL(glBindTexture(GL_TEXTURE_2D_ARRAY, mDepthBuffers[i]));
			GL(glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_DEPTH_COMPONENT24, width, height, 2));
			GL(glBindTexture(GL_TEXTURE_2D_ARRAY, 0));

			// Create the frame buffer.
			GL(glGenFramebuffers(1, &mFrameBuffers[i]));
			GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffers[i]));
			if (multisamples > 1 && (glFramebufferTextureMultisampleMultiviewOVR != NULL)) {
				GL(glFramebufferTextureMultisampleMultiviewOVR(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthBuffers[i], 0 /* level */, multisamples /* samples */, 0 /* baseViewIndex */, 2 /* numViews */));
				GL(glFramebufferTextureMultisampleMultiviewOVR(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTexture, 0 /* level */, multisamples /* samples */, 0 /* baseViewIndex */, 2 /* numViews */));
			} else {
				GL(glFramebufferTextureMultiviewOVR(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mDepthBuffers[i], 0 /* level */, 0 /* baseViewIndex */, 2 /* numViews */));
				GL(glFramebufferTextureMultiviewOVR(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTexture, 0 /* level */, 0 /* baseViewIndex */, 2 /* numViews */));
			}

			GL(GLenum renderFramebufferStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER));
			GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
			if (renderFramebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
				ALOGE("Incomplete frame buffer object: %s", OpenGLExtensions::GlFrameBufferStatusString(renderFramebufferStatus));
				return;
			}
		} else {
			if (multisamples > 1 && glRenderbufferStorageMultisampleEXT != NULL && glFramebufferTexture2DMultisampleEXT != NULL) {
				// Create multisampled depth buffer.
				GL(glGenRenderbuffers(1, &mDepthBuffers[i]));
				GL(glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffers[i]));
				GL(glRenderbufferStorageMultisampleEXT(GL_RENDERBUFFER, multisamples, GL_DEPTH_COMPONENT24, width, height));
				GL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

				// Create the frame buffer.
				// NOTE: glFramebufferTexture2DMultisampleEXT only works with GL_FRAMEBUFFER.
				GL(glGenFramebuffers(1, &mFrameBuffers[i]));
				GL(glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffers[i]));
				GL(glFramebufferTexture2DMultisampleEXT(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0, multisamples));
				GL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffers[i]));
				GL(GLenum renderFramebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER));
				GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
				if (renderFramebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
					ALOGE("Incomplete frame buffer object: %s", OpenGLExtensions::GlFrameBufferStatusString(renderFramebufferStatus));
					return;
				}
			} else {
				// Create depth buffer.
				GL(glGenRenderbuffers(1, &mDepthBuffers[i]));
				GL(glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffers[i]));
				GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height));
				GL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

				// Create the frame buffer.
				GL(glGenFramebuffers(1, &mFrameBuffers[i]));
				GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffers[i]));
				GL(glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffers[i]));
				GL(glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0));
				GL(GLenum renderFramebufferStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER));
				GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
				if (renderFramebufferStatus != GL_FRAMEBUFFER_COMPLETE) {
					ALOGE("Incomplete frame buffer object: %s", OpenGLExtensions::GlFrameBufferStatusString(renderFramebufferStatus));
					return;
				}
			}
		}
	}
}

frameBuffer::~frameBuffer() {
	GL(glDeleteFramebuffers(mTextureSwapChainLength, mFrameBuffers));
	if (mUseMultiview) {
		GL(glDeleteTextures(mTextureSwapChainLength, mDepthBuffers));
	} else {
		GL(glDeleteRenderbuffers(mTextureSwapChainLength, mDepthBuffers));
	}
	vrapi_DestroyTextureSwapChain(mColorTextureSwapChain);

	free(mDepthBuffers);
	free(mFrameBuffers);
}

void frameBuffer::setCurrent() {
	GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFrameBuffers[mTextureSwapChainIndex]));
}

void frameBuffer::setNone() {
	GL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
}

void frameBuffer::resolve() {
	// Discard the depth buffer, so the tiler won't need to write it back out to memory.
	const GLenum depthAttachment[1] = { GL_DEPTH_ATTACHMENT };
	glInvalidateFramebuffer(GL_DRAW_FRAMEBUFFER, 1, depthAttachment);

	// Flush this frame worth of commands.
	glFlush();
}

void frameBuffer::advance() {
	// Advance to the next texture from the set.
	mTextureSwapChainIndex = (mTextureSwapChainIndex + 1) % mTextureSwapChainLength;
}

} // namespace OVR