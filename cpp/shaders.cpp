#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createShader) {
	
	REQ_INT32_ARG(0, id);
	
	GLuint shader = glCreateShader(id);
	
	RET_VALUE(Nan::New<Number>(shader));
	
}


NAN_METHOD(deleteShader) {
	
	REQ_UINT32_ARG(0, shader);
	
	glDeleteShader(shader);
	
}


NAN_METHOD(detachShader) {
	
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, shader);
	
	glDetachShader(program, shader);
	
}


NAN_METHOD(isShader) {
	
	REQ_UINT32_ARG(0, shader);
	
	RET_VALUE(JS_BOOL(glIsShader(shader) != 0));
	
}


NAN_METHOD(shaderSource) {
	
	REQ_INT32_ARG(0, id);
	REQ_UTF8_ARG(1, code);
	
	const char* codes[1];
	codes[0] = *code;
	GLint length = code.length();
	
	glShaderSource(id, 1, codes, &length);
	
}


NAN_METHOD(compileShader) {
	
	REQ_INT32_ARG(0, id);
	
	glCompileShader(id);
	
}


#define CASES_SHADER_PARAM_BOOL case GL_DELETE_STATUS: \
	case GL_COMPILE_STATUS:

#define CASES_SHADER_PARAM_NUMBER case GL_SHADER_TYPE: \
	case GL_INFO_LOG_LENGTH: \
	case GL_SHADER_SOURCE_LENGTH:

NAN_METHOD(getShaderParameter) {
	
	REQ_INT32_ARG(0, shader);
	REQ_INT32_ARG(1, pname);
	
	int value = 0;
	
	switch (pname) {
	
	CASES_SHADER_PARAM_BOOL
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_BOOL(static_cast<bool>(value != 0)));
		break;
	
	CASES_SHADER_PARAM_NUMBER
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_NUM(static_cast<double>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetShaderParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(getShaderInfoLog) {
	
	REQ_INT32_ARG(0, id);
	
	int Len = 1024;
	char Error[1024];
	glGetShaderInfoLog(id, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


NAN_METHOD(attachShader) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, shader);
	
	glAttachShader(program, shader);
	
}


NAN_METHOD(getShaderSource) {
	
	REQ_INT32_ARG(0, shader);
	
	GLint len;
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
	GLchar *source = new GLchar[len];
	glGetShaderSource(shader, len, NULL, source);
	
	Local<String> str = JS_STR(source);
	delete [] source;
	
	RET_VALUE(str);
	
}


NAN_METHOD(getAttachedShaders) {
	
	REQ_INT32_ARG(0, program);
	
	GLuint shaders[1024];
	GLsizei count;
	glGetAttachedShaders(program, 1024, &count, shaders);
	
	Local<Array> shadersArr = Nan::New<Array>(count);
	for (int i = 0; i < count; i++) {
		shadersArr->Set(i, JS_INT(static_cast<int>(shaders[i])));
	}
	
	RET_VALUE(shadersArr);
	
}


} // namespace webgl
