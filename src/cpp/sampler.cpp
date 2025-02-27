#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createSampler) { NAPI_ENV;
	GLuint sampler;
	glGenSamplers(1, &sampler);
	RET_NUM(sampler);
}


DBG_EXPORT JS_METHOD(deleteSampler) {
	LET_ID_ARG(0, sampler);
	GLuint samplers[1] = { sampler };
	glDeleteSamplers(1, samplers);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(isSampler) { NAPI_ENV;
	LET_ID_ARG(0, sampler);
	
	RET_BOOL(glIsSampler(sampler) != 0);
}

DBG_EXPORT JS_METHOD(bindSampler) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	LET_ID_ARG(1, sampler);
	
	glBindSampler(target, sampler);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(samplerParameterf) { NAPI_ENV;
	LET_ID_ARG(0, sampler);
	REQ_INT32_ARG(1, pname);
	REQ_FLOAT_ARG(2, param);
	
	glSamplerParameterf(sampler, pname, param);
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(samplerParameteri) { NAPI_ENV;
	LET_ID_ARG(0, sampler);
	REQ_INT32_ARG(1, pname);
	REQ_INT32_ARG(2, param);
	
	glSamplerParameteri(sampler, pname, param);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(getSamplerParameter) { NAPI_ENV;
	LET_ID_ARG(0, sampler);
	REQ_INT32_ARG(1, pname);
	
	switch (pname) {
	case GL_TEXTURE_COMPARE_FUNC:
	case GL_TEXTURE_COMPARE_MODE:
	case GL_TEXTURE_MAG_FILTER:
	case GL_TEXTURE_MIN_FILTER:
	case GL_TEXTURE_WRAP_R:
	case GL_TEXTURE_WRAP_S:
	case GL_TEXTURE_WRAP_T:
		{
			GLint value = 0;
			glGetSamplerParameteriv(sampler, pname, &value);
			RET_NUM(value);
			break;
		}
	case GL_TEXTURE_MAX_LOD:
	case GL_TEXTURE_MIN_LOD:
		{
			GLfloat value = 0.f;
			glGetSamplerParameterfv(sampler, pname, &value);
			RET_NUM(value);
			break;
		}
	default:
		RET_NULL;
		break;
	}
	
	RET_WEBGL_VOID;
}

} // namespace webgl
