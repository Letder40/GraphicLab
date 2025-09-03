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
    
static inline bool init_GlLoader() {
#ifndef CLANG_COMPLETE_ONLY
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        return false;
    }
    return true;
#endif
    fprintf(stderr, "Error: The flag CLANG_COMPLETE_ONLY is defined, this is only for clangd lsp completions, if this message is shown remove that flag from the compilation process\n");
    return false;
}


#endif
