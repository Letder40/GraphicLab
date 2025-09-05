#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glLoader.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

#include "globjects/GLBuffer.h"

using std::string;
using std::string_view;
using std::vector;
using std::unordered_map;
using std::optional;

typedef unordered_map<string, GLBuffer> glbuffer_map;

class VertexArray {
    private:
        VertexArray();

        uint32_t id = 0;
        uint32_t attribPointer_index = 0;

        glbuffer_map vertex_buffers = glbuffer_map();
        optional<GLBuffer> element_buffer = optional<GLBuffer>();

    public:
        VertexArray(VertexArray&& other) noexcept;
        ~VertexArray();

        void add_vbo(std::string_view name, uint32_t num_components_per_vertex, vector<float>&& vao_data);

        static VertexArray build();
        VertexArray&& with_vbo(std::string_view name, uint32_t num_components_per_vertex, std::vector<float>&& vao_data) &&;
        VertexArray&& with_ebo(std::vector<uint32_t>&& ebo_data) &&;

        void bind();

        optional<GLBuffer*> get_vbo(std::string_view name);
        optional<GLBuffer*> get_ebo();
};
#endif
