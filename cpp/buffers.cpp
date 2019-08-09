#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


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


NAN_METHOD(bindBufferBase) {
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, index);
	REQ_UINT32_ARG(2, buffer);
	
	glBindBufferBase(target, index, buffer);

}


NAN_METHOD(bindBufferRange) {
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, index);
	REQ_UINT32_ARG(2, buffer);
	REQ_INT32_ARG(3, offset);
	REQ_INT32_ARG(4, size);

	glBindBufferRange(target, index, buffer, offset, size);

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
	REQ_TYPED_ARRAY_ARG(2, arr, TypedArray);
	
	int size = arr->ByteLength();
	int byteOffset = arr->ByteOffset();
	void* data = getArrayData<unsigned char>(arr);

	glBufferSubData(target, offset, size, data);
	
}


NAN_METHOD(copyBufferSubData) {

	REQ_INT32_ARG(0, readTarget);
	REQ_INT32_ARG(1, writeTarget);
	REQ_INT32_ARG(2, readOffset);
	REQ_INT32_ARG(3, writeOffset);
	REQ_INT32_ARG(4, size);

	glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
}


NAN_METHOD(getBufferSubData) {

	REQ_INT32_ARG(0, readTarget);
	REQ_INT32_ARG(1, srcByteOffset);
	REQ_TYPED_ARRAY_ARG(2, dst, TypedArray);
	LET_UINT32_ARG(3, dstOffset);
	LET_UINT32_ARG(4, length);

	int BPE = dst->ByteLength() / dst->Length();
	int size = std::min((unsigned int) dst->ByteLength(), length * BPE);

	// dstOffset = dstOffset * BPE + dst->ByteOffset();

	void* data = getArrayData<unsigned char>(dst) + (dstOffset * BPE);

	glGetBufferSubData(readTarget, srcByteOffset, size, data);

}


NAN_METHOD(getBufferParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint params;
	glGetBufferParameteriv(target, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


} // namespace webgl
