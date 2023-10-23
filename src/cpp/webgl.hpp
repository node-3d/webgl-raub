#ifndef _WEBGL_HPP_
#define _WEBGL_HPP_


#include <addon-tools.hpp>

#include <GL/glew.h>


namespace webgl {
	DBG_EXPORT JS_METHOD(init);
	
	// Attrib
	DBG_EXPORT JS_METHOD(bindAttribLocation);
	DBG_EXPORT JS_METHOD(disableVertexAttribArray);
	DBG_EXPORT JS_METHOD(enableVertexAttribArray);
	DBG_EXPORT JS_METHOD(getActiveAttrib);
	DBG_EXPORT JS_METHOD(getAttribLocation);
	DBG_EXPORT JS_METHOD(getVertexAttrib);
	DBG_EXPORT JS_METHOD(getVertexAttribOffset);
	DBG_EXPORT JS_METHOD(vertexAttrib1f);
	DBG_EXPORT JS_METHOD(vertexAttrib1fv);
	DBG_EXPORT JS_METHOD(vertexAttrib2f);
	DBG_EXPORT JS_METHOD(vertexAttrib2fv);
	DBG_EXPORT JS_METHOD(vertexAttrib3f);
	DBG_EXPORT JS_METHOD(vertexAttrib3fv);
	DBG_EXPORT JS_METHOD(vertexAttrib4f);
	DBG_EXPORT JS_METHOD(vertexAttrib4fv);
	DBG_EXPORT JS_METHOD(vertexAttribPointer);
	DBG_EXPORT JS_METHOD(vertexAttribIPointer);
	DBG_EXPORT JS_METHOD(vertexAttribI4i);
	DBG_EXPORT JS_METHOD(vertexAttribI4iv);
	DBG_EXPORT JS_METHOD(vertexAttribI4ui);
	DBG_EXPORT JS_METHOD(vertexAttribI4uiv);
	DBG_EXPORT JS_METHOD(vertexAttribDivisor);

	// Blend
	DBG_EXPORT JS_METHOD(blendColor);
	DBG_EXPORT JS_METHOD(blendEquation);
	DBG_EXPORT JS_METHOD(blendEquationSeparate);
	DBG_EXPORT JS_METHOD(blendFunc);
	DBG_EXPORT JS_METHOD(blendFuncSeparate);
	
	// VBO
	DBG_EXPORT JS_METHOD(createBuffer);
	DBG_EXPORT JS_METHOD(deleteBuffer);
	DBG_EXPORT JS_METHOD(isBuffer);
	DBG_EXPORT JS_METHOD(bindBuffer);
	DBG_EXPORT JS_METHOD(bindBufferBase);
	DBG_EXPORT JS_METHOD(bindBufferRange);
	DBG_EXPORT JS_METHOD(bufferData);
	DBG_EXPORT JS_METHOD(bufferSubData);
	DBG_EXPORT JS_METHOD(copyBufferSubData);
	DBG_EXPORT JS_METHOD(getBufferSubData);
	DBG_EXPORT JS_METHOD(getBufferParameter);
	DBG_EXPORT JS_METHOD(readBuffer);
	
	// FBO
	DBG_EXPORT JS_METHOD(createFramebuffer);
	DBG_EXPORT JS_METHOD(deleteFramebuffer);
	DBG_EXPORT JS_METHOD(invalidateFramebuffer);
	DBG_EXPORT JS_METHOD(invalidateSubFramebuffer);
	DBG_EXPORT JS_METHOD(isFramebuffer);
	DBG_EXPORT JS_METHOD(bindFramebuffer);
	DBG_EXPORT JS_METHOD(blitFramebuffer);
	DBG_EXPORT JS_METHOD(checkFramebufferStatus);
	DBG_EXPORT JS_METHOD(framebufferRenderbuffer);
	DBG_EXPORT JS_METHOD(framebufferTexture2D);
	DBG_EXPORT JS_METHOD(framebufferTextureLayer);
	DBG_EXPORT JS_METHOD(getFramebufferAttachmentParameter);
	
