#include "webgl.hpp"

/**
 * @link https://registry.khronos.org/webgl/specs/latest/2.0/#3.7.14
 */

namespace webgl {

DBG_EXPORT JS_METHOD(fenceSync) { NAPI_ENV;
	REQ_INT32_ARG(0, condition);
	REQ_UINT32_ARG(1, flags);
	GLsync sync = glFenceSync(condition, flags);
	RET_EXT(sync);
}


DBG_EXPORT JS_METHOD(deleteSync) { NAPI_ENV;
	REQ_EXT_ARG(0, sync);
	glDeleteSync(reinterpret_cast<GLsync>(sync));
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isSync) { NAPI_ENV;
	REQ_EXT_ARG(0, sync);
	
	RET_BOOL(glIsSync(reinterpret_cast<GLsync>(sync)) != 0);
}

DBG_EXPORT JS_METHOD(clientWaitSync) { NAPI_ENV;
	REQ_EXT_ARG(0, sync);
	REQ_UINT32_ARG(1, flags);
	USE_DOUBLE_ARG(2, nanosec, -1.0);
	
	GLuint64 timeout64 = nanosec < 0.0 ? GL_TIMEOUT_IGNORED : static_cast<GLuint64>(nanosec);
	GLenum result = glClientWaitSync(reinterpret_cast<GLsync>(sync), flags, timeout64);
	RET_NUM(result);
}

DBG_EXPORT JS_METHOD(waitSync) { NAPI_ENV;
	REQ_EXT_ARG(0, sync);
	LET_UINT32_ARG(1, flags);
	USE_OFFS_ARG(2, nanosec, -1.0);
	
	GLuint64 timeout64 = nanosec < 0.0 ? GL_TIMEOUT_IGNORED : static_cast<GLuint64>(nanosec);
	glWaitSync(reinterpret_cast<GLsync>(sync), flags, timeout64);
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(getSyncParameter) { NAPI_ENV;
	REQ_EXT_ARG(0, sync);
	REQ_INT32_ARG(0, pname);
	
	switch (pname) {
	case GL_OBJECT_TYPE:
	case GL_SYNC_STATUS:
	case GL_SYNC_CONDITION:
	case GL_SYNC_FLAGS:
		{
			GLint value = 0;
			GLsizei length = -1;
			glGetSynciv(reinterpret_cast<GLsync>(sync), pname, 1, &length, &value);
			RET_NUM(value);
		}
	default:
		RET_NULL;
	}
}

} // namespace webgl
