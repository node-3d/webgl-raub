#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createFramebuffer) {
	
	GLuint buffer;
	glGenFramebuffers(1, &buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(deleteFramebuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteFramebuffers(1, reinterpret_cast<GLuint*>(&buffer));
	
}


NAN_METHOD(isFramebuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsFramebuffer(buffer) != 0));
	
}


NAN_METHOD(bindFramebuffer) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindFramebuffer(target, buffer);
	
}


NAN_METHOD(bindFrameBuffer) {
	
	REQ_UINT32_ARG(0, fbo);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
}


NAN_METHOD(blitFrameBuffer) {
	
	REQ_UINT32_ARG(0, fbo1);
	REQ_UINT32_ARG(1, fbo2);
	REQ_UINT32_ARG(2, sw);
	REQ_UINT32_ARG(3, sh);
	REQ_UINT32_ARG(4, dw);
	REQ_UINT32_ARG(5, dh);
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo1);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fbo2);
	
	glBlitFramebuffer(0, 0, sw, sh, 0, 0, dw, dh, GL_COLOR_BUFFER_BIT, GL_LINEAR);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
}


NAN_METHOD(checkFramebufferStatus) {
	
	REQ_INT32_ARG(0, target);
	
	RET_VALUE(JS_INT(static_cast<int>(glCheckFramebufferStatus(target))));
	
}


NAN_METHOD(framebufferRenderbuffer) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, renderbuffertarget);
	REQ_UINT32_ARG(3, renderbuffer);
	
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	
}


NAN_METHOD(framebufferTexture2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, textarget);
	REQ_INT32_ARG(3, texture);
	REQ_INT32_ARG(4, level);
	
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	
}


NAN_METHOD(getFramebufferAttachmentParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, name);
	
	GLint params;
	glGetFramebufferAttachmentParameteriv(target, attachment, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


} // namespace webgl
