#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include "glLoader.h"
#include <string>

using std::string;

class ShaderProgram {
    private:
        uint32_t id = 0;
        string vert_filename; 
        string frag_filename; 

    public:
        ShaderProgram(const char* vert_shader_filename, const char* frag_shader_filename);
        ~ShaderProgram(); 

        bool compile();
        void use() const;
};
#endif
