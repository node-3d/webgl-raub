#include "webgl.hpp"


namespace webgl {

constexpr uint32_t DRAW_BUFFER_COUNT_MAX = 32;


DBG_EXPORT JS_METHOD(drawArrays) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	
	glDrawArrays(mode, first, count);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(drawElements) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElements(mode, count, type, indices);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(drawBuffers) { NAPI_ENV;
	REQ_ARRAY_ARG(0, jsBuffers);
	
	GLenum bufferAttachments[DRAW_BUFFER_COUNT_MAX];
	uint32_t count = std::min(jsBuffers.Length(), DRAW_BUFFER_COUNT_MAX);
	
	for (uint32_t i = 0; i < count; i++) {
		bufferAttachments[i] = jsBuffers.Get(i).As<Napi::Number>().Uint32Value();
	}
	
	glDrawBuffers(count, bufferAttachments);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(drawRangeElements) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_UINT32_ARG(1, start);
	REQ_UINT32_ARG(2, end);
	REQ_UINT32_ARG(3, count);
	REQ_INT32_ARG(4, type);
	REQ_OFFS_ARG(5, ptr);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawRangeElements(mode, start, end, count, type, indices);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(drawArraysInstanced) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	REQ_INT32_ARG(3, primcount);
	
	glDrawArraysInstanced(mode, first, count, primcount);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(drawElementsInstanced) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	REQ_INT32_ARG(4, primcount);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	RET_WEBGL_VOID;
}

} // namespace webgl
