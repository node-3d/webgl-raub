#include <cstring>
#include <vector>
#include <iostream>

#include <node.h>
#include <node_buffer.h>

#include <GL/glew.h>

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
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		RET_VALUE(JS_INT(-1));
	} else {
		RET_VALUE(JS_INT(0));
	}
	
}


NAN_METHOD(uniform1f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glUniform1f(location, x);
	
}


NAN_METHOD(uniform2f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glUniform2f(location, x, y);
	
}


NAN_METHOD(uniform3f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glUniform3f(location, x, y, z);
	
}


NAN_METHOD(uniform4f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glUniform4f(location, x, y, z, w);
	
}


NAN_METHOD(uniform1i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	
	glUniform1i(location, x);
	
}


NAN_METHOD(uniform2i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	
	glUniform2i(location, x, y);
	
}


NAN_METHOD(uniform3i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	
	glUniform3i(location, x, y, z);
	
}


NAN_METHOD(uniform4i) {
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glUniform4i(location, x, y, z, w);
	
}


NAN_METHOD(uniform1fv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	
	glUniform1fv(location, num, ptr);
	
}


NAN_METHOD(uniform2fv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 2;
	
	glUniform2fv(location, num, ptr);
	
}


NAN_METHOD(uniform3fv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 3;
	
	glUniform3fv(location, num, ptr);
	
}


NAN_METHOD(uniform4fv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 4;
	
	glUniform4fv(location, num, ptr);
	
}


NAN_METHOD(uniform1iv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	
	glUniform1iv(location, num, ptr);
	
}


NAN_METHOD(uniform2iv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 2;
	
	glUniform2iv(location, num, ptr);
	
}


NAN_METHOD(uniform3iv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 3;
	
	glUniform3iv(location, num, ptr);
	
}


NAN_METHOD(uniform4iv) {
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 4;
	
	glUniform4iv(location, num, ptr);
	
}


NAN_METHOD(pixelStorei) {
	
	REQ_INT32_ARG(0, name);
	REQ_INT32_ARG(1, param);
	
	glPixelStorei(name, param);
	
}


