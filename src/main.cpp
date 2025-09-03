#include "glLoader.h"
#include <cstdio>

#include "window/Window.h"
#include "shaders/ShaderProgram.h"

#include "globjects/VertexArray.h"
#include "globjects/GLBuffer.h"

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

struct Shaders {
    const char* vertex_shader_src = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
    )";

    const char* fragment_shader_src = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
    )";

    const char* fragment_shader2_src = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(0.0f, 0.0f, 0.8f, 1.0f);
    }
    )";
};


int main () {
    Window window(1920, 1080, "GraphicLab");

#ifndef CLANG_COMPLETE_ONLY
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return -1;
    }
#endif

    VertexArray vao;
    vao.bind();

    GLBuffer vbo(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLBuffer ebo(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shaders shaders;
    ShaderProgram shader_program(shaders.vertex_shader_src, shaders.fragment_shader_src);
    ShaderProgram shader_program2(shaders.vertex_shader_src, shaders.fragment_shader2_src);

    while (!window.should_close()) {
        window.process_input();
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();
        shader_program.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        shader_program2.use();
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(uint32_t) * 3));

        window.poll_events();
        window.swap_buffers();
    }

    glfwTerminate();
}
