#ifndef GLOADER_H
#define GLOADER_H

#ifdef CLANG_COMPLETE_ONLY
    #define GL_GLEXT_PROTOTYPES
    #include <GL/gl.h>
    #include <GL/glext.h>
#else
    #include <GL/glew.h>
#endif

#endif
