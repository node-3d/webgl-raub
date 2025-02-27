#include "webgl.hpp"


namespace webgl {

constexpr uint32_t UNIFORM_COUNT_MAX = 256;

DBG_EXPORT JS_METHOD(getActiveUniform) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[NAME_SIZE_MAX];
	GLenum type;
	GLsizei size;
	glGetActiveUniform(program, index, NAME_SIZE_MAX, nullptr, &size, &type, name);
	
	Napi::Object activeInfo = JS_OBJECT;
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
}

DBG_EXPORT JS_METHOD(getUniformLocation) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	RET_NUM(glGetUniformLocation(program, name.c_str()));
}


DBG_EXPORT JS_METHOD(uniform1f) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glUniform1f(location, x);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2f) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glUniform2f(location, x, y);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3f) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glUniform3f(location, x, y, z);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4f) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glUniform4f(location, x, y, z, w);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform1i) {
	LET_ID_ARG(0, location);
	WEAK_INT32_ARG(1, x);
	
	glUniform1i(location, x);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2i) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	
	glUniform2i(location, x, y);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3i) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	
	glUniform3i(location, x, y, z);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4i) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glUniform4i(location, x, y, z, w);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform1ui) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_UINT32_ARG(1, x);
	
	glUniform1ui(location, x);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2ui) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_UINT32_ARG(1, x);
	REQ_UINT32_ARG(2, y);
	
	glUniform2ui(location, x, y);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3ui) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_UINT32_ARG(1, x);
	REQ_UINT32_ARG(2, y);
	REQ_UINT32_ARG(3, z);
	
	glUniform3ui(location, x, y, z);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4ui) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_UINT32_ARG(1, x);
	REQ_UINT32_ARG(2, y);
	REQ_UINT32_ARG(3, z);
	REQ_UINT32_ARG(4, w);
	
	glUniform4ui(location, x, y, z, w);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform1fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	
	glUniform1fv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 2;
	
	glUniform2fv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 3;
	
	glUniform3fv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLfloat *ptr = getArrayData<GLfloat>(env, abv, &num);
	num /= 4;
	
	glUniform4fv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform1iv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	
	glUniform1iv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2iv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 2;
	
	glUniform2iv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3iv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 3;
	
	glUniform3iv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4iv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLint *ptr = getArrayData<GLint>(env, abv, &num);
	num /= 4;
	
	glUniform4iv(location, num, ptr);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniform1uiv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLuint *ptr = getArrayData<GLuint>(env, abv, &num);
	
	glUniform1uiv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform2uiv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLuint *ptr = getArrayData<GLuint>(env, abv, &num);
	num /= 2;
	
	glUniform2uiv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform3uiv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLuint *ptr = getArrayData<GLuint>(env, abv, &num);
	num /= 3;
	
	glUniform3uiv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniform4uiv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	int num;
	GLuint *ptr = getArrayData<GLuint>(env, abv, &num);
	num /= 4;
	
	glUniform4uiv(location, num, ptr);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(uniformMatrix2fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 4) {
		JS_THROW("Not enough data for `uniformMatrix2fv`.");
	} else {
		glUniformMatrix2fv(location, count / 4, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix2x3fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 6) {
		JS_THROW("Not enough data for `uniformMatrix2x3fv`.");
	} else {
		glUniformMatrix2x3fv(location, count / 6, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix2x4fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 8) {
		JS_THROW("Not enough data for `uniformMatrix2x4fv`.");
	} else {
		glUniformMatrix2x4fv(location, count / 8, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix3fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 9) {
		JS_THROW("Not enough data for `uniformMatrix3fv`.");
	} else {
		glUniformMatrix3fv(location, count / 9, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix3x2fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 6) {
		JS_THROW("Not enough data for `uniformMatrix3x2fv`.");
	} else {
		glUniformMatrix3x2fv(location, count / 6, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix3x4fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 12) {
		JS_THROW("Not enough data for `uniformMatrix3x4fv`.");
	} else {
		glUniformMatrix3x4fv(location, count / 12, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix4fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 16) {
		JS_THROW("Not enough data for `uniformMatrix4fv`.");
		RET_WEBGL_VOID;
	} else {
		glUniformMatrix4fv(location, count / 16, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix4x2fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 8) {
		JS_THROW("Not enough data for `uniformMatrix4x2fv`.");
		RET_WEBGL_VOID;
	} else {
		glUniformMatrix4x2fv(location, count / 8, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(uniformMatrix4x3fv) { NAPI_ENV;
	LET_ID_ARG(0, location);
	WEAK_BOOL_ARG(1, transpose);
	REQ_OBJ_ARG(2, abv);
	
	GLsizei count = 0;
	GLfloat* data = getArrayData<GLfloat>(env, abv, &count);
	
	if (count < 12) {
		JS_THROW("Not enough data for `uniformMatrix4x3fv`.");
		RET_WEBGL_VOID;
	} else {
		glUniformMatrix4x3fv(location, count / 12, transpose, data);
	}
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getUniformfv) { NAPI_ENV;
	LET_ID_ARG(0, program);
	LET_ID_ARG(1, location);
	
	if (location < 0) {
		RET_WEBGL_VOID;
	}
	
	float data[16]; // worst case scenario is 16 floats
	glGetUniformfv(program, location, data);
	
	Napi::Array arr = JS_ARRAY;
	for (int i = 0; i < 16; i++) {
		arr.Set(i, JS_NUM(data[i]));
	}
	
	RET_VALUE(arr);
}

static inline bool isArrayName(const char *name, GLsizei nameLen) {
	if (nameLen < 4) {
		return false;
	}
	GLsizei cmpIdx = nameLen - 3;
	return (
		name[cmpIdx + 0] == '[' &&
		name[cmpIdx + 1] == '0' &&
		name[cmpIdx + 2] == ']'
	);
}

// https://chromium.googlesource.com/chromium/blink/+/refs/heads/main/Source/modules/webgl/WebGLRenderingContextBase.cpp
DBG_EXPORT JS_METHOD(getUniform) { NAPI_ENV;
	LET_ID_ARG(0, program);
	LET_ID_ARG(1, location);
	
	GLint activeUniforms = 0;
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &activeUniforms);
	
	for (GLint i = 0; i < activeUniforms; i++) {
		GLint size;
		GLsizei nameLen;
		GLenum typeUniform;
		GLchar nameBuf[200];
		glGetActiveUniform(
			program, i, 200, &nameLen, &size, &typeUniform, nameBuf
		);
		
		std::string name = std::string(nameBuf);
		
		// Strip "[0]" from the name if it's an array.
		if (size > 1 && isArrayName(nameBuf, nameLen)) {
			name = name.substr(0, nameLen - 3);
		}
		
		// If it's an array, we need to iterate through each element, appending "[index]" to the name.
		for (GLint index = 0; index < size; ++index) {
			std::string indexedName = name;
			if (size > 1 && index >= 1) {
				indexedName.append("[");
				indexedName.append(std::to_string(index));
				indexedName.append("]");
			}
			// Now need to look this up by name again to find its location
			GLint loc = glGetUniformLocation(program, indexedName.c_str());
			if (loc == static_cast<GLint>(location)) {
				// Found it. Use the type in the ActiveInfo to determine the return type.
				GLenum baseType;
				unsigned length;
				switch (typeUniform) {
				case GL_BOOL:
					baseType = GL_BOOL;
					length = 1;
					break;
				case GL_BOOL_VEC2:
					baseType = GL_BOOL;
					length = 2;
					break;
				case GL_BOOL_VEC3:
					baseType = GL_BOOL;
					length = 3;
					break;
				case GL_BOOL_VEC4:
					baseType = GL_BOOL;
					length = 4;
					break;
				case GL_INT:
					baseType = GL_INT;
					length = 1;
					break;
				case GL_INT_VEC2:
					baseType = GL_INT;
					length = 2;
					break;
				case GL_INT_VEC3:
					baseType = GL_INT;
					length = 3;
					break;
				case GL_INT_VEC4:
					baseType = GL_INT;
					length = 4;
					break;
				case GL_FLOAT:
					baseType = GL_FLOAT;
					length = 1;
					break;
				case GL_FLOAT_VEC2:
					baseType = GL_FLOAT;
					length = 2;
					break;
				case GL_FLOAT_VEC3:
					baseType = GL_FLOAT;
					length = 3;
					break;
				case GL_FLOAT_VEC4:
					baseType = GL_FLOAT;
					length = 4;
					break;
				case GL_FLOAT_MAT2:
					baseType = GL_FLOAT;
					length = 4;
					break;
				case GL_FLOAT_MAT3:
					baseType = GL_FLOAT;
					length = 9;
					break;
				case GL_FLOAT_MAT4:
					baseType = GL_FLOAT;
					length = 16;
					break;
				case GL_SAMPLER_2D:
				case GL_SAMPLER_CUBE:
					baseType = GL_INT;
					length = 1;
					break;
				default:
					// handle GLenums for WebGL 2.0 or higher
					switch (typeUniform) {
					case GL_UNSIGNED_INT:
						baseType = GL_UNSIGNED_INT;
						length = 1;
						break;
					case GL_UNSIGNED_INT_VEC2:
						baseType = GL_UNSIGNED_INT;
						length = 2;
						break;
					case GL_UNSIGNED_INT_VEC3:
						baseType = GL_UNSIGNED_INT;
						length = 3;
						break;
					case GL_UNSIGNED_INT_VEC4:
						baseType = GL_UNSIGNED_INT;
						length = 4;
						break;
					case GL_FLOAT_MAT2x3:
						baseType = GL_FLOAT;
						length = 6;
						break;
					case GL_FLOAT_MAT2x4:
						baseType = GL_FLOAT;
						length = 8;
						break;
					case GL_FLOAT_MAT3x2:
						baseType = GL_FLOAT;
						length = 6;
						break;
					case GL_FLOAT_MAT3x4:
						baseType = GL_FLOAT;
						length = 12;
						break;
					case GL_FLOAT_MAT4x2:
						baseType = GL_FLOAT;
						length = 8;
						break;
					case GL_FLOAT_MAT4x3:
						baseType = GL_FLOAT;
						length = 12;
						break;
					case GL_SAMPLER_3D:
					case GL_SAMPLER_2D_ARRAY:
						baseType = GL_INT;
						length = 1;
						break;
					default:
						RET_NULL;
					}
				}
				switch (baseType) {
				case GL_FLOAT: {
					GLfloat value[16] = {0};
					glGetUniformfv(program, location, value);
					if (length == 1) {
						RET_NUM(value[0]);
					}
					
					Napi::Float32Array result = Napi::Float32Array::New(env, length, napi_float32_array);
					for (unsigned j = 0; j < length; j++) {
						result[j] = value[j];
					}
					RET_VALUE(result);
				}
				case GL_INT: {
					GLint value[4] = {0};
					glGetUniformiv(program, location, value);
					if (length == 1) {
						RET_NUM(value[0]);
					}
					
					Napi::Int32Array result = Napi::Int32Array::New(env, length, napi_int32_array);
					for (unsigned j = 0; j < length; j++) {
						result[j] = value[j];
					}
					RET_VALUE(result);
				}
				case GL_UNSIGNED_INT: {
					GLuint value[4] = {0};
					glGetUniformuiv(program, location, value);
					if (length == 1) {
						RET_NUM(value[0]);
					}
					
					Napi::Uint32Array result = Napi::Uint32Array::New(env, length, napi_uint32_array);
					for (unsigned j = 0; j < length; j++) {
						result[j] = value[j];
					}
					RET_VALUE(result);
				}
				case GL_BOOL: {
					GLint value[4] = {0};
					glGetUniformiv(program, location, value);
					if (length == 1) {
						RET_BOOL(value[0] != 0);
					}
					
					Napi::Array result = JS_ARRAY;
					for (unsigned j = 0; j < length; j++) {
						result.Set(j, JS_BOOL(value[j] != 0));
					}
					RET_VALUE(result);
				}
				default:
					RET_NULL;
				}
			}
		}
	}
	
	RET_NULL;
}

DBG_EXPORT JS_METHOD(getActiveUniforms) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_ARRAY_ARG(1, jsIndices);
	REQ_INT32_ARG(2, pname);
	
	uint32_t count = std::min(UNIFORM_COUNT_MAX, jsIndices.Length());
	GLuint indices[UNIFORM_COUNT_MAX];
	GLint outParams[UNIFORM_COUNT_MAX];
	
	for (uint32_t i = 0; i < count; ++i) {
		indices[i] = 0;
	}
	
	glGetActiveUniformsiv(program, count, indices, pname, outParams);
	
	Napi::Array result = JS_ARRAY;
	for (uint32_t j = 0; j < count; j++) {
		result.Set(j, outParams[j]);
	}
	RET_VALUE(result);
}

DBG_EXPORT JS_METHOD(uniformBlockBinding) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_UINT32_ARG(1, uniformBlockIndex);
	REQ_UINT32_ARG(2, uniformBlockBinding);
	
	glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getActiveUniformBlockParameter) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_UINT32_ARG(1, uniformBlockIndex);
	REQ_UINT32_ARG(2, pname);
	
	switch (pname) {
	case GL_UNIFORM_BLOCK_BINDING:
	case GL_UNIFORM_BLOCK_DATA_SIZE:
	case GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS: {
		GLint intValue = 0;
		glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, &intValue);
		RET_NUM(intValue);
	}
	case GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES: {
		GLint uniformCount = 0;
		glGetActiveUniformBlockiv(program, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &uniformCount);
		
		GLint indices[UNIFORM_COUNT_MAX];
		glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, indices);
		
		Napi::Uint32Array result = Napi::Uint32Array::New(env, uniformCount, napi_uint32_array);
		for (GLint j = 0; j < uniformCount; j++) {
			result[j] = indices[j];
		}
		RET_VALUE(result);
	}
	case GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER:
	case GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER: {
		GLint boolValue = 0;
		glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, &boolValue);
		RET_BOOL(boolValue != 0);
	}
	default:
		RET_NULL;
	}
}

DBG_EXPORT JS_METHOD(getActiveUniformBlockName) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_UINT32_ARG(1, uniformBlockIndex);
	
	char buffer[NAME_SIZE_MAX];
	glGetActiveUniformBlockName(program, uniformBlockIndex, NAME_SIZE_MAX, nullptr, buffer);
	
	RET_STR(buffer);
}

} // namespace webgl
