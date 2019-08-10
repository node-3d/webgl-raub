#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(createFramebuffer) { NAPI_ENV;
	
	GLuint buffer;
	glGenFramebuffers(1, &buffer);
	
	RET_NUM(buffer);
	
}


JS_METHOD(deleteFramebuffer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteFramebuffers(1, reinterpret_cast<GLuint*>(&buffer));
	RET_UNDEFINED;
	
}


JS_METHOD(isFramebuffer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_BOOL(glIsFramebuffer(buffer) != 0);
	
}


JS_METHOD(bindFramebuffer) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindFramebuffer(target, buffer);
	RET_UNDEFINED;
	
}


JS_METHOD(bindFrameBuffer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, fbo);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	RET_UNDEFINED;
	
}


JS_METHOD(blitFrameBuffer) { NAPI_ENV;
	
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
	RET_UNDEFINED;
	
}


JS_METHOD(checkFramebufferStatus) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	
	RET_NUM(glCheckFramebufferStatus(target));
	
}


JS_METHOD(framebufferRenderbuffer) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, renderbuffertarget);
	REQ_UINT32_ARG(3, renderbuffer);
	
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	RET_UNDEFINED;
	
}


JS_METHOD(framebufferTexture2D) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, textarget);
	REQ_INT32_ARG(3, texture);
	REQ_INT32_ARG(4, level);
	
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	RET_UNDEFINED;
	
}


JS_METHOD(getFramebufferAttachmentParameter) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, name);
	
	GLint params;
	glGetFramebufferAttachmentParameteriv(target, attachment, name, &params);
	
	RET_NUM(params);
	
}


} // namespace webgl
