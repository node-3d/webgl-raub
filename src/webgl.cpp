#include <cstring>
#include <vector>
#include <iostream>

#include <GL/glew.h>

#include <node.h>
#include <node_buffer.h>

#include "webgl.hpp"
#include "image.hpp"

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


template<typename Type>
inline Type* getArrayData(Local<Value> arg, int *num = NULL) {
	
	Type *data = NULL;
	
	if (num) {
		*num = 0;
	}
	
	if ( ! arg->IsNull() ) {
		
		if (arg->IsArray()) {
			Nan::ThrowError("Array is not supported here");
		} else if (arg->IsObject()) {
			Local<ArrayBufferView> arr = Local<ArrayBufferView>::Cast(arg);
			if (num)
				*num = arr->ByteLength() / sizeof(Type);
			data = reinterpret_cast<Type*>(arr->Buffer()->GetContents().Data());
		} else {
			Nan::ThrowError("Bad array argument");
		}
		
	}
	
	return data;
	
}


inline void *getImageData(Local<Value> arg) {
	
	void *pixels = NULL;
	
	if ( ! arg->IsNull() ) {
		
		Local<Object> obj = Local<Object>::Cast(arg);
		
		if ( ! obj->IsObject() ) {
			Nan::ThrowError("Bad texture argument");
		} else if (obj->IsArrayBufferView()) {
			int num;
			pixels = getArrayData<BYTE>(obj, &num);
		} else {
			pixels = node::Buffer::Data(Nan::Get(obj, JS_STR("data")).ToLocalChecked());
		}
		
	}
	
	return pixels;
	
}


NAN_METHOD(Init) { NAN_HS;
	
	GLenum err = glewInit();
	
	if (GLEW_OK != err) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		RET_VALUE(JS_INT(-1));
	} else {
		RET_VALUE(JS_INT(0));
	}
	
}


NAN_METHOD(Uniform1f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glUniform1f(location, x);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform2f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glUniform2f(location, x, y);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform3f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glUniform3f(location, x, y, z);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform4f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glUniform4f(location, x, y, z, w);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform1i) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	
	glUniform1i(location, x);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform2i) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	
	glUniform2i(location, x, y);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform3i) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	
	glUniform3i(location, x, y, z);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform4i) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_INT32_ARG(1, x);
	REQ_INT32_ARG(2, y);
	REQ_INT32_ARG(3, z);
	REQ_INT32_ARG(4, w);
	
	glUniform4i(location, x, y, z, w);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform1fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	
	glUniform1fv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform2fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 2;
	
	glUniform2fv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform3fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 3;
	
	glUniform3fv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform4fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLfloat *ptr = getArrayData<GLfloat>(info[1], &num);
	num /= 4;
	
	glUniform4fv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform1iv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	
	glUniform1iv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform2iv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 2;
	
	glUniform2iv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform3iv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 3;
	
	glUniform3iv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Uniform4iv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	
	int num = 0;
	GLint *ptr = getArrayData<GLint>(info[1], &num);
	num /= 4;
	
	glUniform4iv(location, num, ptr);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(PixelStorei) { NAN_HS;
	
	REQ_INT32_ARG(0, name);
	REQ_INT32_ARG(1, param);
	
	glPixelStorei(name, param);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BindAttribLocation) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	REQ_UTF8_ARG(2, name);
	
	glBindAttribLocation(program, index, *name);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetError) { NAN_HS;
	
	RET_VALUE(Nan::New<Integer>(glGetError()));
	
}


NAN_METHOD(DrawArrays) { NAN_HS;
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, first);
	REQ_INT32_ARG(2, count);
	
	glDrawArrays(mode, first, count);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(UniformMatrix2fv) { NAN_HS;
	
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


NAN_METHOD(UniformMatrix3fv) { NAN_HS;
	
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


NAN_METHOD(UniformMatrix4fv) { NAN_HS;
	
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


NAN_METHOD(GenerateMipmap) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	
	glGenerateMipmap(target);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetAttribLocation) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(1, name);
	
	RET_VALUE(Nan::New<Number>(glGetAttribLocation(program, *name)));
	
}


NAN_METHOD(DepthFunc) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glDepthFunc(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Viewport) { NAN_HS;
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, w);
	REQ_INT32_ARG(3, h);
	
	glViewport(x, y, w, h);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CreateShader) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	GLuint shader = glCreateShader(id);
	
	#ifdef LOGGING
		cout<<"createShader "<<shader<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_SHADER, shader);
	
	RET_VALUE(Nan::New<Number>(shader));
	
}


