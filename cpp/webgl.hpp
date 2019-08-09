#ifndef _WEBGL_HPP_
#define _WEBGL_HPP_


#include <addon-tools.hpp>

#include <GL/glew.h>


#define USE_UINT32_ARG(I, VAR, DEF)                                           \
	CHECK_LET_ARG(I, IsUint32(), "uint32");                                   \
	unsigned int VAR = IS_ARG_EMPTY(I) ? (DEF) : info[I].As<v8::Uint32>()->Value();

#ifdef _WIN32
	#define	strcasestr(s, t) strstr(strupr(s), strupr(t))
#endif


namespace webgl {
	
	// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
	inline GLuint ToGLuint(const void* ptr) {
		return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
	}
	
	NAN_METHOD(init);
	
	
	// Attrib
	
	NAN_METHOD(bindAttribLocation);
	NAN_METHOD(disableVertexAttribArray);
	NAN_METHOD(enableVertexAttribArray);
	NAN_METHOD(getActiveAttrib);
	NAN_METHOD(getAttribLocation);
	NAN_METHOD(getVertexAttrib);
	NAN_METHOD(getVertexAttribOffset);
	NAN_METHOD(vertexAttrib1f);
	NAN_METHOD(vertexAttrib1fv);
	NAN_METHOD(vertexAttrib2f);
	NAN_METHOD(vertexAttrib2fv);
	NAN_METHOD(vertexAttrib3f);
	NAN_METHOD(vertexAttrib3fv);
	NAN_METHOD(vertexAttrib4f);
	NAN_METHOD(vertexAttrib4fv);
	NAN_METHOD(vertexAttribPointer);
	NAN_METHOD(vertexAttribIPointer);
	
	
	// Blend
	
	NAN_METHOD(blendColor);
	NAN_METHOD(blendEquation);
	NAN_METHOD(blendEquationSeparate);
	NAN_METHOD(blendFunc);
	NAN_METHOD(blendFuncSeparate);
	
	
	// VBO
	
	NAN_METHOD(createBuffer);
	NAN_METHOD(deleteBuffer);
	NAN_METHOD(isBuffer);
	NAN_METHOD(bindBuffer);
	NAN_METHOD(bindBufferBase);
	NAN_METHOD(bindBufferRange);
	NAN_METHOD(bufferData);
	NAN_METHOD(bufferSubData);
	NAN_METHOD(copyBufferSubData);
	NAN_METHOD(getBufferSubData);
	NAN_METHOD(getBufferParameter);
	
	
	// FBO
	
	NAN_METHOD(createFramebuffer);
	NAN_METHOD(deleteFramebuffer);
	NAN_METHOD(isFramebuffer);
	NAN_METHOD(bindFramebuffer);
	NAN_METHOD(bindFrameBuffer);
	NAN_METHOD(blitFrameBuffer);
	NAN_METHOD(checkFramebufferStatus);
	NAN_METHOD(framebufferRenderbuffer);
	NAN_METHOD(framebufferTexture2D);
	NAN_METHOD(getFramebufferAttachmentParameter);
	
	
	// Program
	
	NAN_METHOD(createProgram);
	NAN_METHOD(deleteProgram);
	NAN_METHOD(isProgram);
	NAN_METHOD(getProgramInfoLog);
	NAN_METHOD(getProgramParameter);
	NAN_METHOD(linkProgram);
	NAN_METHOD(useProgram);
	NAN_METHOD(validateProgram);
	
	
	// RBO
	
	NAN_METHOD(createRenderbuffer);
	NAN_METHOD(deleteRenderbuffer);
	NAN_METHOD(isRenderbuffer);
	NAN_METHOD(bindRenderbuffer);
	NAN_METHOD(getRenderbufferParameter);
	NAN_METHOD(renderbufferStorage);
	
	
	// Shader
	
	
	NAN_METHOD(deleteShader);
	NAN_METHOD(createShader);
	NAN_METHOD(isShader);
	NAN_METHOD(attachShader);
	NAN_METHOD(compileShader);
	NAN_METHOD(detachShader);
	NAN_METHOD(getAttachedShaders);
	NAN_METHOD(getShaderInfoLog);
	NAN_METHOD(getShaderParameter);
	NAN_METHOD(getShaderSource);
	NAN_METHOD(shaderSource);
	
	
	// Stencil
	
