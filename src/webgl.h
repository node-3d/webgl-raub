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

Handle<Value> Uniform1f(const Arguments& args);
Handle<Value> Uniform2f(const Arguments& args);
Handle<Value> Uniform3f(const Arguments& args);
Handle<Value> Uniform4f(const Arguments& args);
Handle<Value> Uniform1i(const Arguments& args);
Handle<Value> Uniform2i(const Arguments& args);
Handle<Value> Uniform3i(const Arguments& args);
Handle<Value> Uniform4i(const Arguments& args);
Handle<Value> Uniform1fv(const Arguments& args);
Handle<Value> Uniform2fv(const Arguments& args);
Handle<Value> Uniform3fv(const Arguments& args);
Handle<Value> Uniform4fv(const Arguments& args);
Handle<Value> Uniform1iv(const Arguments& args);
Handle<Value> Uniform2iv(const Arguments& args);
Handle<Value> Uniform3iv(const Arguments& args);
Handle<Value> Uniform4iv(const Arguments& args);
Handle<Value> PixelStorei(const Arguments& args);
Handle<Value> BindAttribLocation(const Arguments& args);
Handle<Value> GetError(const Arguments& args);
Handle<Value> DrawArrays(const Arguments& args);
Handle<Value> UniformMatrix2fv(const Arguments& args);
Handle<Value> UniformMatrix3fv(const Arguments& args);
Handle<Value> UniformMatrix4fv(const Arguments& args);
Handle<Value> GenerateMipmap(const Arguments& args);
Handle<Value> GetAttribLocation(const Arguments& args);
Handle<Value> DepthFunc(const Arguments& args);
Handle<Value> Viewport(const Arguments& args);
Handle<Value> CreateShader(const Arguments& args);
Handle<Value> ShaderSource(const Arguments& args);
Handle<Value> CompileShader(const Arguments& args);
Handle<Value> GetShaderParameter(const Arguments& args);
Handle<Value> GetShaderInfoLog(const Arguments& args);
Handle<Value> CreateProgram(const Arguments& args);
Handle<Value> AttachShader(const Arguments& args);
Handle<Value> LinkProgram(const Arguments& args);
Handle<Value> GetProgramParameter(const Arguments& args);
Handle<Value> GetUniformLocation(const Arguments& args);
Handle<Value> ClearColor(const Arguments& args);
Handle<Value> ClearDepth(const Arguments& args);
Handle<Value> Disable(const Arguments& args);
Handle<Value> Enable(const Arguments& args);
Handle<Value> CreateTexture(const Arguments& args);
Handle<Value> BindTexture(const Arguments& args);
Handle<Value> TexImage2D(const Arguments& args);
Handle<Value> TexParameteri(const Arguments& args);
Handle<Value> TexParameterf(const Arguments& args);
Handle<Value> Clear(const Arguments& args);
Handle<Value> UseProgram(const Arguments& args);
Handle<Value> CreateBuffer(const Arguments& args);
Handle<Value> BindBuffer(const Arguments& args);
Handle<Value> CreateFramebuffer(const Arguments& args);
Handle<Value> BindFramebuffer(const Arguments& args);
Handle<Value> FramebufferTexture2D(const Arguments& args);
Handle<Value> BufferData(const Arguments& args);
Handle<Value> BufferSubData(const Arguments& args);
Handle<Value> BlendEquation(const Arguments& args);
Handle<Value> BlendFunc(const Arguments& args);
Handle<Value> EnableVertexAttribArray(const Arguments& args);
Handle<Value> VertexAttribPointer(const Arguments& args);
Handle<Value> ActiveTexture(const Arguments& args);
Handle<Value> DrawElements(const Arguments& args);
Handle<Value> Flush(const Arguments& args);

}

#endif /* WEBGL_H_ */
