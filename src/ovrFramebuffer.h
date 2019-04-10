////////////////////////////////////////////////////////////////
// Oculus OVR framebuffer helper class
// Copied from Oculus sample projects but wrapped into a class
// Investigate using VrAppFramework which is all this.
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVRFRAMEBUFFER_H
#define OVRFRAMEBUFFER_H

// Include some standard C stuff
#include <stdio.h>
#include <stdlib.h>

#include "ovrCommon.h"

namespace OVR {

class frameBuffer {
private:
	int mWidth;
	int mHeight;
	int mMultisamples;
	int mTextureSwapChainLength;
	int mTextureSwapChainIndex;
	bool mUseMultiview;
	GLuint *mDepthBuffers;
	GLuint *mFrameBuffers;

public:
	ovrTextureSwapChain *mColorTextureSwapChain;

	frameBuffer(const bool useMultiview, const GLenum colorFormat, const int width, const int height, const int multisamples);
	~frameBuffer();

	void setCurrent();
	void setNone();
	void resolve();
	void advance();
};

} // namespace OVR

#endif /* OVRFRAMEBUFFER_H */