NAN_METHOD(bindAttribLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	REQ_UTF8_ARG(2, name);
	
	glBindAttribLocation(program, index, *name);
	
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


NAN_METHOD(uniformMatrix2fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_BOOL_ARG(1, transpose);
	
	GLsizei count=0;
	GLfloat* data=getArrayData<GLfloat>(info[2], &count);
	
	if (count < 4) {
		Nan::ThrowError("Not enough data for UniformMatrix2fv");
	} else {
		glUniformMatrix2fv(location, count / 4, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(uniformMatrix3fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_BOOL_ARG(1, transpose);
	
	GLsizei count=0;
	GLfloat* data=getArrayData<GLfloat>(info[2], &count);
	
	if (count < 9) {
		Nan::ThrowError("Not enough data for UniformMatrix3fv");
	} else {
		glUniformMatrix3fv(location, count / 9, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(uniformMatrix4fv) {
	
	REQ_INT32_ARG(0, location);
	REQ_BOOL_ARG(1, transpose);
	
	GLsizei count=0;
	GLfloat* data=getArrayData<GLfloat>(info[2], &count);
	
	if (count < 16) {
		Nan::ThrowError("Not enough data for UniformMatrix4fv");
	} else {
		glUniformMatrix4fv(location, count / 16, transpose, data);
		RET_UNDEFINED;
	}
	
}


NAN_METHOD(generateMipmap) {
	
	REQ_INT32_ARG(0, target);
	
	glGenerateMipmap(target);
	
}


NAN_METHOD(getAttribLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(1, name);
	
	RET_VALUE(Nan::New<Number>(glGetAttribLocation(program, *name)));
	
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


NAN_METHOD(createShader) {
	
	REQ_INT32_ARG(0, id);
	
	GLuint shader = glCreateShader(id);
	
	#ifdef LOGGING
		cout<<"createShader "<<shader<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_SHADER, shader);
	
	RET_VALUE(Nan::New<Number>(shader));
	
}


NAN_METHOD(shaderSource) {
	
	REQ_INT32_ARG(0, id);
	REQ_UTF8_ARG(1, code);
	
	const char* codes[1];
	codes[0] = *code;
	GLint length=code.length();
	
	glShaderSource(id, 1, codes, &length);
	
}


NAN_METHOD(compileShader) {
	
	REQ_INT32_ARG(0, id);
	
	glCompileShader(id);
	
}


NAN_METHOD(frontFace) {
	
	REQ_INT32_ARG(0, id);
	
	glFrontFace(id);
	
}


NAN_METHOD(getShaderParameter) {
	
	REQ_INT32_ARG(0, shader);
	REQ_INT32_ARG(1, pname);
	
	int value = 0;
	
	switch (pname) {
	
	case GL_DELETE_STATUS:
	case GL_COMPILE_STATUS:
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_BOOL(static_cast<bool>(value!=0)));
		break;
	
	case GL_SHADER_TYPE:
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_NUM(static_cast<unsigned long>(value)));
		break;
	
	case GL_INFO_LOG_LENGTH:
	case GL_SHADER_SOURCE_LENGTH:
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_NUM(static_cast<long>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetShaderParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(getShaderInfoLog) {
	
	REQ_INT32_ARG(0, id);
	
	int Len = 1024;
	char Error[1024];
	glGetShaderInfoLog(id, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


NAN_METHOD(createProgram) {
	
	GLuint program = glCreateProgram();
	
	#ifdef LOGGING
		cout<<"createProgram "<<program<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_PROGRAM, program);
	
	RET_VALUE(Nan::New<Number>(program));
	
}


NAN_METHOD(attachShader) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, shader);
	
	glAttachShader(program, shader);
	
}


NAN_METHOD(linkProgram) {
	
	REQ_INT32_ARG(0, id);
	
	glLinkProgram(id);
	
}


NAN_METHOD(getProgramParameter) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	
	switch (name) {
		
	case GL_DELETE_STATUS:
	case GL_LINK_STATUS:
	case GL_VALIDATE_STATUS:
		glGetProgramiv(program, name, &value);
		RET_VALUE(JS_BOOL(static_cast<bool>(value!=0)));
		break;
	
	case GL_ATTACHED_SHADERS:
	case GL_ACTIVE_ATTRIBUTES:
	case GL_ACTIVE_UNIFORMS:
	case GL_INFO_LOG_LENGTH:
		glGetProgramiv(program, name, &value);
		RET_VALUE(JS_NUM(static_cast<long>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(getUniformLocation) {
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(1, name);
	
	RET_VALUE(JS_INT(glGetUniformLocation(program, *name)));
	
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


NAN_METHOD(createTexture) {
	
	GLuint texture;
	glGenTextures(1, &texture);
	
	#ifdef LOGGING
		cout<<"createTexture "<<texture<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_TEXTURE, texture);
	
	RET_VALUE(Nan::New<Number>(texture));
	
}


NAN_METHOD(bindTexture) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, texture);
	
	glBindTexture(target, texture);
	
}


NAN_METHOD(texImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, width);
	REQ_INT32_ARG(4, height);
	REQ_INT32_ARG(5, border);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	
	void *pixels = getImageData(info[8]);
	
	glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	
}


NAN_METHOD(texParameteri) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_INT32_ARG(2, param);
	
	glTexParameteri(target, name, param);
	
}


NAN_METHOD(texParameterf) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_FLOAT_ARG(2, param);
	
	glTexParameterf(target, name, param);
	
}


NAN_METHOD(clear) {
	
	REQ_INT32_ARG(0, target);
	
	glClear(target);
	
}


NAN_METHOD(useProgram) {
	
	REQ_INT32_ARG(0, id);
	
	glUseProgram(id);
	
}


NAN_METHOD(createBuffer) {
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	
	#ifdef LOGGING
		cout<<"createBuffer "<<buffer<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_BUFFER, buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(bindBuffer) {
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, buffer);
	
	glBindBuffer(target,buffer);
	
}


NAN_METHOD(createFramebuffer) {
	
	GLuint buffer;
	glGenFramebuffers(1, &buffer);
	
	#ifdef LOGGING
		cout<<"createFrameBuffer "<<buffer<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_FRAMEBUFFER, buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(bindFramebuffer) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindFramebuffer(target, buffer);
	
}


NAN_METHOD(framebufferTexture2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, textarget);
	REQ_INT32_ARG(3, texture);
	REQ_INT32_ARG(4, level);
	
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	
}


NAN_METHOD(bufferData) {
	
	REQ_INT32_ARG(0, target);
	
	if (info[1]->IsObject()) {
		
		REQ_ARRV_ARG(1, obj);
		REQ_INT32_ARG(2, usage);
		
		int element_size = 1;
		Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(obj);
		int size = arr->ByteLength()* element_size;
		void* data = arr->Buffer()->GetContents().Data();
		
		glBufferData(target, size, data, usage);
		
	} else if (info[1]->IsNumber()) {
		
		REQ_UINT32_ARG(1, size);
		REQ_INT32_ARG(2, usage);
		
		glBufferData(target, size, NULL, usage);
		
	}
	
}


NAN_METHOD(bufferSubData) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, offset);
	REQ_ARRV_ARG(2, arr);
	
	int element_size = 1;
	int size = arr->ByteLength() * element_size;
	void *data = arr->Buffer()->GetContents().Data();
	
	glBufferSubData(target, offset, size, data);
	
}


NAN_METHOD(blendEquation) {
	
	REQ_INT32_ARG(0, mode);
	
	glBlendEquation(mode);
	
}


NAN_METHOD(blendFunc) {
	
	REQ_INT32_ARG(0, sfactor);
	REQ_INT32_ARG(1, dfactor);
	
	glBlendFunc(sfactor,dfactor);
	
}


NAN_METHOD(enableVertexAttribArray) {
	
	REQ_INT32_ARG(0, id);
	
	glEnableVertexAttribArray(id);
	
}


NAN_METHOD(vertexAttribPointer) {
	
	REQ_INT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	REQ_BOOL_ARG(3, normalized);
	REQ_INT32_ARG(4, stride);
	REQ_OFFS_ARG(5, ptr);
	
	GLvoid *vertices = reinterpret_cast<GLvoid*>(ptr);
	
	// printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
	glVertexAttribPointer(indx, size, type, normalized, stride, vertices);
	
}


NAN_METHOD(activeTexture) {
	
	REQ_INT32_ARG(0, id);
	
	glActiveTexture(id);
	
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


NAN_METHOD(vertexAttrib1f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glVertexAttrib1f(location, x);
	
}


NAN_METHOD(vertexAttrib2f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glVertexAttrib2f(location, x, y);
	
}


NAN_METHOD(vertexAttrib3f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glVertexAttrib3f(location, x, y, z);
	
}


NAN_METHOD(vertexAttrib4f) {
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glVertexAttrib4f(location, x, y, z, w);
	
}


NAN_METHOD(vertexAttrib1fv) {
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib1fv(location, data);
	
}


NAN_METHOD(vertexAttrib2fv) {
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib2fv(location, data);
	
}


NAN_METHOD(vertexAttrib3fv) {
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib3fv(location, data);
	
}


NAN_METHOD(vertexAttrib4fv) {
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib4fv(location, data);
	
}


NAN_METHOD(blendColor) {
	
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glBlendColor(red, green, blue, alpha);
	
}


NAN_METHOD(blendEquationSeparate) {
	
	REQ_INT32_ARG(0, modeRGB);
	REQ_INT32_ARG(1, modeAlpha);
	
	glBlendEquationSeparate(modeRGB, modeAlpha);
	
}


NAN_METHOD(blendFuncSeparate) {
	
	REQ_INT32_ARG(0, srcRGB);
	REQ_INT32_ARG(1, dstRGB);
	REQ_INT32_ARG(2, srcAlpha);
	REQ_INT32_ARG(3, dstAlpha);
	
	glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	
}


NAN_METHOD(clearStencil) {
	
	REQ_INT32_ARG(0, s);
	
	glClearStencil(s);
	
}


NAN_METHOD(colorMask) {
	
	REQ_BOOL_ARG(0, red);
	REQ_BOOL_ARG(1, green);
	REQ_BOOL_ARG(2, blue);
	REQ_BOOL_ARG(3, alpha);
	
	glColorMask(red, green, blue, alpha);
	
}


NAN_METHOD(copyTexImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, x);
	REQ_INT32_ARG(4, y);
	REQ_INT32_ARG(5, width);
	REQ_INT32_ARG(6, height);
	REQ_INT32_ARG(7, border);
	
	glCopyTexImage2D( target, level, internalformat, x, y, width, height, border);
	
}


NAN_METHOD(copyTexSubImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, x);
	REQ_INT32_ARG(5, y);
	REQ_INT32_ARG(6, width);
	REQ_INT32_ARG(7, height);
	
	glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height);
	
}


