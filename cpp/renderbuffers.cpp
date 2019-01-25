#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createRenderbuffer) {
	
	GLuint renderbuffers;
	glGenRenderbuffers(1, &renderbuffers);
	
	RET_VALUE(Nan::New<Number>(renderbuffers));
	
}


NAN_METHOD(deleteRenderbuffer) {
	
	REQ_UINT32_ARG(0, renderbuffer);
	
	glDeleteRenderbuffers(1, reinterpret_cast<GLuint*>(&renderbuffer));
	
}


NAN_METHOD(isRenderbuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsRenderbuffer(buffer) != 0));
	
}


NAN_METHOD(bindRenderbuffer) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindRenderbuffer(target, buffer);
	
}


NAN_METHOD(getRenderbufferParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	glGetRenderbufferParameteriv(target, name, &value);
	
	RET_VALUE(JS_INT(value));
	
}


NAN_METHOD(renderbufferStorage) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, internalformat);
	REQ_UINT32_ARG(2, width);
	REQ_UINT32_ARG(3, height);
	
	glRenderbufferStorage(target, internalformat, width, height);
	
}


} // namespace webgl
