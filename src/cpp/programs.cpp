#include "webgl.hpp"


namespace webgl {

constexpr size_t PROG_UNIFORM_COUNT_MAX = 256;
constexpr size_t PROG_LOG_SIZE_MAX = 10 * 1024;
constexpr size_t BINARY_SIZE_MAX = 10 * 1024;


DBG_EXPORT JS_METHOD(createProgram) { NAPI_ENV;
	GLuint program = glCreateProgram();
	RET_NUM(program);
}


DBG_EXPORT JS_METHOD(deleteProgram) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	glDeleteProgram(program);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isProgram) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	RET_BOOL(glIsProgram(program) != 0);
}


DBG_EXPORT JS_METHOD(getProgramInfoLog) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	char buffer[PROG_LOG_SIZE_MAX];
	glGetProgramInfoLog(program, PROG_LOG_SIZE_MAX, nullptr, buffer);
	
	RET_STR(buffer);
}

DBG_EXPORT JS_METHOD(getProgramParameter) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, name);
	
	GLint value;
	
	switch (name) {
	
	case GL_DELETE_STATUS:
	case GL_LINK_STATUS:
	case GL_VALIDATE_STATUS:
		glGetProgramiv(program, name, &value);
		RET_BOOL(value != 0);
	
	case GL_ATTACHED_SHADERS:
	case GL_TRANSFORM_FEEDBACK_BUFFER_MODE:
	case GL_ACTIVE_ATTRIBUTES:
	case GL_ACTIVE_UNIFORMS:
	case GL_ACTIVE_UNIFORM_BLOCKS:
	case GL_INFO_LOG_LENGTH:
	case GL_TRANSFORM_FEEDBACK_VARYINGS:
		glGetProgramiv(program, name, &value);
		RET_NUM(value);
	
	default:
		RET_NULL;
	}
}


DBG_EXPORT JS_METHOD(linkProgram) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	glLinkProgram(program);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(useProgram) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	glUseProgram(program);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(validateProgram) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	glValidateProgram(program);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(programParameteri) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, pname);
	REQ_INT32_ARG(2, value);
	
	if (pname != GL_PROGRAM_BINARY_RETRIEVABLE_HINT) {
		RET_WEBGL_VOID;
	}
	glProgramParameteri(program, pname, value);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getFragDataLocation) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	GLint result = glGetFragDataLocation(program, name.c_str());
	RET_NUM(result);
}

DBG_EXPORT JS_METHOD(getProgramBinary) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	GLenum format = 0;
	char buffer[BINARY_SIZE_MAX];
	glGetProgramBinary(program, BINARY_SIZE_MAX, nullptr, &format, buffer);
	
	Napi::Object res = JS_OBJECT;
	res.Set("binary", JS_STR(buffer));
	res.Set("binaryFormat", JS_NUM(format));
	RET_VALUE(res);
}

DBG_EXPORT JS_METHOD(programBinary) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, binaryFormat);
	REQ_STR_ARG(2, binary);
	
	glProgramBinary(program, binaryFormat, binary.c_str(), binary.length());
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getUniformBlockIndex) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	GLuint result = glGetUniformBlockIndex(program, name.c_str());
	RET_NUM(result);
}


DBG_EXPORT JS_METHOD(getUniformIndices) { NAPI_ENV;
	LET_ID_ARG(0, program);
	LET_ARRAY_STR_ARG(1, names);
	
	uint32_t count = std::min(PROG_UNIFORM_COUNT_MAX, names.size());
	const GLchar* cppNames[PROG_UNIFORM_COUNT_MAX];
	GLuint outIndices[PROG_UNIFORM_COUNT_MAX];
	
	for (uint32_t i = 0; i < count; i++) {
		cppNames[i] = names[i].c_str();
	}
	
	glGetUniformIndices(program, count, cppNames, outIndices);
	
	Napi::Array arr = JS_ARRAY;
	for (uint32_t i = 0; i < count; i++) {
		arr.Set(i, JS_NUM(outIndices[i]));
	}
	
	RET_VALUE(arr);
}

} // namespace webgl
