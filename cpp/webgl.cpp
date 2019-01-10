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

// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
static GLuint ToGLuint(const void* ptr) {
	return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
}


NAN_METHOD(init) {
	
	GLenum err = glewInit();
	
	if (GLEW_OK != err) {
		// Problem: glewInit failed, something is seriously wrong
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		Nan::ThrowError("Can't initialize GLEW");
	}
	
}


NAN_METHOD(pixelStorei) {
	
	REQ_INT32_ARG(0, name);
	REQ_INT32_ARG(1, param);
	
	glPixelStorei(name, param);
	
}


NAN_METHOD(getRenderTarget) {
	
	REQ_UINT32_ARG(0, width);
	REQ_UINT32_ARG(1, height);
	REQ_UINT32_ARG(2, samples);
	
	GLuint fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	
	GLuint renderBuffer;
	glGenRenderbuffers(1, &renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	
	if (samples > 1) {
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH_COMPONENT, width, height);
	} else {
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	}
	
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,	renderBuffer);
	
	GLuint tex;
	glGenTextures(1, &tex);
	
	if (samples > 1) {
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, tex);
		// glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGBA8, width, height, true);
		// glFramebufferTexture2DMultisampleEXT(
		// 	GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0, samples
		// );
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, tex, 0);
	} else {
		glBindTexture(GL_TEXTURE_2D, tex);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	GLenum framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	
	if (framebufferStatus == GL_FRAMEBUFFER_COMPLETE) {
		
		V8_VAR_ARR result = Nan::New<Array>(2);
		result->Set(0, JS_NUM(fbo));
		result->Set(1, JS_NUM(tex));
		
		RET_VALUE(result);
		
	} else {
		RET_VALUE(Null(Isolate::GetCurrent()));
	}
	
}


NAN_METHOD(getError) {
	
	RET_VALUE(Nan::New<Integer>(glGetError()));
	
}


NAN_METHOD(drawArrays) {
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	
	glDrawArrays(mode, first, count);
	
}


NAN_METHOD(depthFunc) {
	
	REQ_INT32_ARG(0, id);
	
	glDepthFunc(id);
	
}


NAN_METHOD(viewport) {
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, w);
	REQ_INT32_ARG(3, h);
	
	glViewport(x, y, w, h);
	
}


NAN_METHOD(frontFace) {
	
	REQ_INT32_ARG(0, id);
	
	glFrontFace(id);
	
}


NAN_METHOD(clearColor) {
	
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glClearColor(red, green, blue, alpha);
	
}


NAN_METHOD(clearDepth) {
	
	REQ_FLOAT_ARG(0, depth);
	glClearDepth(depth);
	
}


NAN_METHOD(disable) {
	
	REQ_INT32_ARG(0, id);
	
	glDisable(id);
	
}


NAN_METHOD(enable) {
	
	REQ_INT32_ARG(0, id);
	
	glEnable(id);
	
}


NAN_METHOD(clear) {
	
	REQ_INT32_ARG(0, target);
	
	glClear(target);
	
}


NAN_METHOD(drawElements) {
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_OFFS_ARG(3, ptr);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElements(mode, count, type, indices);
	
}


NAN_METHOD(flush) {
	
	glFlush();
	
}


NAN_METHOD(finish) {
	
	glFinish();
	
}


NAN_METHOD(colorMask) {
	
	LET_BOOL_ARG(0, red);
	LET_BOOL_ARG(1, green);
	LET_BOOL_ARG(2, blue);
	LET_BOOL_ARG(3, alpha);
	
	glColorMask(red, green, blue, alpha);
	
}


NAN_METHOD(cullFace) {
	
	REQ_INT32_ARG(0, mode);
	
	glCullFace(mode);
	
}


NAN_METHOD(depthMask) {
	
	LET_BOOL_ARG(0, flag);
	
	glDepthMask(flag);
	
}


NAN_METHOD(depthRange) {
	
	REQ_FLOAT_ARG(0, zNear);
	REQ_FLOAT_ARG(1, zFar);
	
	glDepthRangef(zNear, zFar);
	
}


NAN_METHOD(hint) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, mode);
	
	glHint(target, mode);
	
}


NAN_METHOD(isEnabled) {
	
	REQ_INT32_ARG(0, cap);
	
	bool ret = glIsEnabled(cap) != 0;
	
	RET_VALUE(Nan::New<Boolean>(ret));
	
}


NAN_METHOD(lineWidth) {
	
	REQ_FLOAT_ARG(0, width);
	
	glLineWidth(width);
	
}


NAN_METHOD(polygonOffset) {
	
	REQ_FLOAT_ARG(0, factor);
	REQ_FLOAT_ARG(1, units);
	
	glPolygonOffset(factor, units);
	
}


NAN_METHOD(sampleCoverage) {
	
	REQ_FLOAT_ARG(0, value);
	LET_BOOL_ARG(1, invert);
	
	glSampleCoverage(value, invert);
	
}


NAN_METHOD(scissor) {
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	
	glScissor(x, y, width, height);
	
}


NAN_METHOD(readPixels) {
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	REQ_INT32_ARG(4, format);
	REQ_INT32_ARG(5, type);
	REQ_OBJ_ARG(6, image);
	
	void *pixels = getData(image);
	glReadPixels(x, y, width, height, format, type, pixels);
	
}


