#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createProgram) { NAPI_ENV;
	GLuint program = glCreateProgram();
	RET_NUM(program);
}


DBG_EXPORT JS_METHOD(deleteProgram) { NAPI_ENV;
	REQ_UINT32_ARG(0, program);
	
	glDeleteProgram(program);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isProgram) { NAPI_ENV;
	REQ_UINT32_ARG(0, program);
	
	RET_BOOL(glIsProgram(program) != 0);
}


DBG_EXPORT JS_METHOD(getProgramInfoLog) { NAPI_ENV;
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

DBG_EXPORT JS_METHOD(getProgramParameter) { NAPI_ENV;
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
		JS_THROW("GetProgramParameter: Invalid Enum.");
		RET_NULL;
	}
	
}


DBG_EXPORT JS_METHOD(linkProgram) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	
	glLinkProgram(program);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(useProgram) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	
	glUseProgram(program);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(validateProgram) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	
	glValidateProgram(program);
	RET_UNDEFINED;
}


} // namespace webgl
