#include "globjects/GLBuffer.h"

GLBuffer::GLBuffer(GLenum type, size_t size, const void* data, GLenum usage) {
    this->type = type;
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size, data, usage);
}

GLBuffer::~GLBuffer() { glDeleteBuffers(1, &id); };

void GLBuffer::bind() { glBindBuffer(type, id); };
