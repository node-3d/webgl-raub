#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createTexture) {
	
	GLuint texture;
	glGenTextures(1, &texture);
	
	RET_VALUE(Nan::New<Number>(texture));
	
}


NAN_METHOD(deleteTexture) {
	
	REQ_UINT32_ARG(0, texture);
	
	glDeleteTextures(1, reinterpret_cast<GLuint*>(&texture));
	
}


NAN_METHOD(isTexture) {
	
	REQ_UINT32_ARG(0, texture);
	
	RET_VALUE(JS_BOOL(glIsTexture(texture) != 0));
	
}


NAN_METHOD(generateMipmap) {
	
	REQ_INT32_ARG(0, target);
	
	glGenerateMipmap(target);
	
}


NAN_METHOD(bindTexture) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, texture);
	
	glBindTexture(target, texture);
	
}


NAN_METHOD(texImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, width);
	REQ_INT32_ARG(4, height);
	REQ_INT32_ARG(5, border);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	
	if (info.Length() <= 8 || info[8]->IsNullOrUndefined()) {
		glTexImage2D(target, level, internalformat, width, height, border, format, type, nullptr);
		return;
	}
	
	REQ_OBJ_ARG(8, image);
	
	void *pixels = getData(image);
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	
}


NAN_METHOD(texParameteri) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_INT32_ARG(2, param);
	
	glTexParameteri(target, name, param);
	
}


NAN_METHOD(texParameterf) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_FLOAT_ARG(2, param);
	
	glTexParameterf(target, name, param);
	
}


NAN_METHOD(framebufferTexture2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, textarget);
	REQ_INT32_ARG(3, texture);
	REQ_INT32_ARG(4, level);
	
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	
}


NAN_METHOD(activeTexture) {
	
	REQ_INT32_ARG(0, id);
	
	glActiveTexture(id);
	
}


NAN_METHOD(copyTexImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, x);
	REQ_INT32_ARG(4, y);
	REQ_INT32_ARG(5, width);
	REQ_INT32_ARG(6, height);
	REQ_INT32_ARG(7, border);
	
	glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	
}


NAN_METHOD(copyTexSubImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, x);
	REQ_INT32_ARG(5, y);
	REQ_INT32_ARG(6, width);
	REQ_INT32_ARG(7, height);
	
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	
}


NAN_METHOD(texSubImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, width);
	REQ_INT32_ARG(5, height);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	
	if (info.Length() <= 8 || info[8]->IsNullOrUndefined()) {
		glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, nullptr);
		return;
	}
	
	REQ_OBJ_ARG(8, image);
	
	void *pixels = getData(image);
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	
}


NAN_METHOD(getTexParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint param_value = 0;
	glGetTexParameteriv(target, name, &param_value);
	
	RET_VALUE(Nan::New<Number>(param_value));
	
}


} // namespace webgl
