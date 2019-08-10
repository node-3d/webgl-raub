#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(clearStencil) { NAPI_ENV;
	
	REQ_INT32_ARG(0, s);
	
	glClearStencil(s);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilFunc) { NAPI_ENV;
	
	REQ_INT32_ARG(0, func);
	REQ_INT32_ARG(1, ref);
	REQ_INT32_ARG(2, mask);
	
	glStencilFunc(func, ref, mask);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilFuncSeparate) { NAPI_ENV;
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, func);
	REQ_INT32_ARG(2, ref);
	REQ_INT32_ARG(3, mask);
	
	glStencilFuncSeparate(face, func, ref, mask);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilMask) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, mask);
	
	glStencilMask(mask);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilMaskSeparate) { NAPI_ENV;
	
	REQ_INT32_ARG(0, face);
	REQ_UINT32_ARG(1, mask);
	
	glStencilMaskSeparate(face, mask);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilOp) { NAPI_ENV;
	
	REQ_INT32_ARG(0, fail);
	REQ_INT32_ARG(1, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOp(fail, zfail, zpass);
	RET_UNDEFINED;
	
}


JS_METHOD(stencilOpSeparate) { NAPI_ENV;
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, fail);
	REQ_INT32_ARG(2, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOpSeparate(face, fail, zfail, zpass);
	RET_UNDEFINED;
	
}


} // namespace webgl
