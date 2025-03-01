#include "webgl.hpp"


namespace webgl {

constexpr GLint BUFFER_FORMATS_SIZE = 32;


DBG_EXPORT JS_METHOD(init) { NAPI_ENV;
	glewExperimental = GL_TRUE;
	
	GLenum err = glewInit();
	
	if (GLEW_OK != err) {
		const GLubyte *text = glewGetErrorString(err);
		globalLog(env, "webgl", "error", reinterpret_cast<const char*>(text));
		JS_THROW("Can't initialize GLEW.");
	}
	
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(colorMask) {
	WEAK_BOOL_ARG(0, red);
	WEAK_BOOL_ARG(1, green);
	WEAK_BOOL_ARG(2, blue);
	WEAK_BOOL_ARG(3, alpha);
	
	glColorMask(red, green, blue, alpha);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(cullFace) { NAPI_ENV;
	REQ_INT32_ARG(0, mode);
	
	glCullFace(mode);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(depthFunc) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	glDepthFunc(id);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(depthMask) {
	WEAK_BOOL_ARG(0, flag);
	
	glDepthMask(flag);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(depthRange) { NAPI_ENV;
	REQ_FLOAT_ARG(0, zNear);
	REQ_FLOAT_ARG(1, zFar);
	
	glDepthRangef(zNear, zFar);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(disable) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	glDisable(id);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(enable) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	glEnable(id);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(finish) {
	glFinish();
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(flush) {
	glFlush();
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(frontFace) { NAPI_ENV;
	REQ_INT32_ARG(0, id);
	
	glFrontFace(id);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getError) { NAPI_ENV;
	RET_NUM(glGetError());
}


#define CASES_PARAM_BOOL case GL_BLEND: \
	case GL_TRANSFORM_FEEDBACK_ACTIVE: \
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


DBG_EXPORT JS_METHOD(getParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, name);
	
	GLboolean bParams[4];
	const char *cParams;
	GLint iParams[4];
	GLfloat fParams[4];
	int32_t boundFeedback;
	
	switch(name) {
	
	CASES_PARAM_BOOL
		glGetBooleanv(name, bParams);
		RET_BOOL(bParams[0] != 0);
	
	CASES_PARAM_FLOAT
		glGetFloatv(name, fParams);
		RET_NUM(fParams[0]);
	
	CASES_PARAM_STRING
		cParams = reinterpret_cast<const char*>(glGetString(name));
		if (cParams != NULL) {
			RET_STR(cParams);
		} else {
			RET_WEBGL_VOID;
		}
	
	CASES_PARAM_INT2 {
		Napi::Array arr = JS_ARRAY;
		glGetIntegerv(name, iParams);
		arr.Set(0U, JS_NUM(iParams[0]));
		arr.Set(1U, JS_NUM(iParams[1]));
		RET_VALUE(arr);
	}
	CASES_PARAM_INT4 {
		Napi::Array arr = JS_ARRAY;
		glGetIntegerv(name, iParams);
		arr.Set(0U, JS_NUM(iParams[0]));
		arr.Set(1U, JS_NUM(iParams[1]));
		arr.Set(2U, JS_NUM(iParams[2]));
		arr.Set(3U, JS_NUM(iParams[3]));
		RET_VALUE(arr);
	}
	CASES_PARAM_FLOAT2 {
		Napi::Array arr = JS_ARRAY;
		glGetFloatv(name, fParams);
		arr.Set(0U, JS_NUM(fParams[0]));
		arr.Set(1U, JS_NUM(fParams[1]));
		RET_VALUE(arr);
	}
	CASES_PARAM_FLOAT4 {
		Napi::Array arr = JS_ARRAY;
		glGetFloatv(name, fParams);
		arr.Set(0U, JS_NUM(fParams[0]));
		arr.Set(1U, JS_NUM(fParams[1]));
		arr.Set(2U, JS_NUM(fParams[2]));
		arr.Set(3U, JS_NUM(fParams[3]));
		RET_VALUE(arr);
	}
	CASES_PARAM_BOOL4 {
		Napi::Array arr = JS_ARRAY;
		glGetBooleanv(name, bParams);
		arr.Set(0U, JS_BOOL(bParams[0] != 0));
		arr.Set(1U, JS_BOOL(bParams[1] != 0));
		arr.Set(2U, JS_BOOL(bParams[2] != 0));
		arr.Set(3U, JS_BOOL(bParams[3] != 0));
		RET_VALUE(arr);
	}
	CASES_PARAM_INT
		glGetIntegerv(name, iParams);
		RET_NUM(iParams[0]);
	
	case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
		RET_NULL;
	
	case GL_TRANSFORM_FEEDBACK_BINDING:
		boundFeedback = getBoundFeedback();
		if (boundFeedback < 0) {
			RET_NULL;
		}
		RET_NUM(boundFeedback);
	
	// returns an int
	default:
		glGetIntegerv(name, iParams);
		RET_NUM(iParams[0]);
	}
}


DBG_EXPORT JS_METHOD(getInternalformatParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, internalformat);
	REQ_INT32_ARG(2, pname);
	
	if (target != GL_RENDERBUFFER) {
		RET_NULL;
	}
	
	switch (internalformat) {
		// Renderbuffer doesn't support unsized internal formats,
		// though GL_RGB and GL_RGBA are color-renderable.
		case GL_RGB:
		case GL_RGBA:
		// Multisampling is not supported for signed and unsigned integer internal
		// formats.
		case GL_R8UI:
		case GL_R8I:
		case GL_R16UI:
		case GL_R16I:
		case GL_R32UI:
		case GL_R32I:
		case GL_RG8UI:
		case GL_RG8I:
		case GL_RG16UI:
		case GL_RG16I:
		case GL_RG32UI:
		case GL_RG32I:
		case GL_RGBA8UI:
		case GL_RGBA8I:
		case GL_RGB10_A2UI:
		case GL_RGBA16UI:
		case GL_RGBA16I:
		case GL_RGBA32UI:
		case GL_RGBA32I:
			return Napi::Int32Array::New(env, 0);
		case GL_R8:
		case GL_RG8:
		case GL_RGB8:
		case GL_RGB565:
		case GL_RGBA8:
		case GL_SRGB8_ALPHA8:
		case GL_RGB5_A1:
		case GL_RGBA4:
		case GL_RGB10_A2:
		case GL_DEPTH_COMPONENT16:
		case GL_DEPTH_COMPONENT24:
		case GL_DEPTH_COMPONENT32F:
		case GL_DEPTH24_STENCIL8:
		case GL_DEPTH32F_STENCIL8:
		case GL_STENCIL_INDEX8:
			break;
		case GL_R16F:
		case GL_RG16F:
		case GL_RGBA16F:
		case GL_R32F:
		case GL_RG32F:
		case GL_RGBA32F:
		case GL_R11F_G11F_B10F:
			RET_NULL;
		default:
			RET_NULL;
	}
	
	switch (pname) {
		case GL_SAMPLES: {
			GLint length = -1;
			glGetInternalformativ(target, internalformat, GL_NUM_SAMPLE_COUNTS, 1, &length);
			if (length <= 0) {
				return Napi::Int32Array::New(env, 0);
			}
			
			length = std::min(BUFFER_FORMATS_SIZE, length);
			GLint bufferFormats[BUFFER_FORMATS_SIZE];
			for (GLint i = 0; i < length; ++i) {
				bufferFormats[i] = 0;
			}
			glGetInternalformativ(target, internalformat, GL_SAMPLES, length, bufferFormats);
			
			auto arr = Napi::Int32Array::New(env, length);
			for (GLint i = 0; i < length; ++i) {
				arr.Set(i, bufferFormats[i]);
			}
			
			return arr;
		}
		default:
			RET_NULL;
	}
}


DBG_EXPORT JS_METHOD(getRenderTarget) { NAPI_ENV;
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
		Napi::Array result = JS_ARRAY;
		result.Set(0U, JS_NUM(fbo));
		result.Set(1U, JS_NUM(tex));
		
		RET_VALUE(result);
	} else {
		RET_NULL;
	}
}


DBG_EXPORT JS_METHOD(getSupportedExtensions) { NAPI_ENV;
	const char *extensions = reinterpret_cast<const char *>(glGetString(GL_EXTENSIONS));
	
	if (extensions != NULL) {
		RET_STR(extensions);
	} else {
		RET_STR("");
	}
}


DBG_EXPORT JS_METHOD(hint) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, mode);
	
	glHint(target, mode);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isEnabled) { NAPI_ENV;
	REQ_INT32_ARG(0, capability);
	
	bool ret = glIsEnabled(capability) != 0;
	
	RET_BOOL(ret);
}


DBG_EXPORT JS_METHOD(lineWidth) { NAPI_ENV;
	REQ_FLOAT_ARG(0, width);
	
	glLineWidth(width);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(pixelStorei) { NAPI_ENV;
	REQ_INT32_ARG(0, name);
	WEAK_INT32_ARG(1, param);
	
	glPixelStorei(name, param);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(polygonOffset) { NAPI_ENV;
	REQ_FLOAT_ARG(0, factor);
	REQ_FLOAT_ARG(1, units);
	
	glPolygonOffset(factor, units);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(readPixels) { NAPI_ENV;
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	REQ_INT32_ARG(4, format);
	REQ_INT32_ARG(5, type);
	REQ_OBJ_ARG(6, image);
	
	void *pixels = getData(env, image);
	glReadPixels(x, y, width, height, format, type, pixels);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(scissor) { NAPI_ENV;
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	
	glScissor(x, y, width, height);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(viewport) { NAPI_ENV;
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, w);
	REQ_INT32_ARG(3, h);
	
	glViewport(x, y, w, h);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getIndexedParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, index);
	switch (target) {
		case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING: {
			RET_NULL;
			break;
		}
		case GL_UNIFORM_BUFFER_BINDING:
			RET_NULL;
			break;
		case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE:
		case GL_TRANSFORM_FEEDBACK_BUFFER_START:
		case GL_UNIFORM_BUFFER_SIZE:
		case GL_UNIFORM_BUFFER_START: {
			GLint64 value = -1;
			glGetInteger64i_v(target, index, &value);
			RET_NUM(value);
			break;
		}
		default:
			RET_NULL;
			break;
	}
}

DBG_EXPORT JS_METHOD(sampleCoverage) { NAPI_ENV;
	REQ_FLOAT_ARG(0, value);
	WEAK_BOOL_ARG(1, invert);
	
	glSampleCoverage(value, invert);
	RET_WEBGL_VOID;
}

} // namespace webgl
