#include <cstring>
#include <vector>

#include <node_buffer.h>

#include "webgl.hpp"

using namespace node;
using namespace v8;
using namespace std;


namespace webgl {

NAN_METHOD(createTransformFeedback) {

	GLuint transformFeedback;
	glGenTransformFeedbacks(1, &transformFeedback);

	RET_VALUE(Nan::New<Number>(transformFeedback));
}


NAN_METHOD(deleteTransformFeedback) {

	REQ_UINT32_ARG(0, transformFeedback);

	glDeleteTransformFeedbacks(1, reinterpret_cast<GLuint*>(&transformFeedback));
}


NAN_METHOD(isTransformFeedback) {

	REQ_UINT32_ARG(0, transformFeedback);

	RET_VALUE(JS_BOOL(glIsTransformFeedback(transformFeedback) != 0));
}


NAN_METHOD(bindTransformFeedback) {

	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, transformFeedback);

	glBindTransformFeedback(target, transformFeedback);
}


NAN_METHOD(beginTransformFeedback) {

	REQ_INT32_ARG(0, mode);
	glBeginTransformFeedback(mode);

}


NAN_METHOD(endTransformFeedback) {
	glEndTransformFeedback();
}


NAN_METHOD(pauseTransformFeedback) {
	glPauseTransformFeedback();
}


NAN_METHOD(resumeTransformFeedback) {
	glResumeTransformFeedback();
}


NAN_METHOD(transformFeedbackVaryings) {

	REQ_UINT32_ARG(0, program);
	REQ_ARRAY_ARG(1, js_varyings);
	REQ_INT32_ARG(2, bufferMode);

	std::vector<char*> gl_varyings;

	auto count = js_varyings->Length();

	for (unsigned int i = 0; i < count; ++i) {
		auto varying = Nan::Get(js_varyings, i).ToLocalChecked();
		auto str = new Nan::Utf8String(varying);
		gl_varyings.push_back(**str);
	}

	glTransformFeedbackVaryings(program, count, gl_varyings.data(), bufferMode);
}


NAN_METHOD(getTransformFeedbackVarying) {

	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, index);

	GLsizei len;
	GLenum type;
	GLsizei size;
	GLsizei bufSize;

	glGetProgramiv(program, GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, &bufSize);

	char name[bufSize];

	glGetTransformFeedbackVarying(program, index, bufSize, &len, &size, &type, name);

	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT(static_cast<int>(type)));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
}


} // namespace webgl
