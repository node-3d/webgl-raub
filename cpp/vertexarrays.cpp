#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(createVertexArray) {
	
	GLuint vertexarray;
	glGenVertexArrays(1, &vertexarray);
	
	RET_VALUE(Nan::New<Number>(vertexarray));
	
}


NAN_METHOD(deleteVertexArray) {
	
	REQ_UINT32_ARG(0, vertexarray);
	
	glDeleteVertexArrays(1, reinterpret_cast<GLuint*>(&vertexarray));
	
}


NAN_METHOD(isVertexArray) {
	
	REQ_UINT32_ARG(0, vertexarray);
	
	RET_VALUE(Nan::New<Boolean>(glIsVertexArray(vertexarray) != 0));
	
}


NAN_METHOD(bindVertexArray) {
	
	REQ_UINT32_ARG(0, vertexarray);
	
	glBindVertexArray(vertexarray);
	
}


} // namespace webgl