NAN_METHOD(cullFace) {
	
	REQ_INT32_ARG(0, mode);
	
	glCullFace(mode);
	
}


NAN_METHOD(depthMask) {
	
	REQ_BOOL_ARG(0, flag);
	
	glDepthMask(flag);
	
}


NAN_METHOD(depthRange) {
	
	REQ_FLOAT_ARG(0, zNear);
	REQ_FLOAT_ARG(1, zFar);
	
	glDepthRangef(zNear, zFar);
	
}


NAN_METHOD(disableVertexAttribArray) {
	
	REQ_INT32_ARG(0, index);
	
	glDisableVertexAttribArray(index);
	
}


NAN_METHOD(hint) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, mode);
	
	glHint(target, mode);
	
}


NAN_METHOD(isEnabled) {
	
	REQ_INT32_ARG(0, cap);
	
	bool ret = glIsEnabled(cap)!=0;
	
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
	REQ_BOOL_ARG(1, invert);
	
	glSampleCoverage(value, invert);
	
}


NAN_METHOD(scissor) {
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	
	glScissor(x, y, width, height);
	
}


NAN_METHOD(stencilFunc) {
	
	REQ_INT32_ARG(0, func);
	REQ_INT32_ARG(1, ref);
	REQ_INT32_ARG(2, mask);
	
	glStencilFunc(func, ref, mask);
	
}


