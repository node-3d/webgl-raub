#include "webgl.hpp"


namespace webgl {

constexpr uint32_t CLEAR_BUFFER_SIZE = 4;


DBG_EXPORT JS_METHOD(clear) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	glClear(target);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearColor) { NAPI_ENV;
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glClearColor(red, green, blue, alpha);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearDepth) { NAPI_ENV;
	REQ_FLOAT_ARG(0, depth);
	glClearDepth(depth);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearBufferfv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	GLfloat bufferFv[CLEAR_BUFFER_SIZE];
	uint32_t count = std::min(CLEAR_BUFFER_SIZE, jsValues.Length());
	
	for (uint32_t i = 0; i < count; i++) {
		bufferFv[i] = jsValues.Get(i).As<Napi::Number>().FloatValue();
	}
	
	glClearBufferfv(buffer, drawBuffer, bufferFv);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearBufferiv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	GLint bufferIv[CLEAR_BUFFER_SIZE];
	uint32_t count = std::min(CLEAR_BUFFER_SIZE, jsValues.Length());
	
	for (uint32_t i = 0; i < count; i++) {
		bufferIv[i] = jsValues.Get(i).As<Napi::Number>().Int32Value();
	}
	
	glClearBufferiv(buffer, drawBuffer, bufferIv);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearBufferuiv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	GLuint bufferUiv[CLEAR_BUFFER_SIZE];
	uint32_t count = std::min(CLEAR_BUFFER_SIZE, jsValues.Length());
	
	for (uint32_t i = 0; i < count; i++) {
		bufferUiv[i] = jsValues.Get(i).As<Napi::Number>().Uint32Value();
	}
	
	glClearBufferuiv(buffer, drawBuffer, bufferUiv);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(clearBufferfi) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_FLOAT_ARG(2, depth);
	REQ_INT32_ARG(3, stencil);
	glClearBufferfi(buffer, drawBuffer, depth, stencil);
	RET_WEBGL_VOID;
}

} // namespace webgl
