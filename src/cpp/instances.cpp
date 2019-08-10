#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(drawArraysInstanced) { NAPI_ENV;
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	REQ_INT32_ARG(3, primcount);
	
	glDrawArraysInstanced(mode, first, count, primcount);
	RET_UNDEFINED;
	
}


JS_METHOD(drawElementsInstanced) { NAPI_ENV;
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	REQ_INT32_ARG(4, primcount);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElementsInstanced(mode, count, type, indices, primcount);
	RET_UNDEFINED;
	
}


JS_METHOD(vertexAttribDivisor) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, index);
	REQ_UINT32_ARG(1, divisor);
	
	glVertexAttribDivisor(index, divisor);
	RET_UNDEFINED;
	
}


} // namespace webgl
