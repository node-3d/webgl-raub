#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(createProgram) { NAPI_ENV;
	GLuint program = glCreateProgram();
	RET_NUM(program);
}


JS_METHOD(deleteProgram) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, program);
	
	glDeleteProgram(program);
	RET_UNDEFINED;
	
}


JS_METHOD(isProgram) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, program);
	
	RET_BOOL(glIsProgram(program) != 0);
	RET_UNDEFINED;
	
}


JS_METHOD(getProgramInfoLog) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	
	int Len = 1024;
	char Error[1024];
	glGetProgramInfoLog(program, 1024, &Len, Error);
	
	RET_STR(Error);
	
}


#define CASES_PROGRAM_PARAM_BOOL case GL_DELETE_STATUS: \
	case GL_LINK_STATUS: \
	case GL_VALIDATE_STATUS:

#define CASES_PROGRAM_PARAM_ENUM case GL_TRANSFORM_FEEDBACK_BUFFER_MODE:

#define CASES_PROGRAM_PARAM_NUMBER case GL_ATTACHED_SHADERS: \
	case GL_ACTIVE_ATTRIBUTES: \
	case GL_ACTIVE_UNIFORMS: \
	case GL_ACTIVE_UNIFORM_BLOCKS: \
	case GL_INFO_LOG_LENGTH: \
	case GL_TRANSFORM_FEEDBACK_VARYINGS:

JS_METHOD(getProgramParameter) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	
	switch (name) {
	
	CASES_PROGRAM_PARAM_BOOL
		glGetProgramiv(program, name, &value);
		RET_BOOL(value != 0);
		break;
	
	CASES_PROGRAM_PARAM_ENUM
		glGetProgramiv(program, name, &value);
		RET_NUM(value);
		break;
	
	CASES_PROGRAM_PARAM_NUMBER
		glGetProgramiv(program, name, &value);
		RET_NUM(value);
		break;
	
	default:
		Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
		RET_NULL;
	}
	
}


JS_METHOD(linkProgram) { NAPI_ENV;
	
	REQ_INT32_ARG(0, id);
	
	glLinkProgram(id);
	RET_UNDEFINED;
	
}


JS_METHOD(useProgram) { NAPI_ENV;
	
	REQ_INT32_ARG(0, id);
	
	glUseProgram(id);
	RET_UNDEFINED;
	
}


JS_METHOD(validateProgram) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	
	glValidateProgram(program);
	RET_UNDEFINED;
	
}


} // namespace webgl
