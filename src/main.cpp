#include "glLoader.h"
#include <cstdint>
#include <vector>

#include "globjects/shaders/ShaderProgram.h"
#include "globjects/VertexArray.h"
#include "globjects/Window.h"

using std::vector;

vector<float> vertices = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,
};

vector<uint32_t> indices = {
    0, 1, 3,
    1, 2, 3
};

int main () {
    Window window(1920, 1080, "GraphicLab");

    if (!init_GlLoader()) return 1;

    VertexArray vao = VertexArray::build()
        .with_vbo("test", 3, std::move(vertices))
        .with_ebo(std::move(indices));

    ShaderProgram shader_program_orange("shader.vert", "shader_orange.frag");
    if (!shader_program_orange.compile()) return 1;

    ShaderProgram shader_program_blue("shader.vert", "shader_blue.frag");
    if (!shader_program_blue.compile()) return 1;

    while (!window.should_close()) {
        window.process_input();
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        shader_program_orange.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        shader_program_blue.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * 3));

        window.poll_events();
        window.swap_buffers();
    }
}
