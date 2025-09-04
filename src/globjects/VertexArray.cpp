#include "globjects/VertexArray.h"
#include <optional>
#include <print>

VertexArray::VertexArray() { glGenVertexArrays(1, &id); };

 // prevents destructor of the temporary from deleting the VAO
VertexArray::VertexArray(VertexArray&& other) noexcept {
    id = other.id;
    attribPointer_index = other.attribPointer_index;
    vertex_buffers = std::move(other.vertex_buffers);
    element_buffer = std::move(other.element_buffer);

    other.id = 0;
}

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &id); };

void VertexArray::add_vbo(string_view name, uint32_t num_components_per_vertex, vector<float>&& data) {
    this->bind();
    GLBuffer vbo = GLBuffer(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
    vbo.bind();
    glVertexAttribPointer(this->attribPointer_index, num_components_per_vertex, GL_FLOAT, GL_FALSE, sizeof(float) * num_components_per_vertex, (void*)0);
    glEnableVertexAttribArray(this->attribPointer_index++);
    this->vertex_buffers.insert({string(name), std::move(vbo)});
}

VertexArray VertexArray::build() {
    VertexArray vao;
    return vao;
}

VertexArray&& VertexArray::with_vbo(string_view name, uint32_t num_components_per_vertex, vector<float>&& data) && {
    add_vbo(name, num_components_per_vertex, std::move(data));

    return std::move(*this);
}

VertexArray&& VertexArray::with_ebo(vector<uint32_t>&& data) && {
    this->bind();
    GLBuffer ebo = GLBuffer(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(uint32_t), data.data(), GL_STATIC_DRAW);
    ebo.bind();
    this->element_buffer = std::move(ebo);

    return std::move(*this);
}

optional<GLBuffer> VertexArray::get_vbo(string_view name) {
    auto it = this->vertex_buffers.find(string(name));

    if (it == vertex_buffers.end()) return std::nullopt;
    return it->second;
}

optional<GLBuffer> VertexArray::get_ebo() { return this->element_buffer; };

void VertexArray::bind() { std::print("vao id: {}\n", this->id); glBindVertexArray(id); };
