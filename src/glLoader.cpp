#include <print>
#include "glLoader.h"

void opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) return;

    std::print(stderr,
        "OpenGL Debug Message:\n"
        "  Source: 0x{}, Type: 0x{}, ID: {}, Severity: 0x{}\n"
        "  Message: {}\n\n",
        source, type, id, severity, message
    );

    (void)length;
    (void)userParam;
}

bool init_GlLoader() {
#ifndef CLANG_COMPLETE_ONLY
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(opengl_debug_callback, nullptr);

    return true;
#endif
    std::print(stderr, "Error: The flag CLANG_COMPLETE_ONLY is defined, this is only for clangd lsp completions, if this message is shown remove that flag from the compilation process\n");
    return false;
}
