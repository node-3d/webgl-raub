#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(getActiveUniform) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length = 0;
	GLenum type;
	GLsizei size;
	glGetActiveUniform(program, index, 1024, &length, &size, &type, name);
	
	Napi::Array activeInfo = JS_ARRAY;
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
}


DBG_EXPORT JS_METHOD(getUniform) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, location);
	
	if (location < 0) {
		RET_UNDEFINED;
	}
	
	float data[16]; // worst case scenario is 16 floats
	glGetUniformfv(program, location, data);
	
	Napi::Array arr = JS_ARRAY;
	for (int i = 0; i < 16; i++) {
		arr.Set(i, JS_NUM(data[i]));
	}
	
	RET_VALUE(arr);
}


DBG_EXPORT JS_METHOD(getUniformLocation) { NAPI_ENV;
	REQ_INT32_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	RET_NUM(glGetUniformLocation(program, name.c_str()));
}


DBG_EXPORT JS_METHOD(uniform1f) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glUniform1f(location, x);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform2f) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glUniform2f(location, x, y);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform3f) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glUniform3f(location, x, y, z);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform4f) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glUniform4f(location, x, y, z, w);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform1i) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	
	glUniform1i(location, x);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform2i) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	
	glUniform2i(location, x, y);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform3i) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	
	glUniform3i(location, x, y, z);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform4i) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glUniform4i(location, x, y, z, w);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform1fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	
	glUniform1fv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform2fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 2;
	
	glUniform2fv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform3fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 3;
	
	glUniform3fv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform4fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 4;
	
	glUniform4fv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform1iv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	
	glUniform1iv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform2iv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 2;
	
	glUniform2iv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform3iv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 3;
	
	glUniform3iv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniform4iv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 4;
	
	glUniform4iv(location, num, ptr);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniformMatrix2fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 4) {
		JS_THROW("Not enough data for UniformMatrix2fv.");
	} else {
		glUniformMatrix2fv(location, count / 4, transpose, data);
	}
	
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniformMatrix3fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 9) {
		JS_THROW("Not enough data for UniformMatrix3fv.");
	} else {
		glUniformMatrix3fv(location, count / 9, transpose, data);
	}
	
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(uniformMatrix4fv) { NAPI_ENV;
	REQ_INT32_ARG(0, location);
	LET_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 16) {
		JS_THROW("Not enough data for UniformMatrix4fv.");
		RET_UNDEFINED;
	} else {
		glUniformMatrix4fv(location, count / 16, transpose, data);
	}
	
	RET_UNDEFINED;
}


} // namespace webgl
