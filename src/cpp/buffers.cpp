#include <algorithm>

#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createBuffer) { NAPI_ENV;
	GLuint buffer;
	glGenBuffers(1, &buffer);
	RET_NUM(buffer);
}


DBG_EXPORT JS_METHOD(deleteBuffer) {
	LET_ID_ARG(0, buffer);
	
	GLuint buffers[1] = { buffer };
	glDeleteBuffers(1, buffers);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isBuffer) { NAPI_ENV;
	LET_ID_ARG(0, buffer);
	
	RET_BOOL(glIsBuffer(buffer) != 0);
}


DBG_EXPORT JS_METHOD(bindBuffer) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	LET_ID_ARG(1, buffer);
	
	glBindBuffer(target, buffer);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(bindBufferBase) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, index);
	LET_ID_ARG(2, buffer);
	
	glBindBufferBase(target, index, buffer);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(bindBufferRange) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, index);
	LET_ID_ARG(2, buffer);
	REQ_INT32_ARG(3, offset);
	REQ_INT32_ARG(4, size);
	
	glBindBufferRange(target, index, buffer, offset, size);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(bufferData) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	if (info[1].IsObject()) {
		
		REQ_OBJ_ARG(1, arr);
		REQ_INT32_ARG(2, usage);
		
		int size;
		uint8_t* data = getArrayData<uint8_t>(env, arr, &size);
		
		// WebGL2:
		// void gl.bufferData(target, ArrayBufferView srcData, usage, srcOffset, length);
		LET_INT32_ARG(3, srcOffset);
		USE_INT32_ARG(4, length, size);
		
		glBufferData(target, length, data + srcOffset, usage);
		
	} else if (info[1].IsNumber()) {
		
		REQ_UINT32_ARG(1, size);
		REQ_INT32_ARG(2, usage);
		
		glBufferData(target, size, NULL, usage);
		
	}
	
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(bufferSubData) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, offset);
	REQ_TYPED_ARRAY_ARG(2, arr);
	
	GLsizei count = 0;
	void* data = getArrayData(env, arr, &count);
	
	glBufferSubData(target, offset, count, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(copyBufferSubData) { NAPI_ENV;
	REQ_INT32_ARG(0, readTarget);
	REQ_INT32_ARG(1, writeTarget);
	REQ_INT32_ARG(2, readOffset);
	REQ_INT32_ARG(3, writeOffset);
	REQ_INT32_ARG(4, size);
	
	glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getBufferSubData) { NAPI_ENV;
	REQ_INT32_ARG(0, readTarget);
	REQ_INT32_ARG(1, sourceByteOffset);
	REQ_TYPED_ARRAY_ARG(2, dest);
	LET_OFFS_ARG(3, destByteOffset);
	LET_OFFS_ARG(4, length);
	
	size_t elementSize = dest.ElementSize();
	size_t size = std::min(dest.ByteLength(), static_cast<size_t>(elementSize * length));
	size_t offset = destByteOffset * elementSize;
	
	void* data = getArrayData<uint8_t>(env, dest) + offset;
	
	glGetBufferSubData(readTarget, sourceByteOffset, size, data);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getBufferParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint params;
	glGetBufferParameteriv(target, name, &params);
	
	RET_NUM(params);
}


DBG_EXPORT JS_METHOD(readBuffer) { NAPI_ENV;
	REQ_INT32_ARG(0, src);
	
	glReadBuffer(src);
	RET_WEBGL_VOID;
}


} // namespace webgl