	NAN_METHOD(clearStencil);
	NAN_METHOD(stencilFunc);
	NAN_METHOD(stencilFuncSeparate);
	NAN_METHOD(stencilMask);
	NAN_METHOD(stencilMaskSeparate);
	NAN_METHOD(stencilOp);
	NAN_METHOD(stencilOpSeparate);
	
	
	// Texture
	
	NAN_METHOD(createTexture);
	NAN_METHOD(deleteTexture);
	NAN_METHOD(isTexture);
	NAN_METHOD(bindTexture);
	NAN_METHOD(activeTexture);
	NAN_METHOD(copyTexImage2D);
	NAN_METHOD(copyTexSubImage2D);
	NAN_METHOD(generateMipmap);
	NAN_METHOD(getTexParameter);
	NAN_METHOD(texImage2D);
	NAN_METHOD(texParameterf);
	NAN_METHOD(texParameteri);
	NAN_METHOD(texSubImage2D);
	
	
	// Uniform
	
	NAN_METHOD(getActiveUniform);
	NAN_METHOD(getUniform);
	NAN_METHOD(getUniformLocation);
	NAN_METHOD(uniform1f);
	NAN_METHOD(uniform1fv);
	NAN_METHOD(uniform1i);
	NAN_METHOD(uniform1iv);
	NAN_METHOD(uniform2f);
	NAN_METHOD(uniform2fv);
	NAN_METHOD(uniform2i);
	NAN_METHOD(uniform2iv);
	NAN_METHOD(uniform3f);
	NAN_METHOD(uniform3fv);
	NAN_METHOD(uniform3i);
	NAN_METHOD(uniform3iv);
	NAN_METHOD(uniform4f);
	NAN_METHOD(uniform4fv);
	NAN_METHOD(uniform4i);
	NAN_METHOD(uniform4iv);
	NAN_METHOD(uniformMatrix2fv);
	NAN_METHOD(uniformMatrix3fv);
	NAN_METHOD(uniformMatrix4fv);
	
	
	// VAO
	
	NAN_METHOD(createVertexArray);
	NAN_METHOD(deleteVertexArray);
	NAN_METHOD(isVertexArray);
	NAN_METHOD(bindVertexArray);
	
	
	// Instances
	
	NAN_METHOD(drawArraysInstanced);
	NAN_METHOD(drawElementsInstanced);
	NAN_METHOD(vertexAttribDivisor);
	

	// Transform feedback
	NAN_METHOD(createTransformFeedback);
	NAN_METHOD(deleteTransformFeedback);
	NAN_METHOD(isTransformFeedback);
	NAN_METHOD(bindTransformFeedback);
	NAN_METHOD(beginTransformFeedback);
	NAN_METHOD(endTransformFeedback);
	NAN_METHOD(pauseTransformFeedback);
	NAN_METHOD(resumeTransformFeedback);
	NAN_METHOD(transformFeedbackVaryings);
	NAN_METHOD(getTransformFeedbackVarying);
	
	// Misc OpenGL Functions
	
	NAN_METHOD(clear);
	NAN_METHOD(clearColor);
	NAN_METHOD(clearDepth);
	NAN_METHOD(colorMask);
	NAN_METHOD(cullFace);
	NAN_METHOD(depthFunc);
	NAN_METHOD(depthMask);
	NAN_METHOD(depthRange);
	NAN_METHOD(disable);
	NAN_METHOD(drawArrays);
	NAN_METHOD(drawElements);
	NAN_METHOD(enable);
	NAN_METHOD(finish);
	NAN_METHOD(flush);
	NAN_METHOD(frontFace);
	NAN_METHOD(getError);
	NAN_METHOD(getParameter);
	NAN_METHOD(getRenderTarget);
	NAN_METHOD(getSupportedExtensions);
	NAN_METHOD(hint);
	NAN_METHOD(isEnabled);
	NAN_METHOD(lineWidth);
	NAN_METHOD(pixelStorei);
	NAN_METHOD(polygonOffset);
	NAN_METHOD(readPixels);
	NAN_METHOD(sampleCoverage);
	NAN_METHOD(scissor);
	NAN_METHOD(viewport);
	
} // namespace webgl

#endif /* _WEBGL_HPP_ */
