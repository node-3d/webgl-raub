#include <vector>

#include "webgl.hpp"


namespace webgl {

static int32_t boundFeedback = -1;
int32_t getBoundFeedback() {
	return boundFeedback;
}


DBG_EXPORT JS_METHOD(createTransformFeedback) { NAPI_ENV;
	GLuint feedback;
	glGenTransformFeedbacks(1, &feedback);
	RET_NUM(feedback);
}


DBG_EXPORT JS_METHOD(deleteTransformFeedback) { NAPI_ENV;
	REQ_UINT32_ARG(0, feedback);
	
	if (boundFeedback == feedback) {
		boundFeedback = -1;
	}
	
	GLuint feedbacks[1] = { feedback };
	glDeleteTransformFeedbacks(1, feedbacks);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isTransformFeedback) { NAPI_ENV;
	REQ_UINT32_ARG(0, feedback);
	
	RET_VALUE(JS_BOOL(glIsTransformFeedback(feedback) != 0));
}


DBG_EXPORT JS_METHOD(bindTransformFeedback) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, feedback);
	
	boundFeedback = feedback;
	glBindTransformFeedback(target, feedback);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(beginTransformFeedback) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	glBeginTransformFeedback(mode);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(endTransformFeedback) { NAPI_ENV;
	glEndTransformFeedback();
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(pauseTransformFeedback) { NAPI_ENV;
	glPauseTransformFeedback();
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(resumeTransformFeedback) { NAPI_ENV;
	glResumeTransformFeedback();
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(transformFeedbackVaryings) { NAPI_ENV;
	REQ_UINT32_ARG(0, program);
	REQ_ARRAY_ARG(1, jsVaryings);
	REQ_INT32_ARG(2, bufferMode);
	
	uint32_t count = jsVaryings.Length();
	auto cppVaryings = std::make_unique<std::string[]>(count);
	auto varyings = std::make_unique<const char*[]>(count);
	
	for (uint32_t i = 0; i < count; i++) {
		cppVaryings[i] = jsVaryings.Get(i).As<Napi::String>().Utf8Value();
		varyings[i] = cppVaryings[i].c_str();
	}
	
	glTransformFeedbackVaryings(program, count, varyings.get(), bufferMode);
	
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(getTransformFeedbackVarying) { NAPI_ENV;
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, index);
	
	GLsizei len;
	GLenum type;
	GLsizei size;
	
	char name[1024];
	
	glGetTransformFeedbackVarying(program, index, 1024, &len, &size, &type, name);
	
	Napi::Object activeInfo = JS_OBJECT;
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
}


} // namespace webgl
