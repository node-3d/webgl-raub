#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


#ifdef _WIN32
	#define	strcasestr(s, t) strstr(strupr(s), strupr(t))
#endif


namespace webgl {


NAN_METHOD(createBuffer) {
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(deleteBuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteBuffers(1, reinterpret_cast<GLuint*>(&buffer));
	
}


NAN_METHOD(isBuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(Nan::New<Boolean>(glIsBuffer(buffer) != 0));
	
}


NAN_METHOD(bindBuffer) {
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, buffer);
	
	glBindBuffer(target, buffer);
	
}


NAN_METHOD(bufferData) {
	
	REQ_INT32_ARG(0, target);
	
	if (info[1]->IsObject()) {
		
		REQ_ARRV_ARG(1, obj);
		REQ_INT32_ARG(2, usage);
		
		int element_size = 1;
		Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(obj);
		int size = arr->ByteLength()* element_size;
		void* data = arr->Buffer()->GetContents().Data();
		
		glBufferData(target, size, data, usage);
		
	} else if (info[1]->IsNumber()) {
		
		REQ_UINT32_ARG(1, size);
		REQ_INT32_ARG(2, usage);
		
		glBufferData(target, size, NULL, usage);
		
	}
	
}


NAN_METHOD(bufferSubData) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, offset);
	REQ_ARRV_ARG(2, arr);
	
	int element_size = 1;
	int size = arr->ByteLength() * element_size;
	void *data = arr->Buffer()->GetContents().Data();
	
	glBufferSubData(target, offset, size, data);
	
}


NAN_METHOD(getBufferParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint params;
	glGetBufferParameteriv(target, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


} // namespace webgl
