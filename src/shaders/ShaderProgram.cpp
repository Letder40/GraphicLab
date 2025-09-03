#include "shaders/ShaderProgram.h"
#include <cstdio>

uint32_t id = 0;

ShaderProgram::ShaderProgram(const char* vert_src, const char* frag_src) {
    id = glCreateProgram();
    auto compile = [](const char* src, GLenum type) -> uint32_t {
        uint32_t shader = glCreateShader(type);    
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, log);
            fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILLED\n%s\n", log);
        }

        return shader;
    };
    
    uint32_t vert = compile(vert_src, GL_VERTEX_SHADER);
    uint32_t frag = compile(frag_src, GL_FRAGMENT_SHADER);

    glAttachShader(id, vert);
    glAttachShader(id, frag);
    glLinkProgram(id);

    glDeleteShader(vert);
    glDeleteShader(frag);
};

ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }

void ShaderProgram::use() const { glUseProgram(id); }
