#include "webgl.hpp"


namespace webgl {

DBG_EXPORT JS_METHOD(bindAttribLocation) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, index);
	REQ_STR_ARG(2, name);
	
	glBindAttribLocation(program, index, name.c_str());
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(disableVertexAttribArray) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	
	glDisableVertexAttribArray(index);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(enableVertexAttribArray) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	glEnableVertexAttribArray(id);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getActiveAttrib) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[NAME_SIZE_MAX];
	GLsizei length = 0;
	GLenum type;
	GLsizei size;
	glGetActiveAttrib(program, index, NAME_SIZE_MAX, &length, &size, &type, name);
	
	Napi::Object activeInfo = JS_OBJECT;
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
}


DBG_EXPORT JS_METHOD(getAttribLocation) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_STR_ARG(1, name);
	
	RET_NUM(glGetAttribLocation(program, name.c_str()));
}


#define CASES_VERTEX_ATTR_BOOL case GL_VERTEX_ATTRIB_ARRAY_ENABLED: \
	case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:

#define CASES_VERTEX_ATTR_INT case GL_VERTEX_ATTRIB_ARRAY_SIZE: \
	case GL_VERTEX_ATTRIB_ARRAY_STRIDE: \
	case GL_VERTEX_ATTRIB_ARRAY_TYPE: \
	case GL_VERTEX_ATTRIB_ARRAY_INTEGER: \
	case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:

#define CASES_VERTEX_ATTR_FLOAT4 case GL_CURRENT_VERTEX_ATTRIB:


DBG_EXPORT JS_METHOD(getVertexAttrib) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, pname);
	
	GLint value = 0;
	
	switch (pname) {
	CASES_VERTEX_ATTR_BOOL
		glGetVertexAttribiv(index, pname, &value);
		RET_BOOL(value != 0);
	
	CASES_VERTEX_ATTR_INT
		glGetVertexAttribiv(index, pname, &value);
		RET_NUM(value);
	
	CASES_VERTEX_ATTR_FLOAT4
		{
			float vextex_attribs[4];
			glGetVertexAttribfv(index, pname, vextex_attribs);
			Napi::Array arr = JS_ARRAY;
			arr.Set(0U, JS_NUM(vextex_attribs[0]));
			arr.Set(1U, JS_NUM(vextex_attribs[1]));
			arr.Set(2U, JS_NUM(vextex_attribs[2]));
			arr.Set(3U, JS_NUM(vextex_attribs[3]));
			RET_VALUE(arr);
		}
	default:
		RET_NULL;
	}
}


DBG_EXPORT JS_METHOD(getVertexAttribOffset) { NAPI_ENV;
	REQ_UINT32_ARG(0, index);
	REQ_INT32_ARG(1, name);
	
	void *ret = NULL;
	glGetVertexAttribPointerv(index, name, &ret);
	
	RET_NUM(reinterpret_cast<size_t>(ret));
}


DBG_EXPORT JS_METHOD(vertexAttrib1f) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_FLOAT_ARG(1, x);
	
	glVertexAttrib1f(index, x);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib1fv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(env, abv);
	
	glVertexAttrib1fv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib2f) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glVertexAttrib2f(index, x, y);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib2fv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(env, abv);
	
	glVertexAttrib2fv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib3f) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glVertexAttrib3f(index, x, y, z);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib3fv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(env, abv);
	
	glVertexAttrib3fv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib4f) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glVertexAttrib4f(index, x, y, z, w);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttrib4fv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(env, abv);
	
	glVertexAttrib4fv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttribI4i) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glVertexAttribI4i(index, x, y, z, w);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(vertexAttribI4iv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLint *data = getArrayData<GLint>(env, abv);
	
	glVertexAttribI4iv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttribI4ui) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_UINT32_ARG(1, x);
	REQ_UINT32_ARG(2, y);
	REQ_UINT32_ARG(3, z);
	REQ_UINT32_ARG(4, w);
	
	glVertexAttribI4ui(index, x, y, z, w);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(vertexAttribI4uiv) { NAPI_ENV;
	REQ_INT32_ARG(0, index);
	REQ_OBJ_ARG(1, abv);
	
	GLuint *data = getArrayData<GLuint>(env, abv);
	
	glVertexAttribI4uiv(index, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttribPointer) { NAPI_ENV;
	REQ_INT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	WEAK_BOOL_ARG(3, normalized);
	REQ_INT32_ARG(4, stride);
	REQ_OFFS_ARG(5, offset);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);
	
	glVertexAttribPointer(indx, size, type, normalized, stride, vertices);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(vertexAttribIPointer) { NAPI_ENV;
	REQ_UINT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	REQ_UINT32_ARG(3, stride);
	REQ_OFFS_ARG(4, offset);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);
	
	glVertexAttribIPointer(indx, size, type, stride, vertices);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(vertexAttribDivisor) { NAPI_ENV;
	REQ_UINT32_ARG(0, index);
	REQ_UINT32_ARG(1, divisor);
	
	glVertexAttribDivisor(index, divisor);
	RET_WEBGL_VOID;
}

} // namespace webgl