	// Program
	DBG_EXPORT JS_METHOD(createProgram);
	DBG_EXPORT JS_METHOD(deleteProgram);
	DBG_EXPORT JS_METHOD(isProgram);
	DBG_EXPORT JS_METHOD(getProgramInfoLog);
	DBG_EXPORT JS_METHOD(getProgramParameter);
	DBG_EXPORT JS_METHOD(linkProgram);
	DBG_EXPORT JS_METHOD(useProgram);
	DBG_EXPORT JS_METHOD(validateProgram);
	DBG_EXPORT JS_METHOD(programParameteri);
	DBG_EXPORT JS_METHOD(getFragDataLocation);
	DBG_EXPORT JS_METHOD(getProgramBinary);
	DBG_EXPORT JS_METHOD(programBinary);
	DBG_EXPORT JS_METHOD(getUniformBlockIndex);
	DBG_EXPORT JS_METHOD(getUniformIndices);
	
	// RBO
	DBG_EXPORT JS_METHOD(createRenderbuffer);
	DBG_EXPORT JS_METHOD(deleteRenderbuffer);
	DBG_EXPORT JS_METHOD(isRenderbuffer);
	DBG_EXPORT JS_METHOD(bindRenderbuffer);
	DBG_EXPORT JS_METHOD(getRenderbufferParameter);
	DBG_EXPORT JS_METHOD(renderbufferStorage);
	DBG_EXPORT JS_METHOD(renderbufferStorageMultisample);
	
	// Shader
	DBG_EXPORT JS_METHOD(deleteShader);
	DBG_EXPORT JS_METHOD(createShader);
	DBG_EXPORT JS_METHOD(isShader);
	DBG_EXPORT JS_METHOD(attachShader);
	DBG_EXPORT JS_METHOD(compileShader);
	DBG_EXPORT JS_METHOD(detachShader);
	DBG_EXPORT JS_METHOD(getAttachedShaders);
	DBG_EXPORT JS_METHOD(getShaderInfoLog);
	DBG_EXPORT JS_METHOD(getShaderParameter);
	DBG_EXPORT JS_METHOD(getShaderSource);
	DBG_EXPORT JS_METHOD(getShaderPrecisionFormat);
	DBG_EXPORT JS_METHOD(shaderSource);
	DBG_EXPORT JS_METHOD(releaseShaderCompiler);
	DBG_EXPORT JS_METHOD(shaderBinary);
	
	// Stencil
	DBG_EXPORT JS_METHOD(clearStencil);
	DBG_EXPORT JS_METHOD(stencilFunc);
	DBG_EXPORT JS_METHOD(stencilFuncSeparate);
	DBG_EXPORT JS_METHOD(stencilMask);
	DBG_EXPORT JS_METHOD(stencilMaskSeparate);
	DBG_EXPORT JS_METHOD(stencilOp);
	DBG_EXPORT JS_METHOD(stencilOpSeparate);
	
	// Texture
	DBG_EXPORT JS_METHOD(createTexture);
	DBG_EXPORT JS_METHOD(deleteTexture);
	DBG_EXPORT JS_METHOD(isTexture);
	DBG_EXPORT JS_METHOD(bindTexture);
	DBG_EXPORT JS_METHOD(activeTexture);
	DBG_EXPORT JS_METHOD(copyTexImage2D);
	DBG_EXPORT JS_METHOD(copyTexSubImage2D);
	DBG_EXPORT JS_METHOD(generateMipmap);
	DBG_EXPORT JS_METHOD(getTexParameter);
	DBG_EXPORT JS_METHOD(texImage2D);
	DBG_EXPORT JS_METHOD(texImage3D);
	DBG_EXPORT JS_METHOD(texParameterf);
	DBG_EXPORT JS_METHOD(texParameteri);
	DBG_EXPORT JS_METHOD(texSubImage2D);
	DBG_EXPORT JS_METHOD(compressedTexSubImage2D);
	DBG_EXPORT JS_METHOD(texStorage2D);
	DBG_EXPORT JS_METHOD(compressedTexImage2D);
	DBG_EXPORT JS_METHOD(compressedTexImage3D);
	DBG_EXPORT JS_METHOD(compressedTexSubImage3D);
	
