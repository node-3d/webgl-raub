#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createProgram) {
	
	GLuint program = glCreateProgram();
	
	RET_VALUE(Nan::New<Number>(program));
	
}


NAN_METHOD(deleteProgram) {
	
	REQ_UINT32_ARG(0, program);
	
	glDeleteProgram(program);
	
}


NAN_METHOD(isProgram) {
	
	REQ_UINT32_ARG(0, program);
	
	RET_VALUE(JS_BOOL(glIsProgram(program) != 0));
	
}


NAN_METHOD(getProgramInfoLog) {
	
	REQ_INT32_ARG(0, program);
	
	int Len = 1024;
	char Error[1024];
	glGetProgramInfoLog(program, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


#define CASES_PROGRAM_PARAM_BOOL case GL_DELETE_STATUS: \
	case GL_LINK_STATUS: \
	case GL_VALIDATE_STATUS:

#define CASES_PROGRAM_PARAM_NUMBER case GL_ATTACHED_SHADERS: \
	case GL_ACTIVE_ATTRIBUTES: \
	case GL_ACTIVE_UNIFORMS: \
	case GL_INFO_LOG_LENGTH:

NAN_METHOD(getProgramParameter) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	
	switch (name) {
	
	CASES_PROGRAM_PARAM_BOOL
		glGetProgramiv(program, name, &value);
		RET_VALUE(JS_BOOL(static_cast<bool>(value != 0)));
		break;
	
	CASES_PROGRAM_PARAM_NUMBER
		glGetProgramiv(program, name, &value);
		RET_VALUE(JS_NUM(static_cast<double>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(linkProgram) {
	
	REQ_INT32_ARG(0, id);
	
	glLinkProgram(id);
	
}


NAN_METHOD(useProgram) {
	
	REQ_INT32_ARG(0, id);
	
	glUseProgram(id);
	
}


NAN_METHOD(validateProgram) {
	
	REQ_INT32_ARG(0, program);
	
	glValidateProgram(program);
	
}


} // namespace webgl
