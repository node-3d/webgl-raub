#ifndef _WEBGL_HPP_
#define _WEBGL_HPP_


#include <addon-tools.hpp>

#include <GL/glew.h>


namespace webgl {
	
	// A 32-bit and 64-bit compatible way of converting a pointer to a GLuint.
	inline GLuint ToGLuint(const void* ptr) {
		return static_cast<GLuint>(reinterpret_cast<size_t>(ptr));
	}
	
	JS_METHOD(init);
	
	
	// Attrib
	
	JS_METHOD(bindAttribLocation);
	JS_METHOD(disableVertexAttribArray);
	JS_METHOD(enableVertexAttribArray);
	JS_METHOD(getActiveAttrib);
	JS_METHOD(getAttribLocation);
	JS_METHOD(getVertexAttrib);
	JS_METHOD(getVertexAttribOffset);
	JS_METHOD(vertexAttrib1f);
	JS_METHOD(vertexAttrib1fv);
	JS_METHOD(vertexAttrib2f);
	JS_METHOD(vertexAttrib2fv);
	JS_METHOD(vertexAttrib3f);
	JS_METHOD(vertexAttrib3fv);
	JS_METHOD(vertexAttrib4f);
	JS_METHOD(vertexAttrib4fv);
	JS_METHOD(vertexAttribPointer);
	JS_METHOD(vertexAttribIPointer);
	
	
	// Blend
	
	JS_METHOD(blendColor);
	JS_METHOD(blendEquation);
	JS_METHOD(blendEquationSeparate);
	JS_METHOD(blendFunc);
	JS_METHOD(blendFuncSeparate);
	
	
	// VBO
	
	JS_METHOD(createBuffer);
	JS_METHOD(deleteBuffer);
	JS_METHOD(isBuffer);
	JS_METHOD(bindBuffer);
	JS_METHOD(bindBufferBase);
	JS_METHOD(bindBufferRange);
	JS_METHOD(bufferData);
	JS_METHOD(bufferSubData);
	JS_METHOD(copyBufferSubData);
	JS_METHOD(getBufferSubData);
	JS_METHOD(getBufferParameter);
	
	
	// FBO
	
	JS_METHOD(createFramebuffer);
	JS_METHOD(deleteFramebuffer);
	JS_METHOD(isFramebuffer);
	JS_METHOD(bindFramebuffer);
	JS_METHOD(bindFrameBuffer);
	JS_METHOD(blitFrameBuffer);
	JS_METHOD(checkFramebufferStatus);
	JS_METHOD(framebufferRenderbuffer);
	JS_METHOD(framebufferTexture2D);
	JS_METHOD(getFramebufferAttachmentParameter);
	
	
	// Program
	
	JS_METHOD(createProgram);
	JS_METHOD(deleteProgram);
	JS_METHOD(isProgram);
	JS_METHOD(getProgramInfoLog);
	JS_METHOD(getProgramParameter);
	JS_METHOD(linkProgram);
	JS_METHOD(useProgram);
	JS_METHOD(validateProgram);
	
	
	// RBO
	
	JS_METHOD(createRenderbuffer);
	JS_METHOD(deleteRenderbuffer);
	JS_METHOD(isRenderbuffer);
	JS_METHOD(bindRenderbuffer);
	JS_METHOD(getRenderbufferParameter);
	JS_METHOD(renderbufferStorage);
	
	
	// Shader
	
	
	JS_METHOD(deleteShader);
	JS_METHOD(createShader);
	JS_METHOD(isShader);
	JS_METHOD(attachShader);
	JS_METHOD(compileShader);
	JS_METHOD(detachShader);
	JS_METHOD(getAttachedShaders);
	JS_METHOD(getShaderInfoLog);
	JS_METHOD(getShaderParameter);
	JS_METHOD(getShaderSource);
	JS_METHOD(shaderSource);
	
	
	// Stencil
	
