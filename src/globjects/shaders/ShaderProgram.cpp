#include "globjects/shaders/ShaderProgram.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <print>
#include <sstream>
#include <string>
#include <format>

using std::string;

ShaderProgram::ShaderProgram(const char* vert_filename, const char* frag_filename) {
    id = glCreateProgram();
    this->vert_filename = vert_filename;
    this->frag_filename = frag_filename;
};

ShaderProgram::~ShaderProgram() { glDeleteProgram(id); }

std::optional<string> get_src(string filename) {
    string src_path = std::filesystem::path(__FILE__).parent_path() / "src";
    std::ifstream src_file(std::format("{}/{}", src_path, filename));

    if (!src_file.is_open()) {
        std::print(stderr, "Failed to open source file: {}/{}", src_path, filename);
        return std::nullopt;
    }

    std::stringstream buffer;

    buffer << src_file.rdbuf();
    return buffer.str();
}

bool ShaderProgram::compile() {
    auto compile = [](const char* src, GLenum type) {
        uint32_t shader = glCreateShader(type);    
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char log[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (success) {
            return shader;
        }

        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << std::format("ERROR::SHADER::{}::COMPILATION_FAILED\n{}\n", (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT", log);

        return (uint32_t)0;
    };
    
    std::optional<string> vert_filesrc = get_src(this->vert_filename);
    if (!vert_filesrc) return false; 

    std::optional<string> frag_filesrc = get_src(this->frag_filename);
    if (!frag_filesrc) return false; 

    uint32_t vert = compile(vert_filesrc->c_str(), GL_VERTEX_SHADER);
    uint32_t frag = compile(frag_filesrc->c_str(), GL_FRAGMENT_SHADER);

    if (!vert || !frag) {
        glDeleteShader(vert);
        glDeleteShader(frag);
        return false;
    }

    glAttachShader(this->id, vert);
    glAttachShader(this->id, frag);
    glLinkProgram(this->id);

    int success;
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(id, 512, nullptr, log);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED" << log << std::endl;
        return false;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    return true;
}

void ShaderProgram::use() const { glUseProgram(id); }
