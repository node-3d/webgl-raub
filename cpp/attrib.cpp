#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(bindAttribLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	REQ_UTF8_ARG(2, name);
	
	glBindAttribLocation(program, index, *name);
	
}


NAN_METHOD(disableVertexAttribArray) {
	
	REQ_INT32_ARG(0, index);
	
	glDisableVertexAttribArray(index);
	
}


NAN_METHOD(enableVertexAttribArray) {
	
	REQ_INT32_ARG(0, id);
	
	glEnableVertexAttribArray(id);
	
}


NAN_METHOD(getActiveAttrib) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length = 0;
	GLenum type;
	GLsizei size;
	glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT(static_cast<int>(type)));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(getAttribLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(1, name);
	
	RET_VALUE(Nan::New<Number>(glGetAttribLocation(program, *name)));
	
}


#define CASES_VERTEX_ATTR_BOOL case GL_VERTEX_ATTRIB_ARRAY_ENABLED: \
	case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:

#define CASES_VERTEX_ATTR_INT case GL_VERTEX_ATTRIB_ARRAY_SIZE: \
	case GL_VERTEX_ATTRIB_ARRAY_STRIDE: \
	case GL_VERTEX_ATTRIB_ARRAY_TYPE: \
	case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:

#define CASES_VERTEX_ATTR_FLOAT4 case GL_CURRENT_VERTEX_ATTRIB:


NAN_METHOD(getVertexAttrib) {
	
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, pname);
	
	GLint value = 0;
	float vextex_attribs[4];
	Local<Array> arr;
	
	switch (pname) {
	
	CASES_VERTEX_ATTR_BOOL
		glGetVertexAttribiv(index, pname, &value);
		RET_VALUE(JS_BOOL(value != 0));
		break;
	
	CASES_VERTEX_ATTR_INT
		glGetVertexAttribiv(index, pname, &value);
		RET_VALUE(JS_INT(value));
		break;
	
	CASES_VERTEX_ATTR_FLOAT4
		glGetVertexAttribfv(index, pname, vextex_attribs);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_NUM(vextex_attribs[0]));
		arr->Set(1, JS_NUM(vextex_attribs[1]));
		arr->Set(2, JS_NUM(vextex_attribs[2]));
		arr->Set(3, JS_NUM(vextex_attribs[3]));
		RET_VALUE(arr);
		break;
	
	default:
		Nan::ThrowError("GetVertexAttrib: Invalid Enum");
	
	}
	
}


NAN_METHOD(getVertexAttribOffset) {
	
	REQ_UINT32_ARG(0, index);
	REQ_INT32_ARG(1, name);
	
	void *ret = NULL;
	glGetVertexAttribPointerv(index, name, &ret);
	
	RET_VALUE(JS_INT(ToGLuint(ret)));
	
}


NAN_METHOD(vertexAttrib1f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glVertexAttrib1f(location, x);
	
}


NAN_METHOD(vertexAttrib1fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib1fv(location, data);
	
}


NAN_METHOD(vertexAttrib2f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glVertexAttrib2f(location, x, y);
	
}


NAN_METHOD(vertexAttrib2fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib2fv(location, data);
	
}


NAN_METHOD(vertexAttrib3f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glVertexAttrib3f(location, x, y, z);
	
}


NAN_METHOD(vertexAttrib3fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib3fv(location, data);
	
}


NAN_METHOD(vertexAttrib4f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glVertexAttrib4f(location, x, y, z, w);
	
}


NAN_METHOD(vertexAttrib4fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_OBJ_ARG(1, abv);
	
	GLfloat *data = getArrayData<GLfloat>(abv);
	
	glVertexAttrib4fv(location, data);
	
}


NAN_METHOD(vertexAttribPointer) {
	
	REQ_INT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	LET_BOOL_ARG(3, normalized);
	REQ_INT32_ARG(4, stride);
	REQ_OFFS_ARG(5, offset);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);
	
	// printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
	glVertexAttribPointer(indx, size, type, normalized, stride, vertices);
	
}


NAN_METHOD(vertexAttribIPointer) {
	
	REQ_UINT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	REQ_UINT32_ARG(3, stride);
	REQ_OFFS_ARG(4, offset);

	GLvoid *vertices = reinterpret_cast<GLvoid*>(offset);

	glVertexAttribIPointer(indx, size, type, stride, vertices);
}


} // namespace webgl
