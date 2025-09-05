#include "globjects/GLBuffer.h"
#include <print>

GLBuffer::GLBuffer(GLenum type, size_t size, const void* data, GLenum usage) {
    this->type = type;
    glGenBuffers(1, &id);
    glBindBuffer(type, id);
    glBufferData(type, size, (const void*)data, usage);
}

GLBuffer::GLBuffer(GLBuffer&& other) noexcept { 
    this->id = other.id;
    this->type = other.type;
    other.id = 0;
};

GLBuffer& GLBuffer::operator=(GLBuffer&& other) noexcept {
    if (this == &other) return *this;

    this->id = other.id;
    this->type = other.type;
    other.id = 0;

    return *this;
}

GLBuffer::~GLBuffer() { 
    glDeleteBuffers(1, &id);
    if (id != 0) std::print("cleaned {} with id: {}\n", (type == GL_ARRAY_BUFFER) ? "VBO" : "EBO", id);
};

void GLBuffer::bind() { glBindBuffer(type, id); };
