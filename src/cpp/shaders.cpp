#include "webgl.hpp"


namespace webgl {

constexpr size_t SOURCE_SIZE_MAX = 10 * 1024;
constexpr uint32_t COUNT_SHADERS_MAX = 64;
constexpr size_t SHADER_LOG_SIZE_MAX = 5 * 1024;


DBG_EXPORT JS_METHOD(createShader) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	GLuint shader = glCreateShader(id);
	
	RET_NUM(shader);
}


DBG_EXPORT JS_METHOD(deleteShader) {
	LET_ID_ARG(0, shader);
	
	glDeleteShader(shader);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isShader) { NAPI_ENV;
	LET_ID_ARG(0, shader);
	
	RET_BOOL(glIsShader(shader) != 0);
}


DBG_EXPORT JS_METHOD(attachShader) {
	LET_ID_ARG(0, program);
	LET_ID_ARG(1, shader);
	
	glAttachShader(program, shader);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(compileShader) {
	LET_ID_ARG(0, shader);
	
	glCompileShader(shader);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(detachShader) {
	LET_ID_ARG(0, program);
	LET_ID_ARG(1, shader);
	
	glDetachShader(program, shader);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getAttachedShaders) { NAPI_ENV;
	LET_ID_ARG(0, program);
	
	GLuint shaders[COUNT_SHADERS_MAX];
	GLsizei count;
	glGetAttachedShaders(program, COUNT_SHADERS_MAX, &count, shaders);
	
	Napi::Array shadersArr = JS_ARRAY;
	for (int i = 0; i < count; i++) {
		shadersArr.Set(i, JS_NUM(static_cast<int>(shaders[i])));
	}
	
	RET_VALUE(shadersArr);
}


DBG_EXPORT JS_METHOD(getShaderInfoLog) { NAPI_ENV;
	LET_ID_ARG(0, shader);
	
	char error[SHADER_LOG_SIZE_MAX];
	glGetShaderInfoLog(shader, SHADER_LOG_SIZE_MAX, nullptr, error);
	
	RET_STR(error);
}


#define CASES_SHADER_PARAM_BOOL case GL_DELETE_STATUS: \
	case GL_COMPILE_STATUS:

#define CASES_SHADER_PARAM_NUMBER case GL_SHADER_TYPE: \
	case GL_INFO_LOG_LENGTH: \
	case GL_SHADER_SOURCE_LENGTH:

DBG_EXPORT JS_METHOD(getShaderParameter) { NAPI_ENV;
	LET_ID_ARG(0, shader);
	REQ_INT32_ARG(1, pname);
	
	int value = 0;
	
	switch (pname) {
	
	CASES_SHADER_PARAM_BOOL
		glGetShaderiv(shader, pname, &value);
		RET_BOOL(value != 0);
		break;
	
	CASES_SHADER_PARAM_NUMBER
		glGetShaderiv(shader, pname, &value);
		RET_NUM(value);
		break;
	
	default:
		JS_THROW("GetShaderParameter: Invalid Enum.");
		RET_NULL;
	}
	
}


DBG_EXPORT JS_METHOD(getShaderSource) { NAPI_ENV;
	LET_ID_ARG(0, shader);
	
	char source[SOURCE_SIZE_MAX];
	glGetShaderSource(shader, SOURCE_SIZE_MAX, nullptr, source);
	
	RET_STR(source);
}


DBG_EXPORT JS_METHOD(getShaderPrecisionFormat) { NAPI_ENV;
	REQ_INT32_ARG(0, shaderType);
	REQ_INT32_ARG(1, precisionType);
	
	GLint lowHigh[2];
	GLint precision;
	
	glGetShaderPrecisionFormat(shaderType, precisionType, lowHigh, &precision);
	
	Napi::Object res = JS_OBJECT;
	res.Set("rangeMin", JS_NUM(lowHigh[0]));
	res.Set("rangeMax", JS_NUM(lowHigh[1]));
	res.Set("precision", JS_NUM(precision));
	
	RET_VALUE(res);
}


DBG_EXPORT JS_METHOD(shaderSource) { NAPI_ENV;
	LET_ID_ARG(0, shader);
	REQ_STR_ARG(1, code);
	
	const char *strings = code.c_str();
	GLint lengths = code.length();
	
	glShaderSource(shader, 1, &strings, &lengths);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(releaseShaderCompiler) {
	glReleaseShaderCompiler();
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(shaderBinary) { NAPI_ENV;
	REQ_ARRAY_ARG(0, jsShaders);
	REQ_INT32_ARG(1, binaryFormat);
	REQ_STR_ARG(2, binary);
	
	GLuint cppShaders[COUNT_SHADERS_MAX];
	uint32_t shaderCount = std::min(COUNT_SHADERS_MAX, jsShaders.Length());
	
	for (uint32_t i = 0; i < shaderCount; i++) {
		cppShaders[i] = extractId(jsShaders.Get(i).As<Napi::Object>());
	}
	
	glShaderBinary(
		shaderCount, cppShaders, binaryFormat, binary.c_str(), binary.length()
	);
	RET_WEBGL_VOID;
}

} // namespace webgl