#define CASES_PARAM_BOOL case GL_BLEND: \
	case GL_CULL_FACE: \
	case GL_DEPTH_TEST: \
	case GL_DEPTH_WRITEMASK: \
	case GL_DITHER: \
	case GL_POLYGON_OFFSET_FILL: \
	case GL_SAMPLE_COVERAGE_INVERT: \
	case GL_SCISSOR_TEST: \
	case GL_STENCIL_TEST: \
	case 0x9240 /* UNPACK_FLIP_Y_WEBGL */: \
	case 0x9241 /* UNPACK_PREMULTIPLY_ALPHA_WEBGL*/:

#define CASES_PARAM_FLOAT case GL_DEPTH_CLEAR_VALUE: \
	case GL_LINE_WIDTH: \
	case GL_POLYGON_OFFSET_FACTOR: \
	case GL_POLYGON_OFFSET_UNITS: \
	case GL_SAMPLE_COVERAGE_VALUE:

#define CASES_PARAM_STRING case GL_RENDERER: \
	case GL_SHADING_LANGUAGE_VERSION: \
	case GL_VENDOR: \
	case GL_VERSION: \
	case GL_EXTENSIONS: \

#define CASES_PARAM_INT2 case GL_MAX_VIEWPORT_DIMS:

#define CASES_PARAM_INT4 case GL_SCISSOR_BOX: \
	case GL_VIEWPORT:

#define CASES_PARAM_FLOAT2 case GL_ALIASED_LINE_WIDTH_RANGE: \
	case GL_ALIASED_POINT_SIZE_RANGE: \
	case GL_DEPTH_RANGE:

#define CASES_PARAM_FLOAT4 case GL_BLEND_COLOR: \
	case GL_COLOR_CLEAR_VALUE:

#define CASES_PARAM_BOOL4 case GL_COLOR_WRITEMASK:

#define CASES_PARAM_INT case GL_ARRAY_BUFFER_BINDING: \
	case GL_CURRENT_PROGRAM: \
	case GL_ELEMENT_ARRAY_BUFFER_BINDING: \
	case GL_FRAMEBUFFER_BINDING: \
	case GL_RENDERBUFFER_BINDING: \
	case GL_TEXTURE_BINDING_2D: \
	case GL_TEXTURE_BINDING_CUBE_MAP:



NAN_METHOD(getParameter) {
	
	REQ_INT32_ARG(0, name);
	
	GLboolean bParams[4];
	const char *cParams;
	GLint iParams[4];
	GLfloat fParams[4];
	Local<Array> arr;
	
	switch(name) {
	
	CASES_PARAM_BOOL
		glGetBooleanv(name, bParams);
		RET_VALUE(JS_BOOL(bParams[0] != 0));
		break;
	
	CASES_PARAM_FLOAT
		glGetFloatv(name, fParams);
		RET_VALUE(JS_NUM(fParams[0]));
		break;
	
	CASES_PARAM_STRING
		cParams = reinterpret_cast<const char*>(glGetString(name));
		if (cParams != NULL) {
			RET_VALUE(JS_STR(cParams));
		} else {
			RET_UNDEFINED;
		}
		
		break;
	
	CASES_PARAM_INT2
		glGetIntegerv(name, iParams);
		arr = Nan::New<Array>(2);
		arr->Set(0, JS_INT(iParams[0]));
		arr->Set(1, JS_INT(iParams[1]));
		RET_VALUE(arr);
		break;
	
	CASES_PARAM_INT4
		glGetIntegerv(name, iParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_INT(iParams[0]));
		arr->Set(1, JS_INT(iParams[1]));
		arr->Set(2, JS_INT(iParams[2]));
		arr->Set(3, JS_INT(iParams[3]));
		RET_VALUE(arr);
		break;
	
	CASES_PARAM_FLOAT2
		glGetFloatv(name, fParams);
		arr = Nan::New<Array>(2);
		arr->Set(0, JS_NUM(fParams[0]));
		arr->Set(1, JS_NUM(fParams[1]));
		RET_VALUE(arr);
		break;
	
	CASES_PARAM_FLOAT4
		glGetFloatv(name, fParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_NUM(fParams[0]));
		arr->Set(1, JS_NUM(fParams[1]));
		arr->Set(2, JS_NUM(fParams[2]));
		arr->Set(3, JS_NUM(fParams[3]));
		RET_VALUE(arr);
		break;
	
	CASES_PARAM_BOOL4
		glGetBooleanv(name, bParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_BOOL(bParams[0] != 0));
		arr->Set(1, JS_BOOL(bParams[1] != 0));
		arr->Set(2, JS_BOOL(bParams[2] != 0));
		arr->Set(3, JS_BOOL(bParams[3] != 0));
		RET_VALUE(arr);
		break;
	
	CASES_PARAM_INT
		glGetIntegerv(name, iParams);
		RET_VALUE(JS_INT(iParams[0]));
		break;
	
	// returns an int
	default:
		glGetIntegerv(name, iParams);
		RET_VALUE(JS_INT(iParams[0]));
		break;
	
	}
	
}


NAN_METHOD(getSupportedExtensions) {
	
	const char *extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
	
	RET_VALUE(JS_STR(extensions));
	
}


} // namespace webgl
