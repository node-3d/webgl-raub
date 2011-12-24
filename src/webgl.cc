#include <iostream>
using namespace std;

#include "webgl.h"
#include "image.h"

using namespace node;
using namespace v8;

static int SizeOfArrayElementForType(v8::ExternalArrayType type) {
  switch (type) {
  case v8::kExternalByteArray:
  case v8::kExternalUnsignedByteArray:
    return 1;
  case v8::kExternalShortArray:
  case v8::kExternalUnsignedShortArray:
    return 2;
  case v8::kExternalIntArray:
  case v8::kExternalUnsignedIntArray:
  case v8::kExternalFloatArray:
    return 4;
  default:
    return 0;
  }
}

void *getImageData(Local<Value> arg) {
  void *pixels=NULL;
  Local<Object> obj = Local<Object>::Cast(arg);
  if(!obj->IsObject())
    ThrowException(JS_STR("Bad texture argument"));
  if(obj->GetIndexedPropertiesExternalArrayDataType()>0) {
    cout<<"pixels as TypedArray, type="<<obj->GetIndexedPropertiesExternalArrayDataType()<<endl;
    pixels = obj->GetIndexedPropertiesExternalArrayData();
  }
  else {
    cout<<"Pixels as Image data"<<endl;
    Image *image = ObjectWrap::Unwrap<Image>(arg->ToObject());
    pixels=image->GetData();
  }

  return pixels;
}
namespace webgl {

JS_METHOD(Uniform1f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();

  glUniform1f(location, x);
  return Undefined();
}

JS_METHOD(Uniform2f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();

  glUniform2f(location, x, y);
  return Undefined();
}

JS_METHOD(Uniform3f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();
  double z = args[3]->NumberValue();

  glUniform3f(location, x, y, z);
  return Undefined();
}

JS_METHOD(Uniform4f) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  double x = args[1]->NumberValue();
  double y = args[2]->NumberValue();
  double z = args[3]->NumberValue();
  double w = args[4]->NumberValue();

  glUniform4f(location, x, y, z, w);
  return Undefined();
}

JS_METHOD(Uniform1i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();

  glUniform1i(location, x);
  return Undefined();
}

JS_METHOD(Uniform2i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();

  glUniform2i(location, x, y);
  return Undefined();
}

JS_METHOD(Uniform3i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();

  glUniform3i(location, x, y, z);
  return Undefined();
}

JS_METHOD(Uniform4i) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  int x = args[1]->Int32Value();
  int y = args[2]->Int32Value();
  int z = args[3]->Int32Value();
  int w = args[4]->Int32Value();

  glUniform4i(location, x, y, z, w);
  return Undefined();
}

