#include "webgl.hpp"


namespace webgl {
constexpr uint32_t VARYING_COUNT_MAX = 256;


static int32_t boundFeedback = -1;
int32_t getBoundFeedback() {
	return boundFeedback;
}


DBG_EXPORT JS_METHOD(createTransformFeedback) { NAPI_ENV;
	GLuint feedback;
	glGenTransformFeedbacks(1, &feedback);
	RET_NUM(feedback);
}


DBG_EXPORT JS_METHOD(deleteTransformFeedback) {
	LET_ID_ARG(0, feedback);
	
	if (boundFeedback > -1 && static_cast<uint32_t>(boundFeedback) == feedback) {
		boundFeedback = -1;
	}
	
	GLuint feedbacks[1] = { feedback };
	glDeleteTransformFeedbacks(1, feedbacks);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isTransformFeedback) { NAPI_ENV;
	LET_ID_ARG(0, feedback);
	
	RET_VALUE(JS_BOOL(glIsTransformFeedback(feedback) != 0));
}


DBG_EXPORT JS_METHOD(bindTransformFeedback) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	LET_ID_ARG(1, feedback);
	
	boundFeedback = feedback;
	glBindTransformFeedback(target, feedback);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(beginTransformFeedback) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	glBeginTransformFeedback(mode);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(endTransformFeedback) {
	glEndTransformFeedback();
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(pauseTransformFeedback) {
	glPauseTransformFeedback();
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(resumeTransformFeedback) {
	glResumeTransformFeedback();
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(transformFeedbackVaryings) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_ARRAY_ARG(1, jsVaryings);
	REQ_INT32_ARG(2, bufferMode);
	
	uint32_t count = std::min(VARYING_COUNT_MAX, jsVaryings.Length());
	const char* varyings[VARYING_COUNT_MAX];
	
	for (uint32_t i = 0; i < count; i++) {
		varyings[i] = jsVaryings.Get(i).As<Napi::String>().Utf8Value().c_str();
	}
	
	glTransformFeedbackVaryings(program, count, varyings, bufferMode);
	
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getTransformFeedbackVarying) { NAPI_ENV;
	LET_ID_ARG(0, program);
	REQ_UINT32_ARG(1, index);
	
	GLenum type;
	GLsizei size;
	
	char name[NAME_SIZE_MAX];
	glGetTransformFeedbackVarying(program, index, NAME_SIZE_MAX, nullptr, &size, &type, name);
	
	Napi::Object activeInfo = JS_OBJECT;
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
}


} // namespace webgl
