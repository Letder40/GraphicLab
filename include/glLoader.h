#ifndef GLOADER_H
#define GLOADER_H

#include <cstdio>
#ifdef CLANG_COMPLETE_ONLY
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    #include <GL/glew.h>
#endif
    
bool init_GlLoader();


#endif