	// Uniform
	DBG_EXPORT JS_METHOD(getActiveUniform);
	DBG_EXPORT JS_METHOD(getUniform);
	DBG_EXPORT JS_METHOD(getUniformLocation);
	DBG_EXPORT JS_METHOD(uniform1f);
	DBG_EXPORT JS_METHOD(uniform1fv);
	DBG_EXPORT JS_METHOD(uniform1i);
	DBG_EXPORT JS_METHOD(uniform1iv);
	DBG_EXPORT JS_METHOD(uniform2f);
	DBG_EXPORT JS_METHOD(uniform2fv);
	DBG_EXPORT JS_METHOD(uniform2i);
	DBG_EXPORT JS_METHOD(uniform2iv);
	DBG_EXPORT JS_METHOD(uniform3f);
	DBG_EXPORT JS_METHOD(uniform3fv);
	DBG_EXPORT JS_METHOD(uniform3i);
	DBG_EXPORT JS_METHOD(uniform3iv);
	DBG_EXPORT JS_METHOD(uniform4f);
	DBG_EXPORT JS_METHOD(uniform4fv);
	DBG_EXPORT JS_METHOD(uniform4i);
	DBG_EXPORT JS_METHOD(uniform4iv);
	DBG_EXPORT JS_METHOD(uniformMatrix2fv);
	DBG_EXPORT JS_METHOD(uniformMatrix3fv);
	DBG_EXPORT JS_METHOD(uniformMatrix4fv);
	DBG_EXPORT JS_METHOD(uniform1ui);
	DBG_EXPORT JS_METHOD(uniform2ui);
	DBG_EXPORT JS_METHOD(uniform3ui);
	DBG_EXPORT JS_METHOD(uniform4ui);
	DBG_EXPORT JS_METHOD(uniform1uiv);
	DBG_EXPORT JS_METHOD(uniform2uiv);
	DBG_EXPORT JS_METHOD(uniform3uiv);
	DBG_EXPORT JS_METHOD(uniform4uiv);
	DBG_EXPORT JS_METHOD(uniformMatrix2x3fv);
	DBG_EXPORT JS_METHOD(uniformMatrix2x4fv);
	DBG_EXPORT JS_METHOD(uniformMatrix3x2fv);
	DBG_EXPORT JS_METHOD(uniformMatrix3x4fv);
	DBG_EXPORT JS_METHOD(uniformMatrix4x2fv);
	DBG_EXPORT JS_METHOD(uniformMatrix4x3fv);
	DBG_EXPORT JS_METHOD(getUniformfv);
	DBG_EXPORT JS_METHOD(getUniform);
	DBG_EXPORT JS_METHOD(getActiveUniforms);
	DBG_EXPORT JS_METHOD(uniformBlockBinding);
	DBG_EXPORT JS_METHOD(getActiveUniformBlockParameter);
	DBG_EXPORT JS_METHOD(getActiveUniformBlockName);
	
	// VAO
	DBG_EXPORT JS_METHOD(createVertexArray);
	DBG_EXPORT JS_METHOD(deleteVertexArray);
	DBG_EXPORT JS_METHOD(isVertexArray);
	DBG_EXPORT JS_METHOD(bindVertexArray);
	
	// Transform feedback
	int32_t getBoundFeedback();
	DBG_EXPORT JS_METHOD(createTransformFeedback);
	DBG_EXPORT JS_METHOD(deleteTransformFeedback);
	DBG_EXPORT JS_METHOD(isTransformFeedback);
	DBG_EXPORT JS_METHOD(bindTransformFeedback);
	DBG_EXPORT JS_METHOD(beginTransformFeedback);
	DBG_EXPORT JS_METHOD(endTransformFeedback);
	DBG_EXPORT JS_METHOD(pauseTransformFeedback);
	DBG_EXPORT JS_METHOD(resumeTransformFeedback);
	DBG_EXPORT JS_METHOD(transformFeedbackVaryings);
	DBG_EXPORT JS_METHOD(getTransformFeedbackVarying);
	
