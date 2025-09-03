#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glLoader.h"
#include <cstddef>

class VertexArray {
    private:
        uint32_t id = 0;

    public:
        VertexArray();
        ~VertexArray();

        void bind();
};

class GLBuffer {
    private:
        uint32_t id = 0;
        GLenum type = 0;

    public:
        GLBuffer(GLenum type, size_t size, const void* data, GLenum usage);
        ~GLBuffer();

        void bind();
};

#endif