NAN_METHOD(ShaderSource) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	REQ_UTF8_ARG(1, code);
	
	const char* codes[1];
	codes[0] = *code;
	GLint length=code.length();
	
	glShaderSource(id, 1, codes, &length);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CompileShader) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glCompileShader(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(FrontFace) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glFrontFace(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetShaderParameter) { NAN_HS;
	
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
		RET_VALUE(JS_FLOAT(static_cast<unsigned long>(value)));
		break;
	
	case GL_INFO_LOG_LENGTH:
	case GL_SHADER_SOURCE_LENGTH:
		glGetShaderiv(shader, pname, &value);
		RET_VALUE(JS_FLOAT(static_cast<long>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetShaderParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(GetShaderInfoLog) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	int Len = 1024;
	char Error[1024];
	glGetShaderInfoLog(id, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


NAN_METHOD(CreateProgram) { NAN_HS;
	
	GLuint program = glCreateProgram();
	
	#ifdef LOGGING
		cout<<"createProgram "<<program<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_PROGRAM, program);
	
	RET_VALUE(Nan::New<Number>(program));
	
}


NAN_METHOD(AttachShader) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, shader);
	
	glAttachShader(program, shader);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(LinkProgram) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glLinkProgram(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetProgramParameter) { NAN_HS;
	
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
		RET_VALUE(JS_FLOAT(static_cast<long>(value)));
		break;
	
	default:
		Nan::ThrowTypeError("GetProgramParameter: Invalid Enum");
	
	}
	
}


NAN_METHOD(GetUniformLocation) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_UTF8_ARG(0, name);
	
	RET_VALUE(JS_INT(glGetUniformLocation(program, *name)));
	
}


NAN_METHOD(ClearColor) { NAN_HS;
	
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glClearColor(red, green, blue, alpha);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(ClearDepth) { NAN_HS;
	
	REQ_FLOAT_ARG(0, depth);
	glClearDepth(depth);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Disable) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glDisable(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Enable) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glEnable(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CreateTexture) { NAN_HS;
	
	GLuint texture;
	glGenTextures(1, &texture);
	
	#ifdef LOGGING
		cout<<"createTexture "<<texture<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_TEXTURE, texture);
	
	RET_VALUE(Nan::New<Number>(texture));
	
}


NAN_METHOD(BindTexture) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, texture);
	
	glBindTexture(target, texture);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(TexImage2D) { NAN_HS;
	
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
	
	RET_UNDEFINED;
	
}


NAN_METHOD(TexParameteri) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_INT32_ARG(2, param);
	
	glTexParameteri(target, name, param);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(TexParameterf) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	REQ_FLOAT_ARG(2, param);
	
	glTexParameterf(target, name, param);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Clear) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	
	glClear(target);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(UseProgram) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glUseProgram(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CreateBuffer) { NAN_HS;
	
	GLuint buffer;
	glGenBuffers(1, &buffer);
	
	#ifdef LOGGING
		cout<<"createBuffer "<<buffer<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_BUFFER, buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(BindBuffer) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_UINT32_ARG(1, buffer);
	
	glBindBuffer(target,buffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CreateFramebuffer) { NAN_HS;
	
	GLuint buffer;
	glGenFramebuffers(1, &buffer);
	
	#ifdef LOGGING
		cout<<"createFrameBuffer "<<buffer<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_FRAMEBUFFER, buffer);
	
	RET_VALUE(Nan::New<Number>(buffer));
	
}


