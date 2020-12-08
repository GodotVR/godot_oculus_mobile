////////////////////////////////////////////////////////////////
// Oculus OVR framebuffer helper class
// Copied from Oculus sample projects but wrapped into a class
// Investigate using VrAppFramework which is all this.
//
// Written by Bastiaan "Mux213" Olij and Paritosh Sharma,
// with loads of help from Thomas "Karroffel" Herzog

#ifndef OVRMOBILE_FRAMEBUFFER_H
#define OVRMOBILE_FRAMEBUFFER_H

#include "common.h"
#include <stdio.h>
#include <stdlib.h>

namespace ovrmobile {

class FrameBuffer {
 public:
    FrameBuffer(const GLenum colorFormat, const int width, const int height);
    ~FrameBuffer();

    // returns the currently active rendertarget texture from the texture swap chain
    GLuint get_active_target_texture();

    // Advance to the next rendertarget texture from the texture swap chain
    void advance_texture_swap_chain();

    int get_texture_swap_chain_index() { return mTextureSwapChainIndex; }

    ovrTextureSwapChain *get_texture_swap_chain() { return mColorTextureSwapChain; }

 private:
    int mWidth;
    int mHeight;
    int mTextureSwapChainLength;
    int mTextureSwapChainIndex;
    ovrTextureSwapChain *mColorTextureSwapChain;
};

} // namespace ovrmobile

#endif // OVRMOBILE_FRAMEBUFFER_H