	JS_METHOD(clearStencil);
	JS_METHOD(stencilFunc);
	JS_METHOD(stencilFuncSeparate);
	JS_METHOD(stencilMask);
	JS_METHOD(stencilMaskSeparate);
	JS_METHOD(stencilOp);
	JS_METHOD(stencilOpSeparate);
	
	
	// Texture
	
	JS_METHOD(createTexture);
	JS_METHOD(deleteTexture);
	JS_METHOD(isTexture);
	JS_METHOD(bindTexture);
	JS_METHOD(activeTexture);
	JS_METHOD(copyTexImage2D);
	JS_METHOD(copyTexSubImage2D);
	JS_METHOD(generateMipmap);
	JS_METHOD(getTexParameter);
	JS_METHOD(texImage2D);
	JS_METHOD(texParameterf);
	JS_METHOD(texParameteri);
	JS_METHOD(texSubImage2D);
	
	
	// Uniform
	
	JS_METHOD(getActiveUniform);
	JS_METHOD(getUniform);
	JS_METHOD(getUniformLocation);
	JS_METHOD(uniform1f);
	JS_METHOD(uniform1fv);
	JS_METHOD(uniform1i);
	JS_METHOD(uniform1iv);
	JS_METHOD(uniform2f);
	JS_METHOD(uniform2fv);
	JS_METHOD(uniform2i);
	JS_METHOD(uniform2iv);
	JS_METHOD(uniform3f);
	JS_METHOD(uniform3fv);
	JS_METHOD(uniform3i);
	JS_METHOD(uniform3iv);
	JS_METHOD(uniform4f);
	JS_METHOD(uniform4fv);
	JS_METHOD(uniform4i);
	JS_METHOD(uniform4iv);
	JS_METHOD(uniformMatrix2fv);
	JS_METHOD(uniformMatrix3fv);
	JS_METHOD(uniformMatrix4fv);
	
	
	// VAO
	
	JS_METHOD(createVertexArray);
	JS_METHOD(deleteVertexArray);
	JS_METHOD(isVertexArray);
	JS_METHOD(bindVertexArray);
	
	
	// Instances
	
	JS_METHOD(drawArraysInstanced);
	JS_METHOD(drawElementsInstanced);
	JS_METHOD(vertexAttribDivisor);
	

	// Transform feedback
	JS_METHOD(createTransformFeedback);
	JS_METHOD(deleteTransformFeedback);
	JS_METHOD(isTransformFeedback);
	JS_METHOD(bindTransformFeedback);
	JS_METHOD(beginTransformFeedback);
	JS_METHOD(endTransformFeedback);
	JS_METHOD(pauseTransformFeedback);
	JS_METHOD(resumeTransformFeedback);
	JS_METHOD(transformFeedbackVaryings);
	JS_METHOD(getTransformFeedbackVarying);
	
	// Misc OpenGL Functions
	
	JS_METHOD(clear);
	JS_METHOD(clearColor);
	JS_METHOD(clearDepth);
	JS_METHOD(colorMask);
	JS_METHOD(cullFace);
	JS_METHOD(depthFunc);
	JS_METHOD(depthMask);
	JS_METHOD(depthRange);
	JS_METHOD(disable);
	JS_METHOD(drawArrays);
	JS_METHOD(drawElements);
	JS_METHOD(enable);
	JS_METHOD(finish);
	JS_METHOD(flush);
	JS_METHOD(frontFace);
	JS_METHOD(getError);
	JS_METHOD(getParameter);
	JS_METHOD(getRenderTarget);
	JS_METHOD(getSupportedExtensions);
	JS_METHOD(hint);
	JS_METHOD(isEnabled);
	JS_METHOD(lineWidth);
	JS_METHOD(pixelStorei);
	JS_METHOD(polygonOffset);
	JS_METHOD(readPixels);
	JS_METHOD(sampleCoverage);
	JS_METHOD(scissor);
	JS_METHOD(viewport);
	
} // namespace webgl

#endif /* _WEBGL_HPP_ */
