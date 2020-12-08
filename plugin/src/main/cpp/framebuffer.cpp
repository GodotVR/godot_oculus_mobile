////////////////////////////////////////////////////////////////
// Oculus OVR framebuffer helper functions
// Copied from Oculus sample projects but wrapped into a class
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#include "framebuffer.h"

namespace ovrmobile {

namespace {
const int kDefaultBufferCount = 3;
} // namespace

FrameBuffer::FrameBuffer(const GLenum colorFormat, const int width, const int height) {
    mWidth = width;
    mHeight = height;

    // more detail about this initialization code can be found in the Oculus VR SDK in
    // VrSamples/VrCubeWorld_SurfaceView
    mColorTextureSwapChain = vrapi_CreateTextureSwapChain3(
            VRAPI_TEXTURE_TYPE_2D, colorFormat, width, height, 1, kDefaultBufferCount);
    mTextureSwapChainLength = vrapi_GetTextureSwapChainLength(mColorTextureSwapChain);
    mTextureSwapChainIndex = 0;

    ALOGV("    Create Framebuffer(...): mTextureSwapChainLength=%d", mTextureSwapChainLength);
    GL(); // empty GL macro call to catch previous GL errors and not report them on the next GL call
          // in this function

    for (int i = 0; i < mTextureSwapChainLength; i++) {
        // Create the color buffer texture.
        const GLuint colorTexture = vrapi_GetTextureSwapChainHandle(mColorTextureSwapChain, i);
        GLenum colorTextureTarget = GL_TEXTURE_2D;

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
    }
}

FrameBuffer::~FrameBuffer() {
    vrapi_DestroyTextureSwapChain(mColorTextureSwapChain);
}

GLuint FrameBuffer::get_active_target_texture() {
    return vrapi_GetTextureSwapChainHandle(mColorTextureSwapChain, mTextureSwapChainIndex);
}

void FrameBuffer::advance_texture_swap_chain() {
    mTextureSwapChainIndex = (mTextureSwapChainIndex + 1) % mTextureSwapChainLength;
}

} // namespace ovrmobile