JS_METHOD(Uniform1fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length();

  glUniform1fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform2fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/2;

  glUniform2fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform3fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/3;

  glUniform3fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform4fv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/4;

  glUniform4fv(location, num, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform1iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length();

  glUniform1iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform2iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/2;

  glUniform2iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform3iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/3;

  glUniform3iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(Uniform4iv) {
  HandleScope scope;

  int location = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);
  int num=arr->Length()/4;

  glUniform4iv(location, num, (int*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(PixelStorei) {
  HandleScope scope;

  int pname = args[0]->Int32Value();
  int param = args[1]->Int32Value();

  glPixelStorei(pname,param);

  return Undefined();
}

JS_METHOD(BindAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int index = args[1]->Int32Value();
  String::Utf8Value name(args[2]);

  glBindAttribLocation(program, index, *name);

  return Undefined();
}


JS_METHOD(GetError) {
  HandleScope scope;

  return Number::New(glGetError());
}


JS_METHOD(DrawArrays) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int first = args[1]->Int32Value();
  int count = args[2]->Int32Value();

  glDrawArrays(mode, first, count);

  return Undefined();
}

JS_METHOD(UniformMatrix2fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  Local<Object> value = Local<Object>::Cast(args[2]);


  GLsizei count = value->GetIndexedPropertiesExternalArrayDataLength();

  if (count < 4) {
    return ThrowException(Exception::TypeError(String::New("Not enough data for UniformMatrix4fv")));
  }

  const GLfloat* data = (const GLfloat*)value->GetIndexedPropertiesExternalArrayData();

  //    printf("count=%d\n", count);
  //    printf("[%f, %f, %f, %f,\n", data[0], data[1], data[2], data[3]);
  //    printf(" %f, %f, %f, %f,\n", data[4], data[5], data[6], data[7]);
  //    printf(" %f, %f, %f, %f,\n", data[8], data[9], data[10], data[11]);
  //    printf(" %f, %f, %f, %f]\n", data[12], data[13], data[14], data[15]);


  glUniformMatrix4fv(location, count / 4, transpose, data);

  return Undefined();
}

JS_METHOD(UniformMatrix3fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  Local<Object> value = Local<Object>::Cast(args[2]);


  GLsizei count = value->GetIndexedPropertiesExternalArrayDataLength();

  if (count < 9) {
    return ThrowException(Exception::TypeError(String::New("Not enough data for UniformMatrix4fv")));
  }

  const GLfloat* data = (const GLfloat*)value->GetIndexedPropertiesExternalArrayData();

  //    printf("count=%d\n", count);
  //    printf("[%f, %f, %f, %f,\n", data[0], data[1], data[2], data[3]);
  //    printf(" %f, %f, %f, %f,\n", data[4], data[5], data[6], data[7]);
  //    printf(" %f, %f, %f, %f,\n", data[8], data[9], data[10], data[11]);
  //    printf(" %f, %f, %f, %f]\n", data[12], data[13], data[14], data[15]);


  glUniformMatrix4fv(location, count / 9, transpose, data);

  return Undefined();
}

JS_METHOD(UniformMatrix4fv) {
  HandleScope scope;

  GLint location = args[0]->Int32Value();
  GLboolean transpose = args[1]->BooleanValue();
  Local<Object> value = Local<Object>::Cast(args[2]);


  GLsizei count = value->GetIndexedPropertiesExternalArrayDataLength();

  if (count < 16) {
    return ThrowException(Exception::TypeError(String::New("Not enough data for UniformMatrix4fv")));
  }

  const GLfloat* data = (const GLfloat*)value->GetIndexedPropertiesExternalArrayData();

  //    printf("count=%d\n", count);
  //    printf("[%f, %f, %f, %f,\n", data[0], data[1], data[2], data[3]);
  //    printf(" %f, %f, %f, %f,\n", data[4], data[5], data[6], data[7]);
  //    printf(" %f, %f, %f, %f,\n", data[8], data[9], data[10], data[11]);
  //    printf(" %f, %f, %f, %f]\n", data[12], data[13], data[14], data[15]);


  glUniformMatrix4fv(location, count / 16, transpose, data);

  return Undefined();
}

JS_METHOD(GenerateMipmap) {
  HandleScope scope;

  GLint target = args[0]->Int32Value();
  glGenerateMipmap(target);

  return Undefined();
}

JS_METHOD(GetAttribLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::Utf8Value name(args[1]);

  return Number::New(glGetAttribLocation(program, *name));
}


JS_METHOD(DepthFunc) {
  HandleScope scope;

  glDepthFunc(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(Viewport) {
  HandleScope scope;

  int x = args[0]->Int32Value();
  int y = args[1]->Int32Value();
  int width = args[2]->Int32Value();
  int height = args[3]->Int32Value();

  glViewport(x, y, width, height);

  return Undefined();

  return Number::New(glCreateShader(args[0]->Int32Value()));
}

JS_METHOD(CreateShader) {
  HandleScope scope;

  return Number::New(glCreateShader(args[0]->Int32Value()));
}


JS_METHOD(ShaderSource) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  String::Utf8Value code(args[1]);

  const char* codes[1];
  codes[0] = *code;

  glShaderSource  (id, 1, codes, NULL);

  return Undefined();
}


JS_METHOD(CompileShader) {
  HandleScope scope;


  glCompileShader(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(GetShaderParameter) {
  HandleScope scope;

  int shader = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_COMPILE_STATUS:
    glGetShaderiv(shader, pname, &value);
    return Boolean::New(static_cast<bool>(value));
  case GL_SHADER_TYPE:
    glGetShaderiv(shader, pname, &value);
    return Number::New(static_cast<unsigned long>(value));
  case GL_INFO_LOG_LENGTH:
  case GL_SHADER_SOURCE_LENGTH:
    glGetShaderiv(shader, pname, &value);
    return Number::New(static_cast<long>(value));
  default:
    return ThrowException(Exception::TypeError(String::New("GetShaderParameter: Invalid Enum")));
  }
}

JS_METHOD(GetShaderInfoLog) {
  HandleScope scope;

  int id = args[0]->Int32Value();
  int Len = 1024;
  char Error[1024];
  glGetShaderInfoLog(id, 1024, &Len, Error);

  return String::New(Error);
}


JS_METHOD(CreateProgram) {
  HandleScope scope;

  return Number::New(glCreateProgram());
}


JS_METHOD(AttachShader) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int shader = args[1]->Int32Value();

  glAttachShader(program, shader);

  return Undefined();
}


JS_METHOD(LinkProgram) {
  HandleScope scope;

  glLinkProgram(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(GetProgramParameter) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  int pname = args[1]->Int32Value();

  int value = 0;
  switch (pname) {
  case GL_DELETE_STATUS:
  case GL_LINK_STATUS:
  case GL_VALIDATE_STATUS:
    glGetProgramiv(program, pname, &value);
    return Boolean::New(static_cast<bool>(value));
  case GL_ATTACHED_SHADERS:
  case GL_ACTIVE_ATTRIBUTES:
  case GL_ACTIVE_UNIFORMS:
    glGetProgramiv(program, pname, &value);
    return Number::New(static_cast<long>(value));
  default:
    return ThrowException(Exception::TypeError(String::New("GetProgramParameter: Invalid Enum")));
  }
}


JS_METHOD(GetUniformLocation) {
  HandleScope scope;

  int program = args[0]->Int32Value();
  String::Utf8Value name(args[1]);

  return Number::New(glGetUniformLocation(program, *name));
}


JS_METHOD(ClearColor) {
  HandleScope scope;

  double red = args[0]->NumberValue();
  double green = args[1]->NumberValue();
  double blue = args[2]->NumberValue();
  double alpha = args[3]->NumberValue();

  glClearColor(red, green, blue, alpha);

  return Undefined();
}


JS_METHOD(ClearDepth) {
  HandleScope scope;

  double depth = args[0]->NumberValue();

  glClearDepthf(depth);

  return Undefined();
}

JS_METHOD(Disable) {
  HandleScope scope;

  glDisable(args[0]->Int32Value());
  return Undefined();
}

JS_METHOD(Enable) {
  HandleScope scope;

  glEnable(args[0]->Int32Value());
  return Undefined();
}


JS_METHOD(CreateTexture) {
  HandleScope scope;

  GLuint texture;
  glGenTextures(1, &texture);
  return Number::New(texture);
}


JS_METHOD(BindTexture) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int texture = args[1]->Int32Value();

  glBindTexture(target, texture);
  return Undefined();
}


JS_METHOD(TexImage2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int level = args[1]->Int32Value();
  int internalformat = args[2]->Int32Value();
  int width = args[3]->Int32Value();
  int height = args[4]->Int32Value();
  int border = args[5]->Int32Value();
  int format = args[6]->Int32Value();
  int type = args[7]->Int32Value();
  void *pixels=getImageData(args[8]);

  if(pixels)
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);

  return Undefined();
}


JS_METHOD(TexParameteri) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  int param = args[2]->Int32Value();

  glTexParameteri(target, pname, param);

  return Undefined();
}

JS_METHOD(TexParameterf) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int pname = args[1]->Int32Value();
  float param = args[2]->NumberValue();

  glTexParameterf(target, pname, param);

  return Undefined();
}


JS_METHOD(Clear) {
  HandleScope scope;

  glClear(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(UseProgram) {
  HandleScope scope;

  glUseProgram(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(CreateBuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenBuffers(1, &buffer);
  return Number::New(buffer);
}


JS_METHOD(BindBuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->Int32Value();

  glBindBuffer(target, buffer);

  return Undefined();
}


JS_METHOD(CreateFramebuffer) {
  HandleScope scope;

  GLuint buffer;
  glGenFramebuffers(1, &buffer);
  return Number::New(buffer);
}


JS_METHOD(BindFramebuffer) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int buffer = args[1]->Int32Value();

  glBindFramebuffer(target, buffer);

  return Undefined();
}


JS_METHOD(FramebufferTexture2D) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int attachment = args[1]->Int32Value();
  int textarget = args[2]->Int32Value();
  int texture = args[3]->Int32Value();
  int level = args[4]->Int32Value();

  glFramebufferTexture2D(target, attachment, textarget, texture, level);

  return Undefined();
}


JS_METHOD(BufferData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(args[1]);
  int usage = args[2]->Int32Value();

  int element_size = SizeOfArrayElementForType(obj->GetIndexedPropertiesExternalArrayDataType());
  int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
  void* data = obj->GetIndexedPropertiesExternalArrayData();


  //    printf("BufferData %d %d %d\n", target, size, usage);
  glBufferData(target, size, data, usage);

  return Undefined();
}


JS_METHOD(BufferSubData) {
  HandleScope scope;

  int target = args[0]->Int32Value();
  int offset = args[1]->Int32Value();
  Local<Object> obj = Local<Object>::Cast(args[2]);

  int element_size = SizeOfArrayElementForType( obj->GetIndexedPropertiesExternalArrayDataType());
  int size = obj->GetIndexedPropertiesExternalArrayDataLength() * element_size;
  void* data = obj->GetIndexedPropertiesExternalArrayData();

  glBufferSubData(target, offset, size, data);

  return Undefined();
}


JS_METHOD(BlendEquation) {
  HandleScope scope;

  int mode=args[0]->Int32Value();;

  glBlendEquation(mode);

  return Undefined();
}


JS_METHOD(BlendFunc) {
  HandleScope scope;

  int sfactor=args[0]->Int32Value();;
  int dfactor=args[1]->Int32Value();;

  glBlendFunc(sfactor,dfactor);

  return Undefined();
}


JS_METHOD(EnableVertexAttribArray) {
  HandleScope scope;

  glEnableVertexAttribArray(args[0]->Int32Value());

  return Undefined();
}


JS_METHOD(VertexAttribPointer) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  int size = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  int normalized = args[3]->BooleanValue();
  int stride = args[4]->Int32Value();
  int offset = args[5]->Int32Value();

  //    printf("VertexAttribPointer %d %d %d %d %d %d\n", indx, size, type, normalized, stride, offset);
  glVertexAttribPointer(indx, size, type, normalized, stride, (const GLvoid *)offset);

  return Undefined();
}


JS_METHOD(ActiveTexture) {
  HandleScope scope;

  glActiveTexture(args[0]->Int32Value());
  return Undefined();
}


JS_METHOD(DrawElements) {
  HandleScope scope;

  int mode = args[0]->Int32Value();
  int count = args[1]->Int32Value();
  int type = args[2]->Int32Value();
  int offset = args[3]->Int32Value();
  glDrawElements(mode, count, type, (const GLvoid*)offset);
  return Undefined();
}


JS_METHOD(Flush) {
  HandleScope scope;
  glFlush();
  return Undefined();
}

JS_METHOD(vertexAttrib1f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();

  glVertexAttrib1f(indx, x);
  return Undefined();
}

JS_METHOD(vertexAttrib2f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();

  glVertexAttrib2f(indx, x, y);
  return Undefined();
}

JS_METHOD(vertexAttrib3f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();
  GLfloat z = args[3]->NumberValue();

  glVertexAttrib3f(indx, x, y, z);
  return Undefined();
}

JS_METHOD(vertexAttrib4f) {
  HandleScope scope;

  GLuint indx = args[0]->Int32Value();
  GLfloat x = args[1]->NumberValue();
  GLfloat y = args[2]->NumberValue();
  GLfloat z = args[3]->NumberValue();
  GLfloat w = args[4]->NumberValue();

  glVertexAttrib4f(indx, x, y, z, w);
  return Undefined();
}

JS_METHOD(vertexAttrib1fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);

  glVertexAttrib1fv(indx, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(vertexAttrib2fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);

  glVertexAttrib2fv(indx, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(vertexAttrib3fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);

  glVertexAttrib3fv(indx, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}

JS_METHOD(vertexAttrib4fv) {
  HandleScope scope;

  int indx = args[0]->Int32Value();
  Local<Array> arr = Array::Cast(*args[1]);

  glVertexAttrib4fv(indx, (float*) arr->GetIndexedPropertiesExternalArrayData());
  return Undefined();
}


} // end namespace webgl
