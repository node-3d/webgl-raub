#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createShader) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	GLuint shader = glCreateShader(id);
	
	RET_NUM(shader);
}


DBG_EXPORT JS_METHOD(deleteShader) { NAPI_ENV;
	REQ_UINT32_ARG(0, shader);
	
	glDeleteShader(shader);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isShader) { NAPI_ENV;
	REQ_UINT32_ARG(0, shader);
	
	RET_BOOL(glIsShader(shader) != 0);
}


DBG_EXPORT JS_METHOD(attachShader) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, shader);
	
	glAttachShader(program, shader);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(compileShader) { NAPI_ENV;
	REQ_INT32_ARG(0, shader);
	
	glCompileShader(shader);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(detachShader) { NAPI_ENV;
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, shader);
	
	glDetachShader(program, shader);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(getAttachedShaders) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	
	GLuint shaders[1024];
	GLsizei count;
	glGetAttachedShaders(program, 1024, &count, shaders);
	
	Napi::Array shadersArr = JS_ARRAY;
	for (int i = 0; i < count; i++) {
		shadersArr.Set(i, JS_NUM(static_cast<int>(shaders[i])));
	}
	
	RET_VALUE(shadersArr);
}


DBG_EXPORT JS_METHOD(getShaderInfoLog) { NAPI_ENV;
	REQ_INT32_ARG(0, shader);
	
	int len = 1024;
	char error[1024];
	glGetShaderInfoLog(shader, 1024, &len, error);
	
	RET_STR(error);
}


#define CASES_SHADER_PARAM_BOOL case GL_DELETE_STATUS: \
	case GL_COMPILE_STATUS:

#define CASES_SHADER_PARAM_NUMBER case GL_SHADER_TYPE: \
	case GL_INFO_LOG_LENGTH: \
	case GL_SHADER_SOURCE_LENGTH:

DBG_EXPORT JS_METHOD(getShaderParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, shader);
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
	REQ_INT32_ARG(0, shader);
	
	GLint len;
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
	auto source = std::make_unique<GLchar[]>(len);
	glGetShaderSource(shader, len, NULL, source.get());
	
	Napi::String str = JS_STR(source.get());
	
	RET_VALUE(str);
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
	REQ_INT32_ARG(0, shader);
	REQ_STR_ARG(1, code);
	
	const char *strings = code.c_str();
	GLint lengths = code.length();
	
	glShaderSource(shader, 1, &strings, &lengths);
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(releaseShaderCompiler) { NAPI_ENV;
	glReleaseShaderCompiler();
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(shaderBinary) { NAPI_ENV;
	REQ_INT32_ARG(0, count);
	REQ_ARRAY_ARG(1, jsShaders);
	REQ_INT32_ARG(2, binaryFormat);
	REQ_STR_ARG(3, binary);
	
	uint32_t shaderCount = jsShaders.Length();
	auto cppShaders = std::make_unique<GLuint[]>(shaderCount);
	for (uint32_t i = 0; i < shaderCount; i++) {
		cppShaders[i] = jsShaders.Get(i).As<Napi::Number>().FloatValue();
	}
	
	glShaderBinary(count, cppShaders.get(), binaryFormat, binary.c_str(), binary.length());
	RET_UNDEFINED;
}

} // namespace webgl
