#include <vector>

#include "webgl.hpp"


using namespace std;


namespace webgl {

JS_METHOD(createTransformFeedback) { NAPI_ENV;
	
	GLuint transformFeedback;
	glGenTransformFeedbacks(1, &transformFeedback);
	
	RET_NUM(transformFeedback);
	
}


JS_METHOD(deleteTransformFeedback) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, transformFeedback);
	
	glDeleteTransformFeedbacks(1, reinterpret_cast<GLuint*>(&transformFeedback));
	RET_UNDEFINED;
	
}


JS_METHOD(isTransformFeedback) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, transformFeedback);
	
	RET_VALUE(JS_BOOL(glIsTransformFeedback(transformFeedback) != 0));
	RET_UNDEFINED;
	
}


JS_METHOD(bindTransformFeedback) { NAPI_ENV;
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, transformFeedback);
	
	glBindTransformFeedback(target, transformFeedback);
	RET_UNDEFINED;
	
}


JS_METHOD(beginTransformFeedback) { NAPI_ENV;
	
	REQ_INT32_ARG(0, mode);
	glBeginTransformFeedback(mode);
	RET_UNDEFINED;
	
}


JS_METHOD(endTransformFeedback) { NAPI_ENV;
	glEndTransformFeedback();
	RET_UNDEFINED;
}


JS_METHOD(pauseTransformFeedback) { NAPI_ENV;
	glPauseTransformFeedback();
	RET_UNDEFINED;
}


JS_METHOD(resumeTransformFeedback) { NAPI_ENV;
	glResumeTransformFeedback();
	RET_UNDEFINED;
}


JS_METHOD(transformFeedbackVaryings) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, program);
	REQ_ARRAY_ARG(1, jsVaryings);
	REQ_INT32_ARG(2, bufferMode);
	
	uint32_t count = jsVaryings.Length();
	std::string *cppVaryings = new std::string [count];
	const char **varyings = new const char* [count];
	
	for (uint32_t i = 0; i < count; i++) {
		cppVaryings[i] = jsVaryings.Get(i).As<Napi::String>().Utf8Value();
		varyings[i] = cppVaryings[i].c_str();
	}
	
	glTransformFeedbackVaryings(program, count, varyings, bufferMode);
	
	delete [] varyings;
	delete [] cppVaryings;
	
	RET_UNDEFINED;
	
}


JS_METHOD(getTransformFeedbackVarying) { NAPI_ENV;
	
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, index);
	
	GLsizei len;
	GLenum type;
	GLsizei size;
	
	char name[1024];
	
	glGetTransformFeedbackVarying(program, index, 1024, &len, &size, &type, name);
	
	Napi::Array activeInfo = Napi::Array::New(env);
	activeInfo.Set("size", JS_NUM(size));
	activeInfo.Set("type", JS_NUM(static_cast<int>(type)));
	activeInfo.Set("name", JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


} // namespace webgl
