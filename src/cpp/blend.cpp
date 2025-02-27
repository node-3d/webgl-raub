#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(blendColor) { NAPI_ENV;
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glBlendColor(red, green, blue, alpha);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(blendEquation) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	
	glBlendEquation(mode);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(blendEquationSeparate) { NAPI_ENV;
	REQ_INT32_ARG(0, modeRGB);
	REQ_INT32_ARG(1, modeAlpha);
	
	glBlendEquationSeparate(modeRGB, modeAlpha);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(blendFunc) { NAPI_ENV;
	REQ_INT32_ARG(0, sfactor);
	REQ_INT32_ARG(1, dfactor);
	
	glBlendFunc(sfactor, dfactor);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(blendFuncSeparate) { NAPI_ENV;
	REQ_INT32_ARG(0, srcRGB);
	REQ_INT32_ARG(1, dstRGB);
	REQ_INT32_ARG(2, srcAlpha);
	REQ_INT32_ARG(3, dstAlpha);
	
	glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	RET_WEBGL_VOID;
}


} // namespace webgl
