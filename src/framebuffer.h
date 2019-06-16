////////////////////////////////////////////////////////////////
// Oculus OVR framebuffer helper class
// Copied from Oculus sample projects but wrapped into a class
// Investigate using VrAppFramework which is all this.
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVRMOBILE_FRAMEBUFFER_H
#define OVRMOBILE_FRAMEBUFFER_H

// Include some standard C stuff
#include <stdio.h>
#include <stdlib.h>

#include "common.h"

namespace ovrmobile {

class FrameBuffer {
private:
	int mWidth;
	int mHeight;
	int mMultisamples;
	int mTextureSwapChainLength;
	bool mUseMultiview;
	GLuint *mDepthBuffers;
	GLuint *mFrameBuffers;

public:
	int mTextureSwapChainIndex;
	ovrTextureSwapChain *mColorTextureSwapChain;

	FrameBuffer(const bool useMultiview, const GLenum colorFormat, const int width, const int height, const int multisamples);
	~FrameBuffer();

	GLuint getFrameBufferTexture();
	void resolve();
	void advance();
};

} // namespace ovrmobile

#endif // OVRMOBILE_FRAMEBUFFER_H
