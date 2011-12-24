/*
 * webgl.h
 *
 *  Created on: Dec 13, 2011
 *      Author: ngk437
 */

#ifndef WEBGL_H_
#define WEBGL_H_

#include "common.h"

using namespace v8;

namespace webgl {

JS_METHOD(Uniform1f);
JS_METHOD(Uniform2f);
JS_METHOD(Uniform3f);
JS_METHOD(Uniform4f);
JS_METHOD(Uniform1i);
JS_METHOD(Uniform2i);
JS_METHOD(Uniform3i);
JS_METHOD(Uniform4i);
JS_METHOD(Uniform1fv);
JS_METHOD(Uniform2fv);
JS_METHOD(Uniform3fv);
JS_METHOD(Uniform4fv);
JS_METHOD(Uniform1iv);
JS_METHOD(Uniform2iv);
JS_METHOD(Uniform3iv);
JS_METHOD(Uniform4iv);
JS_METHOD(PixelStorei);
JS_METHOD(BindAttribLocation);
JS_METHOD(GetError);
JS_METHOD(DrawArrays);
JS_METHOD(UniformMatrix2fv);
JS_METHOD(UniformMatrix3fv);
JS_METHOD(UniformMatrix4fv);
JS_METHOD(GenerateMipmap);
JS_METHOD(GetAttribLocation);
JS_METHOD(DepthFunc);
JS_METHOD(Viewport);
JS_METHOD(CreateShader);
JS_METHOD(ShaderSource);
JS_METHOD(CompileShader);
JS_METHOD(GetShaderParameter);
JS_METHOD(GetShaderInfoLog);
JS_METHOD(CreateProgram);
JS_METHOD(AttachShader);
JS_METHOD(LinkProgram);
JS_METHOD(GetProgramParameter);
JS_METHOD(GetUniformLocation);
JS_METHOD(ClearColor);
JS_METHOD(ClearDepth);
JS_METHOD(Disable);
JS_METHOD(Enable);
JS_METHOD(CreateTexture);
JS_METHOD(BindTexture);
JS_METHOD(TexImage2D);
JS_METHOD(TexParameteri);
JS_METHOD(TexParameterf);
JS_METHOD(Clear);
JS_METHOD(UseProgram);
JS_METHOD(CreateBuffer);
JS_METHOD(BindBuffer);
JS_METHOD(CreateFramebuffer);
JS_METHOD(BindFramebuffer);
JS_METHOD(FramebufferTexture2D);
JS_METHOD(BufferData);
JS_METHOD(BufferSubData);
JS_METHOD(BlendEquation);
JS_METHOD(BlendFunc);
JS_METHOD(EnableVertexAttribArray);
JS_METHOD(VertexAttribPointer);
JS_METHOD(ActiveTexture);
JS_METHOD(DrawElements);
JS_METHOD(Flush);

JS_METHOD(vertexAttrib1f);
JS_METHOD(vertexAttrib2f);
JS_METHOD(vertexAttrib3f);
JS_METHOD(vertexAttrib4f);
JS_METHOD(vertexAttrib1fv);
JS_METHOD(vertexAttrib2fv);
JS_METHOD(vertexAttrib3fv);
JS_METHOD(vertexAttrib4fv);

}

#endif /* WEBGL_H_ */
