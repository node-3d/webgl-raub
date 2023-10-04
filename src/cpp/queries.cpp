#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createQuery) { NAPI_ENV;
	GLuint query_ids[1];
	glGenQueries(1, query_ids);
	RET_NUM(JS_NUM(query_ids[0]));
}


DBG_EXPORT JS_METHOD(deleteQuery) { NAPI_ENV;
	REQ_UINT32_ARG(0, query);
	GLuint query_ids[1] = {query};
	glDeleteQueries(1, query_ids);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isQuery) { NAPI_ENV;
	REQ_UINT32_ARG(0, query);
	
	RET_BOOL(glIsQuery(query) != 0);
}

//
DBG_EXPORT JS_METHOD(beginQuery) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, query);
	
	glBeginQuery(target, query);
	
	RET_UNDEFINED;
}
DBG_EXPORT JS_METHOD(endQuery) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	glEndQuery(target);
	
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(getQueryParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, query);
	REQ_INT32_ARG(1, pname);
	
	int value = 0;
	
	switch (pname) {
	
	case GL_QUERY_RESULT_AVAILABLE:
		glGetQueryObjectiv(query, pname, &value);
		RET_BOOL(value != 0);
		break;
	
	case GL_QUERY_RESULT:
		glGetQueryObjectiv(query, pname, &value);
		RET_NUM(value);
		break;
		
	default:
		JS_THROW("getQueryParameter: Invalid Enum.");
		RET_NULL;
	}
}

} // namespace webgl
