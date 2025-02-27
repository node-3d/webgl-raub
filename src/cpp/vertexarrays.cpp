#include "webgl.hpp"


namespace webgl {

DBG_EXPORT JS_METHOD(createVertexArray) { NAPI_ENV;
	GLuint vertexarray;
	glGenVertexArrays(1, &vertexarray);
	
	RET_NUM(vertexarray);
}


DBG_EXPORT JS_METHOD(deleteVertexArray) {
	LET_ID_ARG(0, vertexarray);
	
	GLuint vertexarrays[1] = { vertexarray };
	glDeleteVertexArrays(1, vertexarrays);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isVertexArray) { NAPI_ENV;
	LET_ID_ARG(0, vertexarray);
	
	RET_BOOL(glIsVertexArray(vertexarray) != 0);
}


DBG_EXPORT JS_METHOD(bindVertexArray) {
	LET_ID_ARG(0, vertexarray);
	
	glBindVertexArray(vertexarray);
	RET_WEBGL_VOID;
}

} // namespace webgl
