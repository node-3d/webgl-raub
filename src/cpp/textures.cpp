#include "webgl.hpp"


namespace webgl {


DBG_EXPORT JS_METHOD(createTexture) { NAPI_ENV;
	GLuint texture;
	glGenTextures(1, &texture);
	
	RET_NUM(texture);
}


DBG_EXPORT JS_METHOD(deleteTexture) { NAPI_ENV;
	REQ_UINT32_ARG(0, texture);
	
	glDeleteTextures(1, reinterpret_cast<GLuint*>(&texture));
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(isTexture) { NAPI_ENV;
	REQ_UINT32_ARG(0, texture);
	
	RET_BOOL(glIsTexture(texture) != 0);
}


DBG_EXPORT JS_METHOD(bindTexture) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, texture);
	
	glBindTexture(target, texture);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(activeTexture) { NAPI_ENV;
	REQ_INT32_ARG(0, texture);
	
	glActiveTexture(texture);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(copyTexImage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, x);
	REQ_INT32_ARG(4, y);
	REQ_INT32_ARG(5, width);
	REQ_INT32_ARG(6, height);
	REQ_INT32_ARG(7, border);
	
	glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(copyTexSubImage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, x);
	REQ_INT32_ARG(5, y);
	REQ_INT32_ARG(6, width);
	REQ_INT32_ARG(7, height);
	
	glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(generateMipmap) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	
	glGenerateMipmap(target);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(getTexParameter) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint param_value = 0;
	glGetTexParameteriv(target, name, &param_value);
	
	RET_NUM(param_value);
}


DBG_EXPORT JS_METHOD(texImage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, width);
	REQ_INT32_ARG(4, height);
	REQ_INT32_ARG(5, border);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	
	if (info.Length() <= 8 || IS_ARG_EMPTY(8)) {
		glTexImage2D(
			target,
			level,
			internalformat,
			width,
			height,
			border,
			format,
			type,
			nullptr
		);
	} else if (info[8].IsNumber()) {
		// In WebGL2 the last parameter can be a byte offset if glBindBuffer()
		// was called with GL_PIXEL_UNPACK_BUFFER prior to glTexImage2D
		REQ_OFFS_ARG(8, offset);
		// From https://www.khronos.org/registry/OpenGL-Refpages/es3.0/html/glBindBuffer.xhtml
		// "The pointer parameter is interpreted as an offset within the buffer
		// object measured in basic machine units."
		glTexImage2D(
			target,
			level,
			internalformat,
			width,
			height,
			border,
			format,
			type,
			reinterpret_cast<void *>(offset)
		);
	} else {
		REQ_OBJ_ARG(8, image);
		
		void *ptr = getData(env, image);
		glTexImage2D(
			target,
			level,
			internalformat,
			width,
			height,
			border,
			format,
			type,
			ptr
		);
	}
	
	RET_UNDEFINED;
}

DBG_EXPORT JS_METHOD(texImage3D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, width);
	REQ_INT32_ARG(4, height);
	REQ_INT32_ARG(5, depth);
	REQ_INT32_ARG(6, border);
	REQ_INT32_ARG(7, format);
	REQ_INT32_ARG(8, type);
	
	if (info.Length() == 9 || IS_ARG_EMPTY(9)) {
		glTexImage3D(
			target,
			level,
			internalformat,
			width,
			height,
			depth,
			border,
			format,
			type,
			nullptr
		);
	} else {
		REQ_OBJ_ARG(9, image);
		
		void *ptr = getData(env, image);
		glTexImage3D(
			target,
			level,
			internalformat,
			width,
			height,
			depth,
			border,
			format,
			type,
			ptr
		);
	}
	
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(texParameterf) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_FLOAT_ARG(2, param);
	
	glTexParameterf(target, name, param);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(texParameteri) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_INT32_ARG(2, param);
	
	glTexParameteri(target, name, param);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(texStorage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, levels);
	REQ_INT32_ARG(2, format);
	REQ_INT32_ARG(3, width);
	REQ_INT32_ARG(4, height);
	
	glTexStorage2D(target, levels, format, width, height);
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(texSubImage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	
	if (info.Length() == 7 || IS_ARG_EMPTY(8)) {
		REQ_INT32_ARG(4, format);
		REQ_INT32_ARG(5, type);
		REQ_OBJ_ARG(6, image);
		
		void *pixels = getData(env, image);
		
		glTexSubImage2D(
			target,
			level,
			xoffset,
			yoffset,
			0,
			0,
			format,
			type,
			pixels
		);
		RET_UNDEFINED;
	}
	
	REQ_INT32_ARG(4, width);
	REQ_INT32_ARG(5, height);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	
	if (info.Length() <= 8 || IS_ARG_EMPTY(8)) {
		glTexSubImage2D(
			target,
			level,
			xoffset,
			yoffset,
			width,
			height,
			format,
			type,
			nullptr
		);
	} else {
		REQ_OBJ_ARG(8, image);
		void *pixels = getData(env, image);
		glTexSubImage2D(
			target,
			level,
			xoffset,
			yoffset,
			width,
			height,
			format,
			type,
			pixels
		);
	}
	
	RET_UNDEFINED;
}


DBG_EXPORT JS_METHOD(compressedTexSubImage2D) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, width);
	REQ_INT32_ARG(5, height);
	REQ_INT32_ARG(6, format);
	REQ_OBJ_ARG(7, image);
	
	int size = 0;
	void *pixels = nullptr;
	
	if (image.IsTypedArray() || image.IsArrayBuffer()) {
		pixels = getArrayData<uint8_t>(env, image, &size);
	} else if (image.IsBuffer()) {
		pixels = getBufferData<uint8_t>(env, image, &size);
	} else if (image.Has("data")) {
		Napi::Object data = image.Get("data").As<Napi::Object>();
		if (data.IsTypedArray() || data.IsArrayBuffer()) {
			pixels = getArrayData<uint8_t>(env, data, &size);
		} else if (data.IsBuffer()) {
			pixels = getBufferData<uint8_t>(env, data, &size);
		}
	}
	
	glCompressedTexSubImage2D(
		target,
		level,
		xoffset,
		yoffset,
		width,
		height,
		format,
		size,
		pixels
	);
	
	RET_UNDEFINED;
}


} // namespace webgl
