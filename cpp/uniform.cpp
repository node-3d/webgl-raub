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

NAN_METHOD(uniform1f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glUniform1f(location, x);
	
}


NAN_METHOD(uniform2f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glUniform2f(location, x, y);
	
}


NAN_METHOD(uniform3f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glUniform3f(location, x, y, z);
	
}


NAN_METHOD(uniform4f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glUniform4f(location, x, y, z, w);
	
}


NAN_METHOD(uniform1i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	
	glUniform1i(location, x);
	
}


NAN_METHOD(uniform2i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	
	glUniform2i(location, x, y);
	
}


NAN_METHOD(uniform3i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	
	glUniform3i(location, x, y, z);
	
}


NAN_METHOD(uniform4i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glUniform4i(location, x, y, z, w);
	
}


NAN_METHOD(uniform1fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(abv, &num);
	
	glUniform1fv(location, num, ptr);
	
}


NAN_METHOD(uniform2fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(abv, &num);
	num /= 2;
	
	glUniform2fv(location, num, ptr);
	
}


NAN_METHOD(uniform3fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(abv, &num);
	num /= 3;
	
	glUniform3fv(location, num, ptr);
	
}


NAN_METHOD(uniform4fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(abv, &num);
	num /= 4;
	
	glUniform4fv(location, num, ptr);
	
}


NAN_METHOD(uniform1iv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(abv, &num);
	
	glUniform1iv(location, num, ptr);
	
}


NAN_METHOD(uniform2iv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(abv, &num);
	num /= 2;
	
	glUniform2iv(location, num, ptr);
	
}


NAN_METHOD(uniform3iv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(abv, &num);
	num /= 3;
	
	glUniform3iv(location, num, ptr);
	
}


NAN_METHOD(uniform4iv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(abv, &num);
	num /= 4;
	
	glUniform4iv(location, num, ptr);
	
}


NAN_METHOD(uniformMatrix2fv) {
	
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(abv, &count);
	
	if (count < 4) {
		Nan::ThrowError("Not enough data for UniformMatrix2fv");
	} else {
		glUniformMatrix2fv(location, count / 4, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(uniformMatrix3fv) {
	
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(abv, &count);
	
	if (count < 9) {
		Nan::ThrowError("Not enough data for UniformMatrix3fv");
	} else {
		glUniformMatrix3fv(location, count / 9, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(uniformMatrix4fv) {
	
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(abv, &count);
	
	if (count < 16) {
		Nan::ThrowError("Not enough data for UniformMatrix4fv");
	} else {
		glUniformMatrix4fv(location, count / 16, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(getUniformLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(1, name);
	
	RET_VALUE(JS_INT(glGetUniformLocation(program, *name)));
	
}


NAN_METHOD(getActiveUniform) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length = 0;
	GLenum type;
	GLsizei size;
	glGetActiveUniform(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT(static_cast<int>(type)));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(getUniform) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, location);
	
	if (location < 0) {
		RET_UNDEFINED;
	}
	
	float data[16]; // worst case scenario is 16 floats
	glGetUniformfv(program, location, data);
	
	Local<Array> arr = Nan::New<Array>(16);
	for (int i = 0; i < 16; i++) {
		arr->Set(i, JS_NUM(data[i]));
	}
	
	RET_VALUE(arr);
	
}


} // namespace webgl
