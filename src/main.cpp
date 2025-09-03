#include "glLoader.h"
#include <cstdint>

#include "globjects/shaders/ShaderProgram.h"
#include "globjects/VertexArray.h"
#include "globjects/GLBuffer.h"
#include "globjects/Window.h"

const float vertices[] = {
    0.5f,  0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
   -0.5f,  0.5f, 0.0f,
};

const uint32_t indices[] = {
    0, 1, 3,
    1, 2, 3
};

int main () {
    Window window(1920, 1080, "GraphicLab");

    if (!init_GlLoader()) return 1;

    VertexArray vao;
    vao.bind();

    GLBuffer vbo(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLBuffer ebo(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

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