NAN_METHOD(BindFramebuffer) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindFramebuffer(target, buffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(FramebufferTexture2D) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, textarget);
	REQ_INT32_ARG(3, texture);
	REQ_INT32_ARG(4, level);
	
	glFramebufferTexture2D(target, attachment, textarget, texture, level);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BufferData) { NAN_HS;
	
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
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BufferSubData) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, offset);
	REQ_ARRV_ARG(2, arr);
	
	int element_size = 1;
	int size = arr->ByteLength() * element_size;
	void *data = arr->Buffer()->GetContents().Data();
	
	glBufferSubData(target, offset, size, data);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BlendEquation) { NAN_HS;
	
	REQ_INT32_ARG(0, mode);
	
	glBlendEquation(mode);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BlendFunc) { NAN_HS;
	
	REQ_INT32_ARG(0, sfactor);
	REQ_INT32_ARG(1, dfactor);
	
	glBlendFunc(sfactor,dfactor);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(EnableVertexAttribArray) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glEnableVertexAttribArray(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttribPointer) { NAN_HS;
	
	REQ_INT32_ARG(0, indx);
	REQ_INT32_ARG(1, size);
	REQ_INT32_ARG(2, type);
	REQ_BOOL_ARG(3, normalized);
	REQ_INT32_ARG(4, stride);
	REQ_INT32_ARG(5, offset);
	
	// printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
	glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(ActiveTexture) { NAN_HS;
	
	REQ_INT32_ARG(0, id);
	
	glActiveTexture(id);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DrawElements) { NAN_HS;
	
	REQ_INT32_ARG(0, mode);
	REQ_INT32_ARG(1, count);
	REQ_INT32_ARG(2, type);
	REQ_UINT32_ARG(3, ptr);
	
	GLvoid *indices = reinterpret_cast<GLvoid*>(ptr);
	
	glDrawElements(mode, count, type, indices);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Flush) { NAN_HS;
	
	glFlush();
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Finish) { NAN_HS;
	
	glFinish();
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib1f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	
	glVertexAttrib1f(location, x);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib2f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	
	glVertexAttrib2f(location, x, y);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib3f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	
	glVertexAttrib3f(location, x, y, z);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib4f) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	REQ_FLOAT_ARG(1, x);
	REQ_FLOAT_ARG(2, y);
	REQ_FLOAT_ARG(3, z);
	REQ_FLOAT_ARG(4, w);
	
	glVertexAttrib4f(location, x, y, z, w);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib1fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib1fv(location, data);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib2fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib2fv(location, data);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib3fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib3fv(location, data);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(VertexAttrib4fv) { NAN_HS;
	
	REQ_INT32_ARG(0, location);
	GLfloat *data = getArrayData<GLfloat>(info[1]);
	
	glVertexAttrib4fv(location, data);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BlendColor) { NAN_HS;
	
	REQ_FLOAT_ARG(0, red);
	REQ_FLOAT_ARG(1, green);
	REQ_FLOAT_ARG(2, blue);
	REQ_FLOAT_ARG(3, alpha);
	
	glBlendColor(red, green, blue, alpha);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BlendEquationSeparate) { NAN_HS;
	
	REQ_INT32_ARG(0, modeRGB);
	REQ_INT32_ARG(1, modeAlpha);
	
	glBlendEquationSeparate(modeRGB, modeAlpha);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BlendFuncSeparate) { NAN_HS;
	
	REQ_INT32_ARG(0, srcRGB);
	REQ_INT32_ARG(1, dstRGB);
	REQ_INT32_ARG(2, srcAlpha);
	REQ_INT32_ARG(3, dstAlpha);
	
	glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(ClearStencil) { NAN_HS;
	
	REQ_INT32_ARG(0, s);
	
	glClearStencil(s);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(ColorMask) { NAN_HS;
	
	REQ_BOOL_ARG(0, red);
	REQ_BOOL_ARG(1, green);
	REQ_BOOL_ARG(2, blue);
	REQ_BOOL_ARG(3, alpha);
	
	glColorMask(red, green, blue, alpha);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CopyTexImage2D) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, internalformat);
	REQ_INT32_ARG(3, x);
	REQ_INT32_ARG(4, y);
	REQ_INT32_ARG(5, width);
	REQ_INT32_ARG(6, height);
	REQ_INT32_ARG(7, border);
	
	glCopyTexImage2D( target, level, internalformat, x, y, width, height, border);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CopyTexSubImage2D) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, level);
	REQ_INT32_ARG(2, xoffset);
	REQ_INT32_ARG(3, yoffset);
	REQ_INT32_ARG(4, x);
	REQ_INT32_ARG(5, y);
	REQ_INT32_ARG(6, width);
	REQ_INT32_ARG(7, height);
	
	glCopyTexSubImage2D( target, level, xoffset, yoffset, x, y, width, height);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CullFace) { NAN_HS;
	
	REQ_INT32_ARG(0, mode);
	
	glCullFace(mode);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DepthMask) { NAN_HS;
	
	REQ_BOOL_ARG(0, flag);
	
	glDepthMask(flag);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DepthRange) { NAN_HS;
	
	REQ_FLOAT_ARG(0, zNear);
	REQ_FLOAT_ARG(1, zFar);
	
	glDepthRangef(zNear, zFar);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DisableVertexAttribArray) { NAN_HS;
	
	REQ_INT32_ARG(0, index);
	
	glDisableVertexAttribArray(index);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Hint) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, mode);
	
	glHint(target, mode);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(IsEnabled) { NAN_HS;
	
	REQ_INT32_ARG(0, cap);
	
	bool ret = glIsEnabled(cap)!=0;
	
	RET_VALUE(Nan::New<Boolean>(ret));
	
}


