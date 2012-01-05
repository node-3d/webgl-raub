#ifndef _INCLUDE_ARCH_WRAPPER_
#define _INCLUDE_ARCH_WRAPPER_
  #ifdef __IPHONE_OS_VERSION_MIN_REQUIRED
    #include <OpenGLES/ES2/gl.h>
    #include <OpenGLES/ES2/glext.h>
    typedef double GLclampd;
  #else
    #ifdef __APPLE__
      #include <OpenGL/OpenGL.h>
      #include <OpenGL/gl.h>
      #include <OpenGL/glext.h>
      #define glClearDepthf glClearDepth
      #define glDepthRangef glDepthRange
    #else
      #ifdef _WIN32
        #include <windows.h>
      #else
        #include "GLES2/gl2.h"
        #include "GLES2/gl2ext.h"
      #endif
    #endif
  #endif
#endif