NAN_METHOD(stencilFuncSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, func);
	REQ_INT32_ARG(2, ref);
	REQ_INT32_ARG(3, mask);
	
	glStencilFuncSeparate(face, func, ref, mask);
	
}


NAN_METHOD(stencilMask) {
	
	REQ_UINT32_ARG(0, mask);
	
	glStencilMask(mask);
	
}


NAN_METHOD(stencilMaskSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_UINT32_ARG(1, mask);
	
	glStencilMaskSeparate(face, mask);
	
}


NAN_METHOD(stencilOp) {
	
	REQ_INT32_ARG(0, fail);
	REQ_INT32_ARG(1, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOp(fail, zfail, zpass);
	
}


NAN_METHOD(stencilOpSeparate) {
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, fail);
	REQ_INT32_ARG(2, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOpSeparate(face, fail, zfail, zpass);
	
}


NAN_METHOD(bindRenderbuffer) {
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindRenderbuffer(target, buffer);
	
}


NAN_METHOD(createRenderbuffer) {
	
	GLuint renderbuffers;
	glGenRenderbuffers(1, &renderbuffers);
	
	#ifdef LOGGING
		cout<<"createRenderBuffer "<<renderbuffers<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_RENDERBUFFER, renderbuffers);
	
	RET_VALUE(Nan::New<Number>(renderbuffers));
	
}


NAN_METHOD(deleteBuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteBuffers(1, reinterpret_cast<GLuint*>(&buffer));
	
}


