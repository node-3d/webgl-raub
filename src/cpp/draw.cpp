#include <cstring>
#include <vector>

#include "webgl.hpp"


namespace webgl {

DBG_EXPORT JS_METHOD(drawArrays) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	
	glDrawArrays(mode, first, count);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(drawElements) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElements(mode, count, type, indices);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(drawBuffers) { NAPI_ENV;
	REQ_ARRAY_ARG(0, jsBuffers);
	
	uint32_t count = jsBuffers.Length();
	auto cppBuffers = std::make_unique<GLenum[]>(count);
	
	for (uint32_t i = 0; i < count; i++) {
		cppBuffers[i] = jsBuffers.Get(i).As<Napi::Number>().Uint32Value();
	}
	
	glDrawBuffers(count, cppBuffers.get());
	RET_UNDEFINED;
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
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(drawArraysInstanced) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	REQ_INT32_ARG(3, primcount);
	
	glDrawArraysInstanced(mode, first, count, primcount);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(drawElementsInstanced) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	REQ_INT32_ARG(4, primcount);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	RET_UNDEFINED;
}

} // namespace webgl
