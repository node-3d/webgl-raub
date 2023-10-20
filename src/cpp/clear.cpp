#include <cstring>
#include <vector>

#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(clear) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	glClear(target);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearColor) { NAPI_ENV;
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glClearColor(red, green, blue, alpha);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearDepth) { NAPI_ENV;
	REQ_FLOAT_ARG(0, depth);
	glClearDepth(depth);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearBufferfv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	uint32_t count = jsValues.Length();
	auto cppValues = std::make_unique<GLfloat[]>(count);
	for (uint32_t i = 0; i < count; i++) {
		cppValues[i] = jsValues.Get(i).As<Napi::Number>().FloatValue();
	}
	
	glClearBufferfv(buffer, drawBuffer, cppValues.get());
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearBufferiv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	uint32_t count = jsValues.Length();
	auto cppValues = std::make_unique<GLint[]>(count);
	
	for (uint32_t i = 0; i < count; i++) {
		cppValues[i] = jsValues.Get(i).As<Napi::Number>().Int32Value();
	}
	
	glClearBufferiv(buffer, drawBuffer, cppValues.get());
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearBufferuiv) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_ARRAY_ARG(2, jsValues);
	
	uint32_t count = jsValues.Length();
	auto cppValues = std::make_unique<GLuint[]>(count);
	
	for (uint32_t i = 0; i < count; i++) {
		cppValues[i] = jsValues.Get(i).As<Napi::Number>().Uint32Value();
	}
	
	glClearBufferuiv(buffer, drawBuffer, cppValues.get());
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(clearBufferfi) { NAPI_ENV;
	REQ_INT32_ARG(0, buffer);
	REQ_INT32_ARG(1, drawBuffer);
	REQ_FLOAT_ARG(2, depth);
	REQ_INT32_ARG(3, stencil);
	glClearBufferfi(buffer, drawBuffer, depth, stencil);
	RET_UNDEFINED;
}

} // namespace webgl
