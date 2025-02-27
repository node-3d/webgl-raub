#include "webgl.hpp"


namespace webgl {

static uint32_t currentOcclusionQuery = -1;
static uint32_t currentFeedbackQuery = -1;


DBG_EXPORT JS_METHOD(createQuery) { NAPI_ENV;
	GLuint query;
	glGenQueries(1, &query);
	RET_NUM(query);
}


DBG_EXPORT JS_METHOD(deleteQuery) { NAPI_ENV;
	LET_ID_ARG(0, query);
	GLuint queries[1] = { query };
	glDeleteQueries(1, queries);
	RET_WEBGL_VOID;
}


DBG_EXPORT JS_METHOD(isQuery) { NAPI_ENV;
	LET_ID_ARG(0, query);
	
	RET_BOOL(glIsQuery(query) != 0);
}


DBG_EXPORT JS_METHOD(beginQuery) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	LET_ID_ARG(1, query);
	
	switch (target) {
	case GL_ANY_SAMPLES_PASSED:
	case GL_ANY_SAMPLES_PASSED_CONSERVATIVE:
		currentOcclusionQuery = query;
		break;
	case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
		currentFeedbackQuery = query;
		break;
	default:
		break;
	}
	
	glBeginQuery(target, query);
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(endQuery) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	switch (target) {
	case GL_ANY_SAMPLES_PASSED:
	case GL_ANY_SAMPLES_PASSED_CONSERVATIVE:
		currentOcclusionQuery = -1;
		break;
	case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
		currentFeedbackQuery = -1;
		break;
	default:
		break;
	}

	glEndQuery(target);
	
	RET_WEBGL_VOID;
}

DBG_EXPORT JS_METHOD(getQueryParameter) { NAPI_ENV;
	LET_ID_ARG(0, query);
	REQ_INT32_ARG(1, pname);
	
	GLuint value;
	
	switch (pname) {
	case GL_QUERY_RESULT_AVAILABLE:
		glGetQueryObjectuiv(query, pname, &value);
		RET_BOOL(value != 0);
	case GL_QUERY_RESULT:
		glGetQueryObjectuiv(query, pname, &value);
		RET_NUM(value);
	default:
		RET_NULL;
	}
}

DBG_EXPORT JS_METHOD(getQuery) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, pname);
	
	if (pname != GL_CURRENT_QUERY) {
		RET_NULL;
	}
	
	switch (target) {
	case GL_ANY_SAMPLES_PASSED:
	case GL_ANY_SAMPLES_PASSED_CONSERVATIVE:
		RET_NUM(currentOcclusionQuery);
	case GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN:
		RET_NUM(currentFeedbackQuery);
	default:
		RET_NULL;
	}
}

} // namespace webgl