NAN_METHOD(LineWidth) { NAN_HS;
	
	REQ_FLOAT_ARG(0, width);
	
	glLineWidth(width);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(PolygonOffset) { NAN_HS;
	
	REQ_FLOAT_ARG(0, factor);
	REQ_FLOAT_ARG(1, units);
	
	glPolygonOffset(factor, units);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(SampleCoverage) { NAN_HS;
	
	REQ_FLOAT_ARG(0, value);
	REQ_BOOL_ARG(1, invert);
	
	glSampleCoverage(value, invert);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(Scissor) { NAN_HS;
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	
	glScissor(x, y, width, height);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilFunc) { NAN_HS;
	
	REQ_INT32_ARG(0, func);
	REQ_INT32_ARG(1, ref);
	REQ_INT32_ARG(2, mask);
	
	glStencilFunc(func, ref, mask);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilFuncSeparate) { NAN_HS;
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, func);
	REQ_INT32_ARG(2, ref);
	REQ_INT32_ARG(3, mask);
	
	glStencilFuncSeparate(face, func, ref, mask);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilMask) { NAN_HS;
	
	REQ_UINT32_ARG(0, mask);
	
	glStencilMask(mask);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilMaskSeparate) { NAN_HS;
	
	REQ_INT32_ARG(0, face);
	REQ_UINT32_ARG(1, mask);
	
	glStencilMaskSeparate(face, mask);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilOp) { NAN_HS;
	
	REQ_INT32_ARG(0, fail);
	REQ_INT32_ARG(1, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOp(fail, zfail, zpass);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(StencilOpSeparate) { NAN_HS;
	
	REQ_INT32_ARG(0, face);
	REQ_INT32_ARG(1, fail);
	REQ_INT32_ARG(2, zfail);
	REQ_INT32_ARG(2, zpass);
	
	glStencilOpSeparate(face, fail, zfail, zpass);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(BindRenderbuffer) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	LET_INT32_ARG(1, buffer);
	
	glBindRenderbuffer(target, buffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(CreateRenderbuffer) { NAN_HS;
	
	GLuint renderbuffers;
	glGenRenderbuffers(1, &renderbuffers);
	
	#ifdef LOGGING
		cout<<"createRenderBuffer "<<renderbuffers<<endl;
	#endif
	
	registerGLObj(GLOBJECT_TYPE_RENDERBUFFER, renderbuffers);
	
	RET_VALUE(Nan::New<Number>(renderbuffers));
	
}


NAN_METHOD(DeleteBuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteBuffers(1, &buffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DeleteFramebuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, buffer);
	
	glDeleteFramebuffers(1, &buffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DeleteProgram) { NAN_HS;
	
	REQ_UINT32_ARG(0, program);
	
	glDeleteProgram(program);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DeleteRenderbuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, renderbuffer);
	
	glDeleteRenderbuffers(1, &renderbuffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DeleteShader) { NAN_HS;
	
	REQ_UINT32_ARG(0, shader);
	
	glDeleteShader(shader);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DeleteTexture) { NAN_HS;
	
	REQ_UINT32_ARG(0, texture);
	
	glDeleteTextures(1, &texture);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(DetachShader) { NAN_HS;
	
	REQ_UINT32_ARG(0, program);
	REQ_UINT32_ARG(1, shader);
	
	glDetachShader(program, shader);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(FramebufferRenderbuffer) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, renderbuffertarget);
	REQ_UINT32_ARG(3, renderbuffer);
	
	glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetVertexAttribOffset) { NAN_HS;
	
	REQ_UINT32_ARG(0, index);
	REQ_INT32_ARG(1, name);
	
	void *ret = NULL;
	glGetVertexAttribPointerv(index, name, &ret);
	
	RET_VALUE(JS_INT(ToGLuint(ret)));
	
}


NAN_METHOD(IsBuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(Nan::New<Boolean>(glIsBuffer(buffer) != 0));
	
}


NAN_METHOD(IsFramebuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsFramebuffer(buffer) != 0));
	
}


NAN_METHOD(IsProgram) { NAN_HS;
	
	REQ_UINT32_ARG(0, program);
	
	RET_VALUE(JS_BOOL(glIsProgram(program) != 0));
	
}


NAN_METHOD(IsRenderbuffer) { NAN_HS;
	
	REQ_UINT32_ARG(0, buffer);
	
	RET_VALUE(JS_BOOL(glIsRenderbuffer(buffer) != 0));
	
}


NAN_METHOD(IsShader) { NAN_HS;
	
	REQ_UINT32_ARG(0, shader);
	
	RET_VALUE(JS_BOOL(glIsShader(shader) != 0));
	
}


NAN_METHOD(IsTexture) { NAN_HS;
	
	REQ_UINT32_ARG(0, texture);
	
	RET_VALUE(JS_BOOL(glIsTexture(texture) != 0));
	
}


NAN_METHOD(RenderbufferStorage) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, internalformat);
	REQ_UINT32_ARG(2, width);
	REQ_UINT32_ARG(3, height);
	
	glRenderbufferStorage(target, internalformat, width, height);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetShaderSource) { NAN_HS;
	
	REQ_INT32_ARG(0, shader);
	
	GLint len;
	glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &len);
	GLchar *source = new GLchar[len];
	glGetShaderSource(shader, len, NULL, source);
	
	Local<String> str = JS_STR(source);
	delete source;
	
	RET_VALUE(str);
	
}


NAN_METHOD(ValidateProgram) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	
	glValidateProgram(program);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(TexSubImage2D) { NAN_HS;
	
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
	
	RET_UNDEFINED;
	
}


NAN_METHOD(ReadPixels) { NAN_HS;
	
	REQ_INT32_ARG(0, x);
	REQ_INT32_ARG(1, y);
	REQ_INT32_ARG(2, width);
	REQ_INT32_ARG(3, height);
	REQ_INT32_ARG(4, format);
	REQ_INT32_ARG(5, type);
	void *pixels = getImageData(info[6]);
	
	glReadPixels(x, y, width, height, format, type, pixels);
	
	RET_UNDEFINED;
	
}


NAN_METHOD(GetTexParameter) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint param_value=0;
	glGetTexParameteriv(target, name, &param_value);
	
	RET_VALUE(Nan::New<Number>(param_value));
	
}


NAN_METHOD(GetActiveAttrib) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length=0;
	GLenum type;
	GLsizei size;
	glGetActiveAttrib(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT((int)type));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(GetActiveUniform) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, index);
	
	char name[1024];
	GLsizei length=0;
	GLenum type;
	GLsizei size;
	glGetActiveUniform(program, index, 1024, &length, &size, &type, name);
	
	Local<Array> activeInfo = Nan::New<Array>(3);
	activeInfo->Set(JS_STR("size"), JS_INT(size));
	activeInfo->Set(JS_STR("type"), JS_INT((int)type));
	activeInfo->Set(JS_STR("name"), JS_STR(name));
	
	RET_VALUE(activeInfo);
	
}