NAN_METHOD(deleteFramebuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteFramebuffers(1, reinterpret_cast<GLuint*>(&buffer));
	
}


NAN_METHOD(deleteProgram) {
	
	REQ_UINT32_ARG(0, program);
	
	glDeleteProgram(program);
	
}


NAN_METHOD(deleteRenderbuffer) {
	
	REQ_UINT32_ARG(0, renderbuffer);
	
	glDeleteRenderbuffers(1, reinterpret_cast<GLuint*>(&renderbuffer));
	
}


NAN_METHOD(deleteShader) {
	
	REQ_UINT32_ARG(0, shader);
	
	glDeleteShader(shader);
	
}


NAN_METHOD(deleteTexture) {
	
	REQ_UINT32_ARG(0, texture);
	
	glDeleteTextures(1, reinterpret_cast<GLuint*>(&texture));
	
}


NAN_METHOD(detachShader) {
	
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, shader);
	
	glDetachShader(program, shader);
	
}


NAN_METHOD(framebufferRenderbuffer) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, renderbuffertarget);
	REQ_UINT32_ARG(3, renderbuffer);
	
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	
}


NAN_METHOD(getVertexAttribOffset) {
	
	REQ_UINT32_ARG(0, index);
	REQ_INT32_ARG(1, name);
	
	void *ret = NULL;
	glGetVertexAttribPointerv(index, name, &ret);
	
	RET_VALUE(JS_INT(ToGLuint(ret)));
	
}


NAN_METHOD(isBuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(Nan::New<Boolean>(glIsBuffer(buffer) != 0));
	
}


NAN_METHOD(isFramebuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsFramebuffer(buffer) != 0));
	
}


NAN_METHOD(isProgram) {
	
	REQ_UINT32_ARG(0, program);
	
	RET_VALUE(JS_BOOL(glIsProgram(program) != 0));
	
}


NAN_METHOD(isRenderbuffer) {
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsRenderbuffer(buffer) != 0));
	
}


NAN_METHOD(isShader) {
	
	REQ_UINT32_ARG(0, shader);
	
	RET_VALUE(JS_BOOL(glIsShader(shader) != 0));
	
}


NAN_METHOD(isTexture) {
	
	REQ_UINT32_ARG(0, texture);
	
	RET_VALUE(JS_BOOL(glIsTexture(texture) != 0));
	
}


NAN_METHOD(renderbufferStorage) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, internalformat);
	REQ_UINT32_ARG(2, width);
	REQ_UINT32_ARG(3, height);
	
	glRenderbufferStorage(target, internalformat, width, height);
	
}


NAN_METHOD(getShaderSource) {
	
	REQ_INT32_ARG(0, shader);
	
	GLint len;
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
	GLchar *source = new GLchar[len];
	glGetShaderSource(shader, len, NULL, source);
	
	Local<String> str = JS_STR(source);
	delete [] source;
	
	RET_VALUE(str);
	
}


NAN_METHOD(validateProgram) {
	
	REQ_INT32_ARG(0, program);
	
	glValidateProgram(program);
	
}


NAN_METHOD(texSubImage2D) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, width);
	REQ_INT32_ARG(5, height);
	REQ_INT32_ARG(6, format);
	REQ_INT32_ARG(7, type);
	void *pixels = getImageData(info[8]);
	
	glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
	
}


NAN_METHOD(readPixels) {
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	REQ_INT32_ARG(4, format);
	REQ_INT32_ARG(5, type);
	void *pixels = getImageData(info[6]);
	
	glReadPixels(x, y, width, height, format, type, pixels);
	
}


NAN_METHOD(getTexParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint param_value=0;
	glGetTexParameteriv(target, name, &param_value);
	
	RET_VALUE(Nan::New<Number>(param_value));
	
}


