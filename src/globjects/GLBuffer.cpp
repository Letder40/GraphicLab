#include "globjects/GLBuffer.h"

GLBuffer::GLBuffer(GLenum type, size_t size, const void* data, GLenum usage) {
    this->type = type;
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size, (const void*)data, usage);
}

GLBuffer::~GLBuffer() { };

void GLBuffer::bind() { glBindBuffer(type, id); };