NAN_METHOD(GetAttachedShaders) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	
	GLuint shaders[1024];
	GLsizei count;
	glGetAttachedShaders(program, 1024, &count, shaders);
	
	Local<Array> shadersArr = Nan::New<Array>(count);
	for(int i=0;i<count;i++)
		shadersArr->Set(i, JS_INT((int)shaders[i]));
	
	RET_VALUE(shadersArr);
	
}


NAN_METHOD(GetParameter) { NAN_HS;
	
	REQ_INT32_ARG(0, name);
	
	switch(name) {
		
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
		// return a boolean
		GLboolean params;
		glGetBooleanv(name, &params);
		RET_VALUE(JS_BOOL(params!=0));
		break;
	
	case GL_DEPTH_CLEAR_VALUE:
	case GL_LINE_WIDTH:
	case GL_POLYGON_OFFSET_FACTOR:
	case GL_POLYGON_OFFSET_UNITS:
	case GL_SAMPLE_COVERAGE_VALUE:
		// return a float
		GLfloat params;
		glGetFloatv(name, &params);
		RET_VALUE(JS_FLOAT(params));
		break;
	
	case GL_RENDERER:
	case GL_SHADING_LANGUAGE_VERSION:
	case GL_VENDOR:
	case GL_VERSION:
	case GL_EXTENSIONS:
		// return a string
		char *params=(char*) ::glGetString(name);
		
		if (params!=NULL) {
			RET_VALUE(JS_STR(params));
		} else {
			RET_UNDEFINED;
		}
		
		break;
	
	case GL_MAX_VIEWPORT_DIMS:
		// return a int32[2]
		GLint params[2];
		glGetIntegerv(name, params);
		
		Local<Array> arr=Nan::New<Array>(2);
		arr->Set(0,JS_INT(params[0]));
		arr->Set(1,JS_INT(params[1]));
		RET_VALUE(arr);
		break;
	
	case GL_SCISSOR_BOX:
	case GL_VIEWPORT:
		// return a int32[4]
		GLint params[4];
		glGetIntegerv(name, params);
		
		Local<Array> arr=Nan::New<Array>(4);
		arr->Set(0,JS_INT(params[0]));
		arr->Set(1,JS_INT(params[1]));
		arr->Set(2,JS_INT(params[2]));
		arr->Set(3,JS_INT(params[3]));
		RET_VALUE(arr);
		break;
	
	case GL_ALIASED_LINE_WIDTH_RANGE:
	case GL_ALIASED_POINT_SIZE_RANGE:
	case GL_DEPTH_RANGE:
		// return a float[2]
		GLfloat params[2];
		glGetFloatv(name, params);
		Local<Array> arr=Nan::New<Array>(2);
		arr->Set(0,JS_FLOAT(params[0]));
		arr->Set(1,JS_FLOAT(params[1]));
		RET_VALUE(arr);
		break;
	
	case GL_BLEND_COLOR:
	case GL_COLOR_CLEAR_VALUE:
		// return a float[4]
		GLfloat params[4];
		glGetFloatv(name, params);
		Local<Array> arr=Nan::New<Array>(4);
		arr->Set(0,JS_FLOAT(params[0]));
		arr->Set(1,JS_FLOAT(params[1]));
		arr->Set(2,JS_FLOAT(params[2]));
		arr->Set(3,JS_FLOAT(params[3]));
		RET_VALUE(arr);
		break;
	
	case GL_COLOR_WRITEMASK:
		// return a boolean[4]
		GLboolean params[4];
		glGetBooleanv(name, params);
		Local<Array> arr=Nan::New<Array>(4);
		arr->Set(0,JS_BOOL(params[0]==1));
		arr->Set(1,JS_BOOL(params[1]==1));
		arr->Set(2,JS_BOOL(params[2]==1));
		arr->Set(3,JS_BOOL(params[3]==1));
		RET_VALUE(arr);
		break;
	
	case GL_ARRAY_BUFFER_BINDING:
	case GL_CURRENT_PROGRAM:
	case GL_ELEMENT_ARRAY_BUFFER_BINDING:
	case GL_FRAMEBUFFER_BINDING:
	case GL_RENDERBUFFER_BINDING:
	case GL_TEXTURE_BINDING_2D:
	case GL_TEXTURE_BINDING_CUBE_MAP:
		GLint params;
		::glGetIntegerv(name, &params);
		RET_VALUE(JS_INT(params));
		break;
	
	default:
		// return a long
		GLint params;
		glGetIntegerv(name, &params);
		RET_VALUE(JS_INT(params));
	
	}
	
}


