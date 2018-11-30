#ifndef _WEBGL_HPP_
#define _WEBGL_HPP_


#include <addon-tools.hpp>

#include <GL/glew.h>


#define USE_UINT32_ARG(I, VAR, DEF)                                           \
	CHECK_LET_ARG(I, IsUint32(), "uint32");                                   \
	unsigned int VAR = IS_ARG_EMPTY(I) ? (DEF) : info[I].As<v8::Uint32>()->Value();


namespace webgl {
	
	// forward declarations
	enum GLObjectType {
		GLOBJECT_TYPE_BUFFER,
		GLOBJECT_TYPE_FRAMEBUFFER,
		GLOBJECT_TYPE_PROGRAM,
		GLOBJECT_TYPE_RENDERBUFFER,
		GLOBJECT_TYPE_SHADER,
		GLOBJECT_TYPE_TEXTURE,
	};
	
	void registerGLObj(GLObjectType type, GLuint obj);
	void unregisterGLObj(GLuint obj);
	
	
	
	void deinit();
	
	NAN_METHOD(init);
	
	NAN_METHOD(uniform1f);
	NAN_METHOD(uniform2f);
	NAN_METHOD(uniform3f);
	NAN_METHOD(uniform4f);
	NAN_METHOD(uniform1i);
	NAN_METHOD(uniform2i);
	NAN_METHOD(uniform3i);
	NAN_METHOD(uniform4i);
	NAN_METHOD(uniform1fv);
	NAN_METHOD(uniform2fv);
	NAN_METHOD(uniform3fv);
	NAN_METHOD(uniform4fv);
	NAN_METHOD(uniform1iv);
	NAN_METHOD(uniform2iv);
	NAN_METHOD(uniform3iv);
	NAN_METHOD(uniform4iv);
	NAN_METHOD(pixelStorei);
	NAN_METHOD(bindAttribLocation);
	NAN_METHOD(blitFrameBuffer);
	NAN_METHOD(getError);
	NAN_METHOD(drawArrays);
	NAN_METHOD(uniformMatrix2fv);
	NAN_METHOD(uniformMatrix3fv);
	NAN_METHOD(uniformMatrix4fv);
	NAN_METHOD(generateMipmap);
	NAN_METHOD(getAttribLocation);
	NAN_METHOD(depthFunc);
	NAN_METHOD(viewport);
	NAN_METHOD(createShader);
	NAN_METHOD(shaderSource);
	NAN_METHOD(compileShader);
	NAN_METHOD(getShaderParameter);
	NAN_METHOD(getShaderInfoLog);
	NAN_METHOD(createProgram);
	NAN_METHOD(attachShader);
	NAN_METHOD(linkProgram);
	NAN_METHOD(getProgramParameter);
	NAN_METHOD(getUniformLocation);
	NAN_METHOD(clearColor);
	NAN_METHOD(clearDepth);
	NAN_METHOD(disable);
	NAN_METHOD(enable);
	NAN_METHOD(createTexture);
	NAN_METHOD(bindTexture);
	NAN_METHOD(texImage2D);
	NAN_METHOD(texParameteri);
	NAN_METHOD(texParameterf);
	NAN_METHOD(clear);
	NAN_METHOD(useProgram);
	NAN_METHOD(createBuffer);
	NAN_METHOD(bindBuffer);
	NAN_METHOD(createFramebuffer);
	NAN_METHOD(bindFramebuffer);
	NAN_METHOD(framebufferTexture2D);
	NAN_METHOD(bufferData);
	NAN_METHOD(bufferSubData);
	NAN_METHOD(blendEquation);
	NAN_METHOD(blendFunc);
	NAN_METHOD(enableVertexAttribArray);
	NAN_METHOD(vertexAttribPointer);
	NAN_METHOD(activeTexture);
	NAN_METHOD(drawElements);
	NAN_METHOD(flush);
	NAN_METHOD(finish);
	
	NAN_METHOD(vertexAttrib1f);
	NAN_METHOD(vertexAttrib2f);
	NAN_METHOD(vertexAttrib3f);
	NAN_METHOD(vertexAttrib4f);
	NAN_METHOD(vertexAttrib1fv);
	NAN_METHOD(vertexAttrib2fv);
	NAN_METHOD(vertexAttrib3fv);
	NAN_METHOD(vertexAttrib4fv);
	
	NAN_METHOD(blendColor);
	NAN_METHOD(blendEquationSeparate);
	NAN_METHOD(blendFuncSeparate);
	NAN_METHOD(clearStencil);
	NAN_METHOD(colorMask);
	NAN_METHOD(copyTexImage2D);
	NAN_METHOD(copyTexSubImage2D);
	NAN_METHOD(cullFace);
	NAN_METHOD(depthMask);
	NAN_METHOD(depthRange);
	NAN_METHOD(disableVertexAttribArray);
	NAN_METHOD(hint);
	NAN_METHOD(isEnabled);
	NAN_METHOD(lineWidth);
	NAN_METHOD(polygonOffset);
	
	NAN_METHOD(scissor);
	NAN_METHOD(stencilFunc);
	NAN_METHOD(stencilFuncSeparate);
	NAN_METHOD(stencilMask);
	NAN_METHOD(stencilMaskSeparate);
	NAN_METHOD(stencilOp);
	NAN_METHOD(stencilOpSeparate);
	NAN_METHOD(bindRenderbuffer);
	NAN_METHOD(createRenderbuffer);
	
	NAN_METHOD(deleteBuffer);
	NAN_METHOD(deleteFramebuffer);
	NAN_METHOD(deleteProgram);
	NAN_METHOD(deleteRenderbuffer);
	NAN_METHOD(deleteShader);
	NAN_METHOD(deleteTexture);
	NAN_METHOD(detachShader);
	NAN_METHOD(framebufferRenderbuffer);
	NAN_METHOD(getVertexAttribOffset);
	
	NAN_METHOD(isBuffer);
	NAN_METHOD(isFramebuffer);
	NAN_METHOD(isProgram);
	NAN_METHOD(isRenderbuffer);
	NAN_METHOD(isShader);
	NAN_METHOD(isTexture);
	
	NAN_METHOD(renderbufferStorage);
	NAN_METHOD(getShaderSource);
	NAN_METHOD(validateProgram);
	
	NAN_METHOD(texSubImage2D);
	NAN_METHOD(readPixels);
	NAN_METHOD(getTexParameter);
	NAN_METHOD(getActiveAttrib);
	NAN_METHOD(getActiveUniform);
	NAN_METHOD(getAttachedShaders);
	NAN_METHOD(getParameter);
	NAN_METHOD(getBufferParameter);
	NAN_METHOD(getFramebufferAttachmentParameter);
	NAN_METHOD(getProgramInfoLog);
	NAN_METHOD(getRenderbufferParameter);
	NAN_METHOD(getVertexAttrib);
	NAN_METHOD(getSupportedExtensions);
	NAN_METHOD(getExtension);
	NAN_METHOD(checkFramebufferStatus);
	
	NAN_METHOD(frontFace);
	
} // namespace webgl

#endif /* _WEBGL_HPP_ */
