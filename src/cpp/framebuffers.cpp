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


JS_METHOD(bindFramebuffer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, fbo);
	
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	RET_UNDEFINED;
	
}


JS_METHOD(blitFramebuffer) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, srcX0);
	REQ_UINT32_ARG(1, srcY0);
	REQ_UINT32_ARG(2, srcX1);
	REQ_UINT32_ARG(3, srcY1);
	REQ_UINT32_ARG(4, dstX0);
	REQ_UINT32_ARG(5, dstY0);
	REQ_UINT32_ARG(6, dstX1);
	REQ_UINT32_ARG(7, dstY1);
	REQ_UINT32_ARG(8, mask);
	REQ_UINT32_ARG(9, filter);
	
	glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
	
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