NAN_METHOD(GetBufferParameter) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	GLint params;
	glGetBufferParameteriv(target, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


NAN_METHOD(GetFramebufferAttachmentParameter) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, attachment);
	REQ_INT32_ARG(2, name);
	
	GLint params;
	glGetFramebufferAttachmentParameteriv(target, attachment, name, &params);
	
	RET_VALUE(JS_INT(params));
	
}


NAN_METHOD(GetProgramInfoLog) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	
	int Len = 1024;
	char Error[1024];
	glGetProgramInfoLog(program, 1024, &Len, Error);
	
	RET_VALUE(JS_STR(Error));
	
}


NAN_METHOD(GetRenderbufferParameter) { NAN_HS;
	
	REQ_INT32_ARG(0, target);
	REQ_INT32_ARG(1, name);
	
	int value = 0;
	glGetRenderbufferParameteriv(target, name, &value);
	
	RET_VALUE(JS_INT(value));
	
}


NAN_METHOD(GetUniform) { NAN_HS;
	
	REQ_INT32_ARG(0, program);
	REQ_INT32_ARG(1, location);
	
	if (location < 0 ) {
		RET_UNDEFINED;
	}
	
	float data[16]; // worst case scenario is 16 floats
	glGetUniformfv(program, location, data);
	
	Local<Array> arr=Nan::New<Array>(16);
	for(int i = 0; i < 16; i++) {
		arr->Set(i,JS_FLOAT(data[i]));
	}
	
	RET_VALUE(arr);
	
}