	// Query
	DBG_EXPORT JS_METHOD(createQuery);
	DBG_EXPORT JS_METHOD(deleteQuery);
	DBG_EXPORT JS_METHOD(isQuery);
	DBG_EXPORT JS_METHOD(beginQuery);
	DBG_EXPORT JS_METHOD(endQuery);
	DBG_EXPORT JS_METHOD(getQueryParameter);
	DBG_EXPORT JS_METHOD(getQuery);
	
	// Sampler
	DBG_EXPORT JS_METHOD(createSampler);
	DBG_EXPORT JS_METHOD(deleteSampler);
	DBG_EXPORT JS_METHOD(isSampler);
	DBG_EXPORT JS_METHOD(bindSampler);
	DBG_EXPORT JS_METHOD(samplerParameterf);
	DBG_EXPORT JS_METHOD(samplerParameteri);
	DBG_EXPORT JS_METHOD(getSamplerParameter);
	
	// Sync
	DBG_EXPORT JS_METHOD(fenceSync);
	DBG_EXPORT JS_METHOD(deleteSync);
	DBG_EXPORT JS_METHOD(isSync);
	DBG_EXPORT JS_METHOD(clientWaitSync);
	DBG_EXPORT JS_METHOD(waitSync);
	DBG_EXPORT JS_METHOD(getSyncParameter);
	
	// Clear
	DBG_EXPORT JS_METHOD(clear);
	DBG_EXPORT JS_METHOD(clearColor);
	DBG_EXPORT JS_METHOD(clearDepth);
	DBG_EXPORT JS_METHOD(clearBufferfv);
	DBG_EXPORT JS_METHOD(clearBufferiv);
	DBG_EXPORT JS_METHOD(clearBufferuiv);
	DBG_EXPORT JS_METHOD(clearBufferfi);
	
	// Draw
	DBG_EXPORT JS_METHOD(drawArrays);
	DBG_EXPORT JS_METHOD(drawElements);
	DBG_EXPORT JS_METHOD(drawBuffers);
	DBG_EXPORT JS_METHOD(drawRangeElements);
	DBG_EXPORT JS_METHOD(drawArraysInstanced);
	DBG_EXPORT JS_METHOD(drawElementsInstanced);
	
	// Misc OpenGL Functions
	DBG_EXPORT JS_METHOD(colorMask);
	DBG_EXPORT JS_METHOD(cullFace);
	DBG_EXPORT JS_METHOD(depthFunc);
	DBG_EXPORT JS_METHOD(depthMask);
	DBG_EXPORT JS_METHOD(depthRange);
	DBG_EXPORT JS_METHOD(disable);
	DBG_EXPORT JS_METHOD(enable);
	DBG_EXPORT JS_METHOD(finish);
	DBG_EXPORT JS_METHOD(flush);
	DBG_EXPORT JS_METHOD(frontFace);
	DBG_EXPORT JS_METHOD(getError);
	DBG_EXPORT JS_METHOD(getParameter);
	DBG_EXPORT JS_METHOD(getInternalformatParameter);
	DBG_EXPORT JS_METHOD(getRenderTarget);
	DBG_EXPORT JS_METHOD(getSupportedExtensions);
	DBG_EXPORT JS_METHOD(hint);
	DBG_EXPORT JS_METHOD(isEnabled);
	DBG_EXPORT JS_METHOD(lineWidth);
	DBG_EXPORT JS_METHOD(pixelStorei);
	DBG_EXPORT JS_METHOD(polygonOffset);
	DBG_EXPORT JS_METHOD(readPixels);
	DBG_EXPORT JS_METHOD(sampleCoverage);
	DBG_EXPORT JS_METHOD(scissor);
	DBG_EXPORT JS_METHOD(viewport);
	DBG_EXPORT JS_METHOD(getIndexedParameter);
} // namespace webgl

#endif /* _WEBGL_HPP_ */
