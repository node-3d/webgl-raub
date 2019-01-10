#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


#ifdef _WIN32
	#define	strcasestr(s, t) strstr(strupr(s), strupr(t))
#endif


namespace webgl {

// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
static GLuint ToGLuint(const void* ptr) {
	return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
}


NAN_METHOD(clearStencil) {
	
	REQ_INT32_ARG(0, s);
	
	glClearStencil(s);
	
}


NAN_METHOD(stencilFunc) {
	
	REQ_INT32_ARG(0, func);
	REQ_INT32_ARG(1, ref);
	REQ_INT32_ARG(2, mask);
	
	glStencilFunc(func, ref, mask);
	
}


NAN_METHOD(stencilFuncSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, func);
	REQ_INT32_ARG(2, ref);
	REQ_INT32_ARG(3, mask);
	
	glStencilFuncSeparate(face, func, ref, mask);
	
}


NAN_METHOD(stencilMask) {
	
	REQ_UINT32_ARG(0, mask);
	
	glStencilMask(mask);
	
}


NAN_METHOD(stencilMaskSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_UINT32_ARG(1, mask);
	
	glStencilMaskSeparate(face, mask);
	
}


NAN_METHOD(stencilOp) {
	
	REQ_INT32_ARG(0, fail);
	REQ_INT32_ARG(1, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOp(fail, zfail, zpass);
	
}


NAN_METHOD(stencilOpSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, fail);
	REQ_INT32_ARG(2, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOpSeparate(face, fail, zfail, zpass);
	
}


} // namespace webgl
