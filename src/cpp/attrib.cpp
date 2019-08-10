#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(bindAttribLocation) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	REQ_STR_ARG(2, name);
	
	glBindAttribLocation(program, index, *name);
	RET_UNDEFINED;
	
}


JS_METHOD(disableVertexAttribArray) { NAPI_ENV;
	
	REQ_INT32_ARG(0, index);
	
	glDisableVertexAttribArray(index);
	RET_UNDEFINED;
	
}


JS_METHOD(enableVertexAttribArray) { NAPI_ENV;
	
	REQ_INT32_ARG(0, id);
	
	glEnableVertexAttribArray(id);
	RET_UNDEFINED;
	
}


JS_METHOD(getActiveAttrib) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length = 0;
	GLenum type;
	GLsizei size;
	glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);
	
	Napi::Array activeInfo = Napi::Array::New(env);
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


JS_METHOD(getAttribLocation) { NAPI_ENV;
	
	REQ_INT32_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	RET_NUM(glGetAttribLocation(program, *name));
	
}


#define CASES_VERTEX_ATTR_BOOL case GL_VERTEX_ATTRIB_ARRAY_ENABLED: \
	case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:

#define CASES_VERTEX_ATTR_INT case GL_VERTEX_ATTRIB_ARRAY_SIZE: \
	case GL_VERTEX_ATTRIB_ARRAY_STRIDE: \
	case GL_VERTEX_ATTRIB_ARRAY_TYPE: \
	case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:

#define CASES_VERTEX_ATTR_FLOAT4 case GL_CURRENT_VERTEX_ATTRIB:


JS_METHOD(getVertexAttrib) { NAPI_ENV;
	
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, pname);
	
	GLint value = 0;
	float vextex_attribs[4];
	Napi::Array arr;
	
	switch (pname) {
	
	CASES_VERTEX_ATTR_BOOL
		glGetVertexAttribiv(index, pname, &value);
		RET_BOOL(value != 0);
		break;
	
	CASES_VERTEX_ATTR_INT
		glGetVertexAttribiv(index, pname, &value);
		RET_INT(value);
		break;
	
	CASES_VERTEX_ATTR_FLOAT4
		glGetVertexAttribfv(index, pname, vextex_attribs);
		arr = Napi::Array::New(env);
		arr.Set(0, JS_NUM(vextex_attribs[0]));
		arr.Set(1, JS_NUM(vextex_attribs[1]));
		arr.Set(2, JS_NUM(vextex_attribs[2]));
		arr.Set(3, JS_NUM(vextex_attribs[3]));
		RET_VALUE(arr);
		break;
	
	default:
		Nan::ThrowError("GetVertexAttrib: Invalid Enum");
	
	}
	
}


JS_METHOD(getVertexAttribOffset) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, index);
	REQ_INT32_ARG(1, name);
	
	void *ret = NULL;
	glGetVertexAttribPointerv(index, name, &ret);
	
	RET_INT(ToGLuint(ret));
	
}


JS_METHOD(vertexAttrib1f) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glVertexAttrib1f(location, x);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib1fv) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib1fv(location, data);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib2f) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glVertexAttrib2f(location, x, y);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib2fv) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib2fv(location, data);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib3f) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glVertexAttrib3f(location, x, y, z);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib3fv) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib3fv(location, data);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib4f) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glVertexAttrib4f(location, x, y, z, w);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttrib4fv) { NAPI_ENV;
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib4fv(location, data);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttribPointer) { NAPI_ENV;
	
	REQ_INT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	LET_BOOL_ARG(3, normalized);
	REQ_INT32_ARG(4, stride);
	REQ_OFFS_ARG(5, offset);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);
	
	glVertexAttribPointer(indx, size, type, normalized, stride, vertices);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttribIPointer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	REQ_UINT32_ARG(3, stride);
	REQ_OFFS_ARG(4, offset);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);
	
	glVertexAttribIPointer(indx, size, type, stride, vertices);
	RET_UNDEFINED;
	
}


} // namespace webgl
