#ifndef GLBUFFER_H
#define GLBUFFER_H

#include "glLoader.h"
#include <cstddef>

class GLBuffer {
    private:
        uint32_t id = 0;
        GLenum type = 0;

    public:
        GLBuffer(GLenum type, size_t size, const void* data, GLenum usage);
        GLBuffer(GLBuffer&& other) noexcept;
        GLBuffer& operator=(GLBuffer&& other) noexcept;
        ~GLBuffer();

        void bind();
};

#endif
