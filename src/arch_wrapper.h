#ifndef _INCLUDE_ARCH_WRAPPER_
#define _INCLUDE_ARCH_WRAPPER_

#ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
    typedef double GLclampd;
#else
    /*#if defined (__APPLE__) || defined(MACOSX)
      #include <OpenGL/gl3.h>
      #include <OpenGL/gl3ext.h>
      #define GL_ALIASED_POINT_SIZE_RANGE       0x846D
      #define GL_RED_BITS                       0x0D52
      #define GL_GREEN_BITS                     0x0D53
      #define GL_BLUE_BITS                      0x0D54
      #define GL_ALPHA_BITS                     0x0D55
      #define GL_DEPTH_BITS                     0x0D56
      #define GL_STENCIL_BITS                   0x0D57
      #define GL_LUMINANCE                      0x1909
      #define GL_LUMINANCE_ALPHA                0x190A
      #define GL_GENERATE_MIPMAP_HINT           0x8192
      //#include "GLES2/gl2.h"
      //#include "GLES2/gl2ext.h"
      #define glClearDepthf glClearDepth
      #define glDepthRangef glDepthRange
    #else
      #ifdef _WIN32*/
        #include <GL/glew.h>
    /*#else
        #include "GLES2/gl2.h"
        #include "GLES2/gl2ext.h"
      #endif
    #endif*/
#endif

#endif
