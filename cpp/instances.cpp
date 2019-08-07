#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {


NAN_METHOD(drawArraysInstanced) {
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	REQ_INT32_ARG(3, primcount);

    glDrawArraysInstanced(mode, first, count, primcount);
}


NAN_METHOD(drawElementsInstanced) {
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
    REQ_OFFS_ARG(3, ptr);
	REQ_INT32_ARG(4, primcount);

	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);

    glDrawElementsInstanced(mode, count, type, indices, primcount);
}


NAN_METHOD(vertexAttribDivisor) {
	
	REQ_UINT32_ARG(0, index);
	REQ_UINT32_ARG(1, divisor);

    glVertexAttribDivisor(index, divisor);
}


} // namespace webgl