NAN_METHOD(GetVertexAttrib) { NAN_HS;
	
	REQ_INT32_ARG(0, index);
	REQ_INT32_ARG(1, pname);
	
	GLint value = 0;
	
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
		float vextex_attribs[4];
		glGetVertexAttribfv(index,pname,vextex_attribs);
		Local<Array> arr=Nan::New<Array>(4);
		arr->Set(0,JS_FLOAT(vextex_attribs[0]));
		arr->Set(1,JS_FLOAT(vextex_attribs[1]));
		arr->Set(2,JS_FLOAT(vextex_attribs[2]));
		arr->Set(3,JS_FLOAT(vextex_attribs[3]));
		RET_VALUE(arr);
		break;
	
	default:
		Nan::ThrowError("GetVertexAttrib: Invalid Enum");
	
	}
	
}


NAN_METHOD(GetSupportedExtensions) { NAN_HS;
	
	char *extensions = static_cast<char*>(glGetString(GL_EXTENSIONS));
	
	RET_VALUE(JS_STR(extensions));
	
}

// TODO GetExtension(name) return the extension name if found, should be an object...
NAN_METHOD(GetExtension) { NAN_HS;
	
	REQ_UTF8_ARG(0, name);
	
	char *sname=*name;
	char *extensions=(char*) glGetString(GL_EXTENSIONS);
	char *ext=strcasestr(extensions, sname);
	
	if (ext==NULL) {
		RET_UNDEFINED;
	} else {
		 RET_VALUE(JS_STR(ext, static_cast<int>(strlen(sname))));
	}
	
}


NAN_METHOD(CheckFramebufferStatus) { NAN_HS;
	
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

void AtExit() {
	
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