NAN_METHOD(getActiveAttrib) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length=0;
	GLenum type;
	GLsizei size;
	glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT(static_cast<int>(type)));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(getActiveUniform) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length=0;
	GLenum type;
	GLsizei size;
	glGetActiveUniform(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT(static_cast<int>(type)));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(getAttachedShaders) {
	
	REQ_INT32_ARG(0, program);
	
	GLuint shaders[1024];
	GLsizei count;
	glGetAttachedShaders(program, 1024, &count, shaders);
	
	Local<Array> shadersArr = Nan::New<Array>(count);
	for (int i = 0; i < count; i++) {
		shadersArr->Set(i, JS_INT(static_cast<int>(shaders[i])));
	}
	
	RET_VALUE(shadersArr);
	
}


NAN_METHOD(getParameter) {
	
	REQ_INT32_ARG(0, name);
	
	GLboolean bParams[4];
	const char *cParams;
	GLint iParams[4];
	GLfloat fParams[4];
	Local<Array> arr;
	
	switch(name) {
	
	// returns a boolean
	case GL_BLEND:
	case GL_CULL_FACE:
	case GL_DEPTH_TEST:
	case GL_DEPTH_WRITEMASK:
	case GL_DITHER:
	case GL_POLYGON_OFFSET_FILL:
	case GL_SAMPLE_COVERAGE_INVERT:
	case GL_SCISSOR_TEST:
	case GL_STENCIL_TEST:
	case 0x9240 /* UNPACK_FLIP_Y_WEBGL */:
	case 0x9241 /* UNPACK_PREMULTIPLY_ALPHA_WEBGL*/:
		glGetBooleanv(name, bParams);
		RET_VALUE(JS_BOOL(bParams[0] != 0));
		break;
	
	// returns a float
	case GL_DEPTH_CLEAR_VALUE:
	case GL_LINE_WIDTH:
	case GL_POLYGON_OFFSET_FACTOR:
	case GL_POLYGON_OFFSET_UNITS:
	case GL_SAMPLE_COVERAGE_VALUE:
		glGetFloatv(name, fParams);
		RET_VALUE(JS_NUM(fParams[0]));
		break;
	
	// returns a string
	case GL_RENDERER:
	case GL_SHADING_LANGUAGE_VERSION:
	case GL_VENDOR:
	case GL_VERSION:
	case GL_EXTENSIONS:
		cParams = reinterpret_cast<const char*>(glGetString(name));
		if (cParams != NULL) {
			RET_VALUE(JS_STR(cParams));
		} else {
			RET_UNDEFINED;
		}
		
		break;
	
	// returns a int32[2]
	case GL_MAX_VIEWPORT_DIMS:
		glGetIntegerv(name, iParams);
		arr = Nan::New<Array>(2);
		arr->Set(0, JS_INT(iParams[0]));
		arr->Set(1, JS_INT(iParams[1]));
		RET_VALUE(arr);
		break;
	
	
	// returns a int32[4]
	case GL_SCISSOR_BOX:
	case GL_VIEWPORT:
		glGetIntegerv(name, iParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_INT(iParams[0]));
		arr->Set(1, JS_INT(iParams[1]));
		arr->Set(2, JS_INT(iParams[2]));
		arr->Set(3, JS_INT(iParams[3]));
		RET_VALUE(arr);
		break;
	
	// returns a float[2]
	case GL_ALIASED_LINE_WIDTH_RANGE:
	case GL_ALIASED_POINT_SIZE_RANGE:
	case GL_DEPTH_RANGE:
		glGetFloatv(name, fParams);
		arr = Nan::New<Array>(2);
		arr->Set(0, JS_NUM(fParams[0]));
		arr->Set(1, JS_NUM(fParams[1]));
		RET_VALUE(arr);
		break;
	
	// returns a float[4]
	case GL_BLEND_COLOR:
	case GL_COLOR_CLEAR_VALUE:
		glGetFloatv(name, fParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_NUM(fParams[0]));
		arr->Set(1, JS_NUM(fParams[1]));
		arr->Set(2, JS_NUM(fParams[2]));
		arr->Set(3, JS_NUM(fParams[3]));
		RET_VALUE(arr);
		break;
	
	// returns a boolean[4]
	case GL_COLOR_WRITEMASK:
		glGetBooleanv(name, bParams);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_BOOL(bParams[0] != 0));
		arr->Set(1, JS_BOOL(bParams[1] != 0));
		arr->Set(2, JS_BOOL(bParams[2] != 0));
		arr->Set(3, JS_BOOL(bParams[3] != 0));
		RET_VALUE(arr);
		break;
	
	// returns an int
	case GL_ARRAY_BUFFER_BINDING:
	case GL_CURRENT_PROGRAM:
	case GL_ELEMENT_ARRAY_BUFFER_BINDING:
	case GL_FRAMEBUFFER_BINDING:
	case GL_RENDERBUFFER_BINDING:
	case GL_TEXTURE_BINDING_2D:
	case GL_TEXTURE_BINDING_CUBE_MAP:
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


NAN_METHOD(getBufferParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint params;
	glGetBufferParameteriv(target, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


NAN_METHOD(getFramebufferAttachmentParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, name);
	
	GLint params;
	glGetFramebufferAttachmentParameteriv(target, attachment, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


NAN_METHOD(getProgramInfoLog) {
	
	REQ_INT32_ARG(0, program);
	
	int Len = 1024;
	char Error[1024];
	glGetProgramInfoLog(program, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


NAN_METHOD(getRenderbufferParameter) {
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	glGetRenderbufferParameteriv(target, name, &value);
	
	RET_VALUE(JS_INT(value));
	
}


NAN_METHOD(getUniform) {
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, location);
	
	if (location < 0 ) {
		RET_UNDEFINED;
	}
	
	float data[16]; // worst case scenario is 16 floats
	glGetUniformfv(program, location, data);
	
	Local<Array> arr = Nan::New<Array>(16);
	for (int i = 0; i < 16; i++) {
		arr->Set(i, JS_NUM(data[i]));
	}
	
	RET_VALUE(arr);
	
}


NAN_METHOD(getVertexAttrib) {
	
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, pname);
	
	GLint value = 0;
	float vextex_attribs[4];
	Local<Array> arr;
	
	switch (pname) {
		
	case GL_VERTEX_ATTRIB_ARRAY_ENABLED:
	case GL_VERTEX_ATTRIB_ARRAY_NORMALIZED:
		glGetVertexAttribiv(index,pname, &value);
		RET_VALUE(JS_BOOL(value != 0));
		break;
	
	case GL_VERTEX_ATTRIB_ARRAY_SIZE:
	case GL_VERTEX_ATTRIB_ARRAY_STRIDE:
	case GL_VERTEX_ATTRIB_ARRAY_TYPE:
		glGetVertexAttribiv(index,pname, &value);
		RET_VALUE(JS_INT(value));
		break;
	
	case GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING:
		glGetVertexAttribiv(index,pname, &value);
		RET_VALUE(JS_INT(value));
		break;
	
	case GL_CURRENT_VERTEX_ATTRIB:
		glGetVertexAttribfv(index,pname,vextex_attribs);
		arr = Nan::New<Array>(4);
		arr->Set(0, JS_NUM(vextex_attribs[0]));
		arr->Set(1, JS_NUM(vextex_attribs[1]));
		arr->Set(2, JS_NUM(vextex_attribs[2]));
		arr->Set(3, JS_NUM(vextex_attribs[3]));
		RET_VALUE(arr);
		break;
	
	default:
		Nan::ThrowError("GetVertexAttrib: Invalid Enum");
	
	}
	
}


NAN_METHOD(getSupportedExtensions) {
	
	const char *extensions = reinterpret_cast<const char*>(glGetString(GL_EXTENSIONS));
	
	RET_VALUE(JS_STR(extensions));
	
}

// TODO GetExtension(name) return the extension name if found, should be an object...
NAN_METHOD(getExtension) {
	
	REQ_UTF8_ARG(0, name);
	
	char *sname = *name;
	char *extensions = (char*)(glGetString(GL_EXTENSIONS));
	char *ext = strcasestr(extensions, sname);
	
	if (ext == NULL) {
		RET_UNDEFINED;
	} else {
		 RET_VALUE(JS_STR(ext, static_cast<int>(strlen(sname))));
	}
	
}


NAN_METHOD(checkFramebufferStatus) {
	
	REQ_INT32_ARG(0, target);
	
	RET_VALUE(JS_INT(static_cast<int>(glCheckFramebufferStatus(target))));
	
}


struct GLObj {
	
	GLObjectType type;
	GLuint obj;
	
	GLObj(GLObjectType type, GLuint obj) {
		this->type = type;
		this->obj = obj;
	}
	
};


vector<GLObj*> globjs;
static bool atExit = false;

void registerGLObj(GLObjectType type, GLuint obj) {
	globjs.push_back(new GLObj(type,obj));
}


void unregisterGLObj(GLuint obj) {
	
	if (atExit) {
		return;
	}
	
	vector<GLObj*>::iterator it = globjs.begin();
	
	while (globjs.size() && it != globjs.end()) {
		
		GLObj *globj = *it;
		
		if (globj->obj == obj) {
			delete globj;
			globjs.erase(it);
			break;
		}
		
		++it;
		
	}
	
}

void deinit() {
	
	atExit = true;
	
	vector<GLObj*>::iterator it;
	
	#ifdef LOGGING
		cout<<"WebGL AtExit() called"<<endl;
		cout<<"	# objects allocated: "<<globjs.size()<<endl;
		
		it = globjs.begin();
		while(globjs.size() && it != globjs.end()) {
			
			GLObj *obj=*it;
			cout<<"[";
			
			switch(obj->type) {
			case GLOBJECT_TYPE_BUFFER: cout<<"buffer"; break;
			case GLOBJECT_TYPE_FRAMEBUFFER: cout<<"framebuffer"; break;
			case GLOBJECT_TYPE_PROGRAM: cout<<"program"; break;
			case GLOBJECT_TYPE_RENDERBUFFER: cout<<"renderbuffer"; break;
			case GLOBJECT_TYPE_SHADER: cout<<"shader"; break;
			case GLOBJECT_TYPE_TEXTURE: cout<<"texture"; break;
			};
			
			cout<<": "<<obj->obj<<"] ";
			++it;
			
		}
		cout<<endl;
	#endif
	
	it = globjs.begin();
	while(globjs.size() && it != globjs.end()) {
		
		GLObj *globj = *it;
		GLuint obj = globj->obj;
		
		switch(globj->type) {
		case GLOBJECT_TYPE_PROGRAM:
			#ifdef LOGGING
			cout<<"	Destroying GL program "<<obj<<endl;
			#endif
			glDeleteProgram(obj);
			break;
		case GLOBJECT_TYPE_BUFFER:
			#ifdef LOGGING
			cout<<"	Destroying GL buffer "<<obj<<endl;
			#endif
			glDeleteBuffers(1, &obj);
			break;
		case GLOBJECT_TYPE_FRAMEBUFFER:
			#ifdef LOGGING
			cout<<"	Destroying GL frame buffer "<<obj<<endl;
			#endif
			glDeleteFramebuffers(1, &obj);
			break;
		case GLOBJECT_TYPE_RENDERBUFFER:
			#ifdef LOGGING
			cout<<"	Destroying GL render buffer "<<obj<<endl;
			#endif
			glDeleteRenderbuffers(1, &obj);
			break;
		case GLOBJECT_TYPE_SHADER:
			#ifdef LOGGING
			cout<<"	Destroying GL shader "<<obj<<endl;
			#endif
			glDeleteShader(obj);
			break;
		case GLOBJECT_TYPE_TEXTURE:
			#ifdef LOGGING
			cout<<"	Destroying GL texture "<<obj<<endl;
			#endif
			glDeleteTextures(1, &obj);
			break;
		default:
			#ifdef LOGGING
			cout<<"	Unknown object "<<obj<<endl;
			#endif
			break;
		}
		
		delete globj;
		++it;
		
	}
	
	globjs.clear();
	
}

} // namespace webgl
