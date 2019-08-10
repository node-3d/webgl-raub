#include <cstring>
#include <vector>

#include "webgl.hpp"


using namespace std;


namespace webgl {


JS_METHOD(createVertexArray) { NAPI_ENV;
	
	GLuint vertexarray;
	glGenVertexArrays(1, &vertexarray);
	
	RET_NUM(vertexarray);
	
}


JS_METHOD(deleteVertexArray) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, vertexarray);
	
	glDeleteVertexArrays(1, reinterpret_cast<GLuint*>(&vertexarray));
	RET_UNDEFINED;
	
}


JS_METHOD(isVertexArray) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, vertexarray);
	
	RET_BOOL(glIsVertexArray(vertexarray) != 0);
	
}


JS_METHOD(bindVertexArray) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, vertexarray);
	
	glBindVertexArray(vertexarray);
	RET_UNDEFINED;
	
}


} // namespace webgl
