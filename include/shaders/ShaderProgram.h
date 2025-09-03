#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include "glLoader.h"

class ShaderProgram {
    private:
        uint32_t id = 0;

    public:
        ShaderProgram(const char*, const char*);
        ~ShaderProgram(); 

        void use() const;
};
#endif
