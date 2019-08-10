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


NAN_METHOD(bindTexture) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, texture);
	
	glBindTexture(target, texture);
	
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


NAN_METHOD(generateMipmap) {
	
	REQ_INT32_ARG(0, target);
	
	glGenerateMipmap(target);
	
}


NAN_METHOD(getTexParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint param_value = 0;
	glGetTexParameteriv(target, name, &param_value);
	
	RET_VALUE(Nan::New<Number>(param_value));
	
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
	} else if (info[8]->IsNumber()) {
		// In WebGL2 the last parameter can be a byte offset if glBindBuffer()
		// was called with GL_PIXEL_UNPACK_BUFFER prior to glTexImage2D
		REQ_OFFS_ARG(8, offset);
		// From https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glBindBuffer.xhtml:
		// "The pointer parameter is interpreted as an offset within the buffer object measured in
		//  basic machine units."
		glTexImage2D(target, level, internalformat,
					 width, height, border, format, type,
					 reinterpret_cast<void *>(offset));
	} else {
		REQ_OBJ_ARG(8, image);
		
		void *ptr = getData(image);
		glTexImage2D(target, level, internalformat, width, height, border, format, type, ptr);
	}
	
}


NAN_METHOD(texParameterf) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_FLOAT_ARG(2, param);
	
	glTexParameterf(target, name, param);
	
}


NAN_METHOD(texParameteri) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_INT32_ARG(2, param);
	
	glTexParameteri(target, name, param);
	
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


} // namespace webgl
