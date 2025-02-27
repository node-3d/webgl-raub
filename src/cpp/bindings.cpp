#include "webgl.cpp"
#include "attrib.cpp"
#include "blend.cpp"
#include "buffers.cpp"
#include "clear.cpp"
#include "draw.cpp"
#include "framebuffers.cpp"
#include "programs.cpp"
#include "queries.cpp"
#include "renderbuffers.cpp"
#include "sampler.cpp"
#include "shaders.cpp"
#include "stencil.cpp"
#include "sync.cpp"
#include "textures.cpp"
#include "transformfeedback.cpp"
#include "uniform.cpp"
#include "vertexarrays.cpp"

/**
 * @link https://chromium.googlesource.com/chromium/blink/+/refs/heads/main/Source/modules/webgl/WebGL2RenderingContextBase.cpp
 * @link https://chromium.googlesource.com/chromium/blink/+/refs/heads/main/Source/modules/webgl/WebGLRenderingContextBase.cpp
 * @link https://registry.khronos.org/webgl/specs/latest/2.0/#3.1
 */

#define JS_CUSTOM_CONSTANT(name, constant)                                    \
	exports.Set(#name, static_cast<double>(constant));

#define JS_GL_CONSTANT(name)                                                  \
	exports.Set(#name, static_cast<double>(GL_ ## name));

#define JS_GL_SET_METHOD(name)                                                \
	exports.DefineProperty(                                                   \
		Napi::PropertyDescriptor::Function(                                   \
			env,                                                              \
			exports,                                                          \
			#name,                                                            \
			webgl::name,                                                      \
			napi_writable                                                     \
		)                                                                     \
	);


static inline void initMethods(Napi::Env env, Napi::Object exports) {
	JS_GL_SET_METHOD(init);

	// Query
	JS_GL_SET_METHOD(createQuery);
	JS_GL_SET_METHOD(deleteQuery);
	JS_GL_SET_METHOD(isQuery);
	JS_GL_SET_METHOD(beginQuery);
	JS_GL_SET_METHOD(endQuery);
	JS_GL_SET_METHOD(getQueryParameter);
	JS_GL_SET_METHOD(getQuery);
	
	// Sampler
	JS_GL_SET_METHOD(createSampler);
	JS_GL_SET_METHOD(deleteSampler);
	JS_GL_SET_METHOD(isSampler);
	JS_GL_SET_METHOD(bindSampler);
	JS_GL_SET_METHOD(samplerParameterf);
	JS_GL_SET_METHOD(samplerParameteri);
	JS_GL_SET_METHOD(getSamplerParameter);
	
	// Sync
	JS_GL_SET_METHOD(fenceSync);
	JS_GL_SET_METHOD(deleteSync);
	JS_GL_SET_METHOD(isSync);
	JS_GL_SET_METHOD(clientWaitSync);
	JS_GL_SET_METHOD(waitSync);
	JS_GL_SET_METHOD(getSyncParameter);
	
	// Attrib
	JS_GL_SET_METHOD(bindAttribLocation);
	JS_GL_SET_METHOD(disableVertexAttribArray);
	JS_GL_SET_METHOD(enableVertexAttribArray);
	JS_GL_SET_METHOD(getActiveAttrib);
	JS_GL_SET_METHOD(getAttribLocation);
	JS_GL_SET_METHOD(getVertexAttrib);
	JS_GL_SET_METHOD(getVertexAttribOffset);
	JS_GL_SET_METHOD(vertexAttrib1f);
	JS_GL_SET_METHOD(vertexAttrib1fv);
	JS_GL_SET_METHOD(vertexAttrib2f);
	JS_GL_SET_METHOD(vertexAttrib2fv);
	JS_GL_SET_METHOD(vertexAttrib3f);
	JS_GL_SET_METHOD(vertexAttrib3fv);
	JS_GL_SET_METHOD(vertexAttrib4f);
	JS_GL_SET_METHOD(vertexAttrib4fv);
	JS_GL_SET_METHOD(vertexAttribPointer);
	JS_GL_SET_METHOD(vertexAttribIPointer);
	JS_GL_SET_METHOD(vertexAttribI4i);
	JS_GL_SET_METHOD(vertexAttribI4iv);
	JS_GL_SET_METHOD(vertexAttribI4ui);
	JS_GL_SET_METHOD(vertexAttribI4uiv);
	JS_GL_SET_METHOD(vertexAttribDivisor);
	JS_GL_SET_METHOD(vertexAttribDivisor);
	
	// Blend
	JS_GL_SET_METHOD(blendColor);
	JS_GL_SET_METHOD(blendEquation);
	JS_GL_SET_METHOD(blendEquationSeparate);
	JS_GL_SET_METHOD(blendFunc);
	JS_GL_SET_METHOD(blendFuncSeparate);
	
	// VBO
	JS_GL_SET_METHOD(createBuffer);
	JS_GL_SET_METHOD(deleteBuffer);
	JS_GL_SET_METHOD(isBuffer);
	JS_GL_SET_METHOD(bindBuffer);
	JS_GL_SET_METHOD(bindBufferBase);
	JS_GL_SET_METHOD(bindBufferRange);
	JS_GL_SET_METHOD(bufferData);
	JS_GL_SET_METHOD(bufferSubData);
	JS_GL_SET_METHOD(copyBufferSubData);
	JS_GL_SET_METHOD(getBufferSubData);
	JS_GL_SET_METHOD(getBufferParameter);
	JS_GL_SET_METHOD(readBuffer);
	
	// FBO
	JS_GL_SET_METHOD(createFramebuffer);
	JS_GL_SET_METHOD(deleteFramebuffer);
	JS_GL_SET_METHOD(invalidateFramebuffer);
	JS_GL_SET_METHOD(invalidateSubFramebuffer);
	JS_GL_SET_METHOD(isFramebuffer);
	JS_GL_SET_METHOD(bindFramebuffer);
	JS_GL_SET_METHOD(blitFramebuffer);
	JS_GL_SET_METHOD(checkFramebufferStatus);
	JS_GL_SET_METHOD(framebufferRenderbuffer);
	JS_GL_SET_METHOD(framebufferTexture2D);
	JS_GL_SET_METHOD(framebufferTextureLayer);
	JS_GL_SET_METHOD(getFramebufferAttachmentParameter);
	
	// Program
	JS_GL_SET_METHOD(createProgram);
	JS_GL_SET_METHOD(deleteProgram);
	JS_GL_SET_METHOD(isProgram);
	JS_GL_SET_METHOD(getProgramInfoLog);
	JS_GL_SET_METHOD(getProgramParameter);
	JS_GL_SET_METHOD(linkProgram);
	JS_GL_SET_METHOD(useProgram);
	JS_GL_SET_METHOD(validateProgram);
	JS_GL_SET_METHOD(programParameteri);
	JS_GL_SET_METHOD(getFragDataLocation);
	JS_GL_SET_METHOD(getProgramBinary);
	JS_GL_SET_METHOD(programBinary);
	JS_GL_SET_METHOD(getUniformBlockIndex);
	JS_GL_SET_METHOD(getUniformIndices);
	
	// Draw
	JS_GL_SET_METHOD(drawArrays);
	JS_GL_SET_METHOD(drawElements);
	JS_GL_SET_METHOD(drawBuffers);
	JS_GL_SET_METHOD(drawArraysInstanced);
	JS_GL_SET_METHOD(drawElementsInstanced);
	JS_GL_SET_METHOD(drawRangeElements);
	
	// RBO
	JS_GL_SET_METHOD(createRenderbuffer);
	JS_GL_SET_METHOD(deleteRenderbuffer);
	JS_GL_SET_METHOD(isRenderbuffer);
	JS_GL_SET_METHOD(bindRenderbuffer);
	JS_GL_SET_METHOD(getRenderbufferParameter);
	JS_GL_SET_METHOD(renderbufferStorage);
	JS_GL_SET_METHOD(renderbufferStorageMultisample);
	
	// Shader
	JS_GL_SET_METHOD(deleteShader);
	JS_GL_SET_METHOD(createShader);
	JS_GL_SET_METHOD(isShader);
	JS_GL_SET_METHOD(attachShader);
	JS_GL_SET_METHOD(compileShader);
	JS_GL_SET_METHOD(detachShader);
	JS_GL_SET_METHOD(getAttachedShaders);
	JS_GL_SET_METHOD(getShaderInfoLog);
	JS_GL_SET_METHOD(getShaderParameter);
	JS_GL_SET_METHOD(getShaderSource);
	JS_GL_SET_METHOD(getShaderPrecisionFormat);
	JS_GL_SET_METHOD(shaderSource);
	JS_GL_SET_METHOD(releaseShaderCompiler);
	JS_GL_SET_METHOD(shaderBinary);
	
	// Stencil
	JS_GL_SET_METHOD(clearStencil);
	JS_GL_SET_METHOD(stencilFunc);
	JS_GL_SET_METHOD(stencilFuncSeparate);
	JS_GL_SET_METHOD(stencilMask);
	JS_GL_SET_METHOD(stencilMaskSeparate);
	JS_GL_SET_METHOD(stencilOp);
	JS_GL_SET_METHOD(stencilOpSeparate);
	
	// Texture
	JS_GL_SET_METHOD(createTexture);
	JS_GL_SET_METHOD(deleteTexture);
	JS_GL_SET_METHOD(isTexture);
	JS_GL_SET_METHOD(bindTexture);
	JS_GL_SET_METHOD(activeTexture);
	JS_GL_SET_METHOD(copyTexImage2D);
	JS_GL_SET_METHOD(copyTexSubImage2D);
	JS_GL_SET_METHOD(generateMipmap);
	JS_GL_SET_METHOD(getTexParameter);
	JS_GL_SET_METHOD(texImage2D);
	JS_GL_SET_METHOD(texImage3D);
	JS_GL_SET_METHOD(texParameterf);
	JS_GL_SET_METHOD(texParameteri);
	JS_GL_SET_METHOD(texSubImage2D);
	JS_GL_SET_METHOD(compressedTexSubImage2D);
	JS_GL_SET_METHOD(texStorage2D);
	JS_GL_SET_METHOD(compressedTexImage2D);
	JS_GL_SET_METHOD(compressedTexImage3D);
	JS_GL_SET_METHOD(compressedTexSubImage3D);
	JS_GL_SET_METHOD(copyTexSubImage3D);
	JS_GL_SET_METHOD(texStorage3D);
	JS_GL_SET_METHOD(texSubImage3D);
	
	// Uniform
	JS_GL_SET_METHOD(getActiveUniform);
	JS_GL_SET_METHOD(getUniform);
	JS_GL_SET_METHOD(getUniformLocation);
	JS_GL_SET_METHOD(uniform1f);
	JS_GL_SET_METHOD(uniform1fv);
	JS_GL_SET_METHOD(uniform1i);
	JS_GL_SET_METHOD(uniform1iv);
	JS_GL_SET_METHOD(uniform2f);
	JS_GL_SET_METHOD(uniform2fv);
	JS_GL_SET_METHOD(uniform2i);
	JS_GL_SET_METHOD(uniform2iv);
	JS_GL_SET_METHOD(uniform3f);
	JS_GL_SET_METHOD(uniform3fv);
	JS_GL_SET_METHOD(uniform3i);
	JS_GL_SET_METHOD(uniform3iv);
	JS_GL_SET_METHOD(uniform4f);
	JS_GL_SET_METHOD(uniform4fv);
	JS_GL_SET_METHOD(uniform4i);
	JS_GL_SET_METHOD(uniform4iv);
	JS_GL_SET_METHOD(uniformMatrix2fv);
	JS_GL_SET_METHOD(uniformMatrix3fv);
	JS_GL_SET_METHOD(uniformMatrix4fv);
	JS_GL_SET_METHOD(uniform1ui);
	JS_GL_SET_METHOD(uniform2ui);
	JS_GL_SET_METHOD(uniform3ui);
	JS_GL_SET_METHOD(uniform4ui);
	JS_GL_SET_METHOD(uniform1uiv);
	JS_GL_SET_METHOD(uniform2uiv);
	JS_GL_SET_METHOD(uniform3uiv);
	JS_GL_SET_METHOD(uniform4uiv);
	JS_GL_SET_METHOD(uniformMatrix2x3fv);
	JS_GL_SET_METHOD(uniformMatrix2x4fv);
	JS_GL_SET_METHOD(uniformMatrix3x2fv);
	JS_GL_SET_METHOD(uniformMatrix3x4fv);
	JS_GL_SET_METHOD(uniformMatrix4x2fv);
	JS_GL_SET_METHOD(uniformMatrix4x3fv);
	JS_GL_SET_METHOD(getUniformfv);
	JS_GL_SET_METHOD(getActiveUniforms);
	JS_GL_SET_METHOD(uniformBlockBinding);
	JS_GL_SET_METHOD(getActiveUniformBlockParameter);
	JS_GL_SET_METHOD(getActiveUniformBlockName);
	
	// VAO
	JS_GL_SET_METHOD(createVertexArray);
	JS_GL_SET_METHOD(deleteVertexArray);
	JS_GL_SET_METHOD(isVertexArray);
	JS_GL_SET_METHOD(bindVertexArray);
	
	// Transform feedback
	JS_GL_SET_METHOD(createTransformFeedback);
	JS_GL_SET_METHOD(deleteTransformFeedback);
	JS_GL_SET_METHOD(isTransformFeedback);
	JS_GL_SET_METHOD(bindTransformFeedback);
	JS_GL_SET_METHOD(beginTransformFeedback);
	JS_GL_SET_METHOD(endTransformFeedback);
	JS_GL_SET_METHOD(pauseTransformFeedback);
	JS_GL_SET_METHOD(resumeTransformFeedback);
	JS_GL_SET_METHOD(transformFeedbackVaryings);
	JS_GL_SET_METHOD(getTransformFeedbackVarying);
	
	// Clear
	JS_GL_SET_METHOD(clear);
	JS_GL_SET_METHOD(clearColor);
	JS_GL_SET_METHOD(clearDepth);
	JS_GL_SET_METHOD(clearBufferfv);
	JS_GL_SET_METHOD(clearBufferiv);
	JS_GL_SET_METHOD(clearBufferuiv);
	JS_GL_SET_METHOD(clearBufferfi);
	
	// Misc OpenGL Functions
	JS_GL_SET_METHOD(colorMask);
	JS_GL_SET_METHOD(cullFace);
	JS_GL_SET_METHOD(depthFunc);
	JS_GL_SET_METHOD(depthMask);
	JS_GL_SET_METHOD(depthRange);
	JS_GL_SET_METHOD(disable);
	JS_GL_SET_METHOD(enable);
	JS_GL_SET_METHOD(finish);
	JS_GL_SET_METHOD(flush);
	JS_GL_SET_METHOD(frontFace);
	JS_GL_SET_METHOD(getError);
	JS_GL_SET_METHOD(getParameter);
	JS_GL_SET_METHOD(getInternalformatParameter);
	JS_GL_SET_METHOD(getRenderTarget);
	JS_GL_SET_METHOD(getSupportedExtensions);
	JS_GL_SET_METHOD(hint);
	JS_GL_SET_METHOD(isEnabled);
	JS_GL_SET_METHOD(lineWidth);
	JS_GL_SET_METHOD(pixelStorei);
	JS_GL_SET_METHOD(polygonOffset);
	JS_GL_SET_METHOD(readPixels);
	JS_GL_SET_METHOD(sampleCoverage);
	JS_GL_SET_METHOD(scissor);
	JS_GL_SET_METHOD(viewport);
	JS_GL_SET_METHOD(getIndexedParameter);
}


/**
 * WebGL 1.03 constants as per WebGL Specification
 *
 * @link https://registry.khronos.org/webgl/specs/1.0.3/
 */
static inline void initConstantsWebgl103(Napi::Env env, Napi::Object exports) {
	JS_CUSTOM_CONSTANT(BROWSER_DEFAULT_WEBGL, 0x9244);
	JS_CUSTOM_CONSTANT(CONTEXT_LOST_WEBGL, 0x9242);
	JS_CUSTOM_CONSTANT(FRAMEBUFFER_INCOMPLETE_DIMENSIONS, 0x8CD9);
	JS_CUSTOM_CONSTANT(UNPACK_COLORSPACE_CONVERSION_WEBGL, 0x9243);
	JS_CUSTOM_CONSTANT(UNPACK_FLIP_Y_WEBGL, 0x9240);
	JS_CUSTOM_CONSTANT(UNPACK_PREMULTIPLY_ALPHA_WEBGL, 0x9241);
	
	JS_GL_CONSTANT(ACTIVE_ATTRIBUTES);
	JS_GL_CONSTANT(ACTIVE_TEXTURE);
	JS_GL_CONSTANT(ACTIVE_UNIFORMS);
	JS_GL_CONSTANT(ALIASED_LINE_WIDTH_RANGE);
	JS_GL_CONSTANT(ALIASED_POINT_SIZE_RANGE);
	JS_GL_CONSTANT(ALPHA_BITS);
	JS_GL_CONSTANT(ALPHA);
	JS_GL_CONSTANT(ALWAYS);
	JS_GL_CONSTANT(ARRAY_BUFFER_BINDING);
	JS_GL_CONSTANT(ARRAY_BUFFER);
	JS_GL_CONSTANT(ATTACHED_SHADERS);
	JS_GL_CONSTANT(BACK);
	JS_GL_CONSTANT(BLEND_COLOR);
	JS_GL_CONSTANT(BLEND_DST_ALPHA);
	JS_GL_CONSTANT(BLEND_DST_RGB);
	JS_GL_CONSTANT(BLEND_EQUATION_ALPHA);
	JS_GL_CONSTANT(BLEND_EQUATION_RGB);
	JS_GL_CONSTANT(BLEND_EQUATION);
	JS_GL_CONSTANT(BLEND_SRC_ALPHA);
	JS_GL_CONSTANT(BLEND_SRC_RGB);
	JS_GL_CONSTANT(BLEND);
	JS_GL_CONSTANT(BLUE_BITS);
	JS_GL_CONSTANT(BOOL_VEC2);
	JS_GL_CONSTANT(BOOL_VEC3);
	JS_GL_CONSTANT(BOOL_VEC4);
	JS_GL_CONSTANT(BOOL);
	JS_GL_CONSTANT(BUFFER_SIZE);
	JS_GL_CONSTANT(BUFFER_USAGE);
	JS_GL_CONSTANT(BYTE);
	JS_GL_CONSTANT(CCW);
	JS_GL_CONSTANT(CLAMP_TO_EDGE);
	JS_GL_CONSTANT(COLOR_ATTACHMENT0);
	JS_GL_CONSTANT(COLOR_BUFFER_BIT);
	JS_GL_CONSTANT(COLOR_CLEAR_VALUE);
	JS_GL_CONSTANT(COLOR_WRITEMASK);
	JS_GL_CONSTANT(COMPILE_STATUS);
	JS_GL_CONSTANT(COMPRESSED_TEXTURE_FORMATS);
	JS_GL_CONSTANT(CONSTANT_ALPHA);
	JS_GL_CONSTANT(CONSTANT_COLOR);
	JS_GL_CONSTANT(CULL_FACE_MODE);
	JS_GL_CONSTANT(CULL_FACE);
	JS_GL_CONSTANT(CURRENT_PROGRAM);
	JS_GL_CONSTANT(CURRENT_VERTEX_ATTRIB);
	JS_GL_CONSTANT(CW);
	JS_GL_CONSTANT(DECR_WRAP);
	JS_GL_CONSTANT(DECR);
	JS_GL_CONSTANT(DELETE_STATUS);
	JS_GL_CONSTANT(DEPTH_ATTACHMENT);
	JS_GL_CONSTANT(DEPTH_BITS);
	JS_GL_CONSTANT(DEPTH_BUFFER_BIT);
	JS_GL_CONSTANT(DEPTH_CLEAR_VALUE);
	JS_GL_CONSTANT(DEPTH_COMPONENT);
	JS_GL_CONSTANT(DEPTH_COMPONENT16);
	JS_GL_CONSTANT(DEPTH_FUNC);
	JS_GL_CONSTANT(DEPTH_RANGE);
	JS_GL_CONSTANT(DEPTH_STENCIL_ATTACHMENT);
	JS_GL_CONSTANT(DEPTH_STENCIL);
	JS_GL_CONSTANT(DEPTH_TEST);
	JS_GL_CONSTANT(DEPTH_WRITEMASK);
	JS_GL_CONSTANT(DITHER);
	JS_GL_CONSTANT(DONT_CARE);
	JS_GL_CONSTANT(DST_ALPHA);
	JS_GL_CONSTANT(DST_COLOR);
	JS_GL_CONSTANT(DYNAMIC_DRAW);
	JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER_BINDING);
	JS_GL_CONSTANT(ELEMENT_ARRAY_BUFFER);
	JS_GL_CONSTANT(EQUAL);
	JS_GL_CONSTANT(FASTEST);
	JS_GL_CONSTANT(FLOAT_MAT2);
	JS_GL_CONSTANT(FLOAT_MAT3);
	JS_GL_CONSTANT(FLOAT_MAT4);
	JS_GL_CONSTANT(FLOAT_VEC2);
	JS_GL_CONSTANT(FLOAT_VEC3);
	JS_GL_CONSTANT(FLOAT_VEC4);
	JS_GL_CONSTANT(FLOAT);
	JS_GL_CONSTANT(FRAGMENT_SHADER);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL);
	JS_GL_CONSTANT(FRAMEBUFFER_BINDING);
	JS_GL_CONSTANT(FRAMEBUFFER_COMPLETE);
	JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_ATTACHMENT);
	JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT);
	JS_GL_CONSTANT(FRAMEBUFFER_UNSUPPORTED);
	JS_GL_CONSTANT(FRAMEBUFFER);
	JS_GL_CONSTANT(FRONT_AND_BACK);
	JS_GL_CONSTANT(FRONT_FACE);
	JS_GL_CONSTANT(FRONT);
	JS_GL_CONSTANT(FUNC_ADD);
	JS_GL_CONSTANT(FUNC_REVERSE_SUBTRACT);
	JS_GL_CONSTANT(FUNC_SUBTRACT);
	JS_GL_CONSTANT(GENERATE_MIPMAP_HINT);
	JS_GL_CONSTANT(GEQUAL);
	JS_GL_CONSTANT(GREATER);
	JS_GL_CONSTANT(GREEN_BITS);
	JS_GL_CONSTANT(HIGH_FLOAT);
	JS_GL_CONSTANT(HIGH_INT);
	JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_FORMAT);
	JS_GL_CONSTANT(IMPLEMENTATION_COLOR_READ_TYPE);
	JS_GL_CONSTANT(INCR_WRAP);
	JS_GL_CONSTANT(INCR);
	JS_GL_CONSTANT(INT_VEC2);
	JS_GL_CONSTANT(INT_VEC3);
	JS_GL_CONSTANT(INT_VEC4);
	JS_GL_CONSTANT(INT);
	JS_GL_CONSTANT(INVALID_ENUM);
	JS_GL_CONSTANT(INVALID_FRAMEBUFFER_OPERATION);
	JS_GL_CONSTANT(INVALID_OPERATION);
	JS_GL_CONSTANT(INVALID_VALUE);
	JS_GL_CONSTANT(INVERT);
	JS_GL_CONSTANT(KEEP);
	JS_GL_CONSTANT(LEQUAL);
	JS_GL_CONSTANT(LESS);
	JS_GL_CONSTANT(LINE_LOOP);
	JS_GL_CONSTANT(LINE_STRIP);
	JS_GL_CONSTANT(LINE_WIDTH);
	JS_GL_CONSTANT(LINEAR_MIPMAP_LINEAR);
	JS_GL_CONSTANT(LINEAR_MIPMAP_NEAREST);
	JS_GL_CONSTANT(LINEAR);
	JS_GL_CONSTANT(LINES);
	JS_GL_CONSTANT(LINK_STATUS);
	JS_GL_CONSTANT(LOW_FLOAT);
	JS_GL_CONSTANT(LOW_INT);
	JS_GL_CONSTANT(LUMINANCE_ALPHA);
	JS_GL_CONSTANT(LUMINANCE);
	JS_GL_CONSTANT(MAX_COMBINED_TEXTURE_IMAGE_UNITS);
	JS_GL_CONSTANT(MAX_CUBE_MAP_TEXTURE_SIZE);
	JS_GL_CONSTANT(MAX_FRAGMENT_UNIFORM_VECTORS);
	JS_GL_CONSTANT(MAX_RENDERBUFFER_SIZE);
	JS_GL_CONSTANT(MAX_TEXTURE_IMAGE_UNITS);
	JS_GL_CONSTANT(MAX_TEXTURE_SIZE);
	JS_GL_CONSTANT(MAX_VARYING_VECTORS);
	JS_GL_CONSTANT(MAX_VERTEX_ATTRIBS);
	JS_GL_CONSTANT(MAX_VERTEX_TEXTURE_IMAGE_UNITS);
	JS_GL_CONSTANT(MAX_VERTEX_UNIFORM_VECTORS);
	JS_GL_CONSTANT(MAX_VIEWPORT_DIMS);
	JS_GL_CONSTANT(MEDIUM_FLOAT);
	JS_GL_CONSTANT(MEDIUM_INT);
	JS_GL_CONSTANT(MIRRORED_REPEAT);
	JS_GL_CONSTANT(NEAREST_MIPMAP_LINEAR);
	JS_GL_CONSTANT(NEAREST_MIPMAP_NEAREST);
	JS_GL_CONSTANT(NEAREST);
	JS_GL_CONSTANT(NEVER);
	JS_GL_CONSTANT(NICEST);
	JS_GL_CONSTANT(NO_ERROR);
	JS_GL_CONSTANT(NONE);
	JS_GL_CONSTANT(NOTEQUAL);
	JS_GL_CONSTANT(ONE_MINUS_CONSTANT_ALPHA);
	JS_GL_CONSTANT(ONE_MINUS_CONSTANT_COLOR);
	JS_GL_CONSTANT(ONE_MINUS_DST_ALPHA);
	JS_GL_CONSTANT(ONE_MINUS_DST_COLOR);
	JS_GL_CONSTANT(ONE_MINUS_SRC_ALPHA);
	JS_GL_CONSTANT(ONE_MINUS_SRC_COLOR);
	JS_GL_CONSTANT(ONE);
	JS_GL_CONSTANT(OUT_OF_MEMORY);
	JS_GL_CONSTANT(PACK_ALIGNMENT);
	JS_GL_CONSTANT(POINTS);
	JS_GL_CONSTANT(POLYGON_OFFSET_FACTOR);
	JS_GL_CONSTANT(POLYGON_OFFSET_FILL);
	JS_GL_CONSTANT(POLYGON_OFFSET_UNITS);
	JS_GL_CONSTANT(RED_BITS);
	JS_GL_CONSTANT(RENDERBUFFER_ALPHA_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_BINDING);
	JS_GL_CONSTANT(RENDERBUFFER_BLUE_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_DEPTH_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_GREEN_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_HEIGHT);
	JS_GL_CONSTANT(RENDERBUFFER_INTERNAL_FORMAT);
	JS_GL_CONSTANT(RENDERBUFFER_RED_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_STENCIL_SIZE);
	JS_GL_CONSTANT(RENDERBUFFER_WIDTH);
	JS_GL_CONSTANT(RENDERBUFFER);
	JS_GL_CONSTANT(RENDERER);
	JS_GL_CONSTANT(REPEAT);
	JS_GL_CONSTANT(REPLACE);
	JS_GL_CONSTANT(RGB);
	JS_GL_CONSTANT(RGB5_A1);
	JS_GL_CONSTANT(RGB565);
	JS_GL_CONSTANT(RGBA);
	JS_GL_CONSTANT(RGBA4);
	JS_GL_CONSTANT(SAMPLE_ALPHA_TO_COVERAGE);
	JS_GL_CONSTANT(SAMPLE_BUFFERS);
	JS_GL_CONSTANT(SAMPLE_COVERAGE_INVERT);
	JS_GL_CONSTANT(SAMPLE_COVERAGE_VALUE);
	JS_GL_CONSTANT(SAMPLE_COVERAGE);
	JS_GL_CONSTANT(SAMPLER_2D);
	JS_GL_CONSTANT(SAMPLER_CUBE);
	JS_GL_CONSTANT(SAMPLES);
	JS_GL_CONSTANT(SCISSOR_BOX);
	JS_GL_CONSTANT(SCISSOR_TEST);
	JS_GL_CONSTANT(SHADER_TYPE);
	JS_GL_CONSTANT(SHADING_LANGUAGE_VERSION);
	JS_GL_CONSTANT(SHORT);
	JS_GL_CONSTANT(SRC_ALPHA_SATURATE);
	JS_GL_CONSTANT(SRC_ALPHA);
	JS_GL_CONSTANT(SRC_COLOR);
	JS_GL_CONSTANT(STATIC_DRAW);
	JS_GL_CONSTANT(STENCIL_ATTACHMENT);
	JS_GL_CONSTANT(STENCIL_BACK_FAIL);
	JS_GL_CONSTANT(STENCIL_BACK_FUNC);
	JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_FAIL);
	JS_GL_CONSTANT(STENCIL_BACK_PASS_DEPTH_PASS);
	JS_GL_CONSTANT(STENCIL_BACK_REF);
	JS_GL_CONSTANT(STENCIL_BACK_VALUE_MASK);
	JS_GL_CONSTANT(STENCIL_BACK_WRITEMASK);
	JS_GL_CONSTANT(STENCIL_BITS);
	JS_GL_CONSTANT(STENCIL_BUFFER_BIT);
	JS_GL_CONSTANT(STENCIL_CLEAR_VALUE);
	JS_GL_CONSTANT(STENCIL_FAIL);
	JS_GL_CONSTANT(STENCIL_FUNC);
	JS_GL_CONSTANT(STENCIL_INDEX);
	JS_GL_CONSTANT(STENCIL_INDEX8);
	JS_GL_CONSTANT(STENCIL_PASS_DEPTH_FAIL);
	JS_GL_CONSTANT(STENCIL_PASS_DEPTH_PASS);
	JS_GL_CONSTANT(STENCIL_REF);
	JS_GL_CONSTANT(STENCIL_TEST);
	JS_GL_CONSTANT(STENCIL_VALUE_MASK);
	JS_GL_CONSTANT(STENCIL_WRITEMASK);
	JS_GL_CONSTANT(STREAM_DRAW);
	JS_GL_CONSTANT(SUBPIXEL_BITS);
	JS_GL_CONSTANT(TEXTURE_2D);
	JS_GL_CONSTANT(TEXTURE_BINDING_2D);
	JS_GL_CONSTANT(TEXTURE_BINDING_CUBE_MAP);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_X);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Y);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_NEGATIVE_Z);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_X);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Y);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP_POSITIVE_Z);
	JS_GL_CONSTANT(TEXTURE_CUBE_MAP);
	JS_GL_CONSTANT(TEXTURE_MAG_FILTER);
	JS_GL_CONSTANT(TEXTURE_MIN_FILTER);
	JS_GL_CONSTANT(TEXTURE_WRAP_S);
	JS_GL_CONSTANT(TEXTURE_WRAP_T);
	JS_GL_CONSTANT(TEXTURE);
	JS_GL_CONSTANT(TEXTURE0);
	JS_GL_CONSTANT(TEXTURE1);
	JS_GL_CONSTANT(TEXTURE10);
	JS_GL_CONSTANT(TEXTURE11);
	JS_GL_CONSTANT(TEXTURE12);
	JS_GL_CONSTANT(TEXTURE13);
	JS_GL_CONSTANT(TEXTURE14);
	JS_GL_CONSTANT(TEXTURE15);
	JS_GL_CONSTANT(TEXTURE16);
	JS_GL_CONSTANT(TEXTURE17);
	JS_GL_CONSTANT(TEXTURE18);
	JS_GL_CONSTANT(TEXTURE19);
	JS_GL_CONSTANT(TEXTURE2);
	JS_GL_CONSTANT(TEXTURE20);
	JS_GL_CONSTANT(TEXTURE21);
	JS_GL_CONSTANT(TEXTURE22);
	JS_GL_CONSTANT(TEXTURE23);
	JS_GL_CONSTANT(TEXTURE24);
	JS_GL_CONSTANT(TEXTURE25);
	JS_GL_CONSTANT(TEXTURE26);
	JS_GL_CONSTANT(TEXTURE27);
	JS_GL_CONSTANT(TEXTURE28);
	JS_GL_CONSTANT(TEXTURE29);
	JS_GL_CONSTANT(TEXTURE3);
	JS_GL_CONSTANT(TEXTURE30);
	JS_GL_CONSTANT(TEXTURE31);
	JS_GL_CONSTANT(TEXTURE4);
	JS_GL_CONSTANT(TEXTURE5);
	JS_GL_CONSTANT(TEXTURE6);
	JS_GL_CONSTANT(TEXTURE7);
	JS_GL_CONSTANT(TEXTURE8);
	JS_GL_CONSTANT(TEXTURE9);
	JS_GL_CONSTANT(TRIANGLE_FAN);
	JS_GL_CONSTANT(TRIANGLE_STRIP);
	JS_GL_CONSTANT(TRIANGLES);
	JS_GL_CONSTANT(UNPACK_ALIGNMENT);
	JS_GL_CONSTANT(UNSIGNED_BYTE);
	JS_GL_CONSTANT(UNSIGNED_INT);
	JS_GL_CONSTANT(UNSIGNED_SHORT_4_4_4_4);
	JS_GL_CONSTANT(UNSIGNED_SHORT_5_5_5_1);
	JS_GL_CONSTANT(UNSIGNED_SHORT_5_6_5);
	JS_GL_CONSTANT(UNSIGNED_SHORT);
	JS_GL_CONSTANT(VALIDATE_STATUS);
	JS_GL_CONSTANT(VENDOR);
	JS_GL_CONSTANT(VERSION);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_BUFFER_BINDING);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_ENABLED);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_NORMALIZED);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_POINTER);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_SIZE);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_STRIDE);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_TYPE);
	JS_GL_CONSTANT(VERTEX_SHADER);
	JS_GL_CONSTANT(VIEWPORT);
	JS_GL_CONSTANT(ZERO);
}


/**
 * WebGL 2.00 constants as per WebGL 2 Specification
 *
 * @link https://registry.khronos.org/webgl/specs/2.0.0/
 */
static inline void initConstantsWebgl200(Napi::Env env, Napi::Object exports) {
	JS_CUSTOM_CONSTANT(MAX_CLIENT_WAIT_TIMEOUT_WEBGL, 0x9247);
	
	JS_GL_CONSTANT(ACTIVE_UNIFORM_BLOCKS);
	JS_GL_CONSTANT(ALREADY_SIGNALED);
	JS_GL_CONSTANT(ANY_SAMPLES_PASSED_CONSERVATIVE);
	JS_GL_CONSTANT(ANY_SAMPLES_PASSED);
	JS_GL_CONSTANT(COLOR_ATTACHMENT1);
	JS_GL_CONSTANT(COLOR_ATTACHMENT10);
	JS_GL_CONSTANT(COLOR_ATTACHMENT11);
	JS_GL_CONSTANT(COLOR_ATTACHMENT12);
	JS_GL_CONSTANT(COLOR_ATTACHMENT13);
	JS_GL_CONSTANT(COLOR_ATTACHMENT14);
	JS_GL_CONSTANT(COLOR_ATTACHMENT15);
	JS_GL_CONSTANT(COLOR_ATTACHMENT2);
	JS_GL_CONSTANT(COLOR_ATTACHMENT3);
	JS_GL_CONSTANT(COLOR_ATTACHMENT4);
	JS_GL_CONSTANT(COLOR_ATTACHMENT5);
	JS_GL_CONSTANT(COLOR_ATTACHMENT6);
	JS_GL_CONSTANT(COLOR_ATTACHMENT7);
	JS_GL_CONSTANT(COLOR_ATTACHMENT8);
	JS_GL_CONSTANT(COLOR_ATTACHMENT9);
	JS_GL_CONSTANT(COLOR);
	JS_GL_CONSTANT(COMPARE_REF_TO_TEXTURE);
	JS_GL_CONSTANT(CONDITION_SATISFIED);
	JS_GL_CONSTANT(COPY_READ_BUFFER_BINDING);
	JS_GL_CONSTANT(COPY_READ_BUFFER);
	JS_GL_CONSTANT(COPY_WRITE_BUFFER_BINDING);
	JS_GL_CONSTANT(COPY_WRITE_BUFFER);
	JS_GL_CONSTANT(CURRENT_QUERY);
	JS_GL_CONSTANT(DEPTH_COMPONENT24);
	JS_GL_CONSTANT(DEPTH_COMPONENT32F);
	JS_GL_CONSTANT(DEPTH_STENCIL_ATTACHMENT);
	JS_GL_CONSTANT(DEPTH_STENCIL);
	JS_GL_CONSTANT(DEPTH);
	JS_GL_CONSTANT(DEPTH24_STENCIL8);
	JS_GL_CONSTANT(DEPTH32F_STENCIL8);
	JS_GL_CONSTANT(DRAW_BUFFER0);
	JS_GL_CONSTANT(DRAW_BUFFER1);
	JS_GL_CONSTANT(DRAW_BUFFER10);
	JS_GL_CONSTANT(DRAW_BUFFER11);
	JS_GL_CONSTANT(DRAW_BUFFER12);
	JS_GL_CONSTANT(DRAW_BUFFER13);
	JS_GL_CONSTANT(DRAW_BUFFER14);
	JS_GL_CONSTANT(DRAW_BUFFER15);
	JS_GL_CONSTANT(DRAW_BUFFER2);
	JS_GL_CONSTANT(DRAW_BUFFER3);
	JS_GL_CONSTANT(DRAW_BUFFER4);
	JS_GL_CONSTANT(DRAW_BUFFER5);
	JS_GL_CONSTANT(DRAW_BUFFER6);
	JS_GL_CONSTANT(DRAW_BUFFER7);
	JS_GL_CONSTANT(DRAW_BUFFER8);
	JS_GL_CONSTANT(DRAW_BUFFER9);
	JS_GL_CONSTANT(DRAW_FRAMEBUFFER_BINDING);
	JS_GL_CONSTANT(DRAW_FRAMEBUFFER);
	JS_GL_CONSTANT(DYNAMIC_COPY);
	JS_GL_CONSTANT(DYNAMIC_READ);
	JS_GL_CONSTANT(FLOAT_32_UNSIGNED_INT_24_8_REV);
	JS_GL_CONSTANT(FLOAT_MAT2x3);
	JS_GL_CONSTANT(FLOAT_MAT2x4);
	JS_GL_CONSTANT(FLOAT_MAT3x2);
	JS_GL_CONSTANT(FLOAT_MAT3x4);
	JS_GL_CONSTANT(FLOAT_MAT4x2);
	JS_GL_CONSTANT(FLOAT_MAT4x3);
	JS_GL_CONSTANT(FRAGMENT_SHADER_DERIVATIVE_HINT);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_BLUE_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_GREEN_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_RED_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE);
	JS_GL_CONSTANT(FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER);
	JS_GL_CONSTANT(FRAMEBUFFER_DEFAULT);
	JS_GL_CONSTANT(FRAMEBUFFER_INCOMPLETE_MULTISAMPLE);
	JS_GL_CONSTANT(HALF_FLOAT);
	JS_GL_CONSTANT(INT_2_10_10_10_REV);
	JS_GL_CONSTANT(INT_SAMPLER_2D_ARRAY);
	JS_GL_CONSTANT(INT_SAMPLER_2D);
	JS_GL_CONSTANT(INT_SAMPLER_3D);
	JS_GL_CONSTANT(INT_SAMPLER_CUBE);
	JS_GL_CONSTANT(INTERLEAVED_ATTRIBS);
	JS_GL_CONSTANT(INVALID_INDEX);
	JS_GL_CONSTANT(MAX_3D_TEXTURE_SIZE);
	JS_GL_CONSTANT(MAX_ARRAY_TEXTURE_LAYERS);
	JS_GL_CONSTANT(MAX_COLOR_ATTACHMENTS);
	JS_GL_CONSTANT(MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS);
	JS_GL_CONSTANT(MAX_COMBINED_UNIFORM_BLOCKS);
	JS_GL_CONSTANT(MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS);
	JS_GL_CONSTANT(MAX_DRAW_BUFFERS);
	JS_GL_CONSTANT(MAX_ELEMENT_INDEX);
	JS_GL_CONSTANT(MAX_ELEMENTS_INDICES);
	JS_GL_CONSTANT(MAX_ELEMENTS_VERTICES);
	JS_GL_CONSTANT(MAX_FRAGMENT_INPUT_COMPONENTS);
	JS_GL_CONSTANT(MAX_FRAGMENT_UNIFORM_BLOCKS);
	JS_GL_CONSTANT(MAX_FRAGMENT_UNIFORM_COMPONENTS);
	JS_GL_CONSTANT(MAX_PROGRAM_TEXEL_OFFSET);
	JS_GL_CONSTANT(MAX_SAMPLES);
	JS_GL_CONSTANT(MAX_SERVER_WAIT_TIMEOUT);
	JS_GL_CONSTANT(MAX_TEXTURE_LOD_BIAS);
	JS_GL_CONSTANT(MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS);
	JS_GL_CONSTANT(MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS);
	JS_GL_CONSTANT(MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS);
	JS_GL_CONSTANT(MAX_UNIFORM_BLOCK_SIZE);
	JS_GL_CONSTANT(MAX_UNIFORM_BUFFER_BINDINGS);
	JS_GL_CONSTANT(MAX_VARYING_COMPONENTS);
	JS_GL_CONSTANT(MAX_VERTEX_OUTPUT_COMPONENTS);
	JS_GL_CONSTANT(MAX_VERTEX_UNIFORM_BLOCKS);
	JS_GL_CONSTANT(MAX_VERTEX_UNIFORM_COMPONENTS);
	JS_GL_CONSTANT(MAX);
	JS_GL_CONSTANT(MIN_PROGRAM_TEXEL_OFFSET);
	JS_GL_CONSTANT(MIN);
	JS_GL_CONSTANT(OBJECT_TYPE);
	JS_GL_CONSTANT(PACK_ROW_LENGTH);
	JS_GL_CONSTANT(PACK_SKIP_PIXELS);
	JS_GL_CONSTANT(PACK_SKIP_ROWS);
	JS_GL_CONSTANT(PIXEL_PACK_BUFFER_BINDING);
	JS_GL_CONSTANT(PIXEL_PACK_BUFFER);
	JS_GL_CONSTANT(PIXEL_UNPACK_BUFFER_BINDING);
	JS_GL_CONSTANT(PIXEL_UNPACK_BUFFER);
	JS_GL_CONSTANT(QUERY_RESULT_AVAILABLE);
	JS_GL_CONSTANT(QUERY_RESULT);
	JS_GL_CONSTANT(R11F_G11F_B10F);
	JS_GL_CONSTANT(R16F);
	JS_GL_CONSTANT(R16I);
	JS_GL_CONSTANT(R16UI);
	JS_GL_CONSTANT(R32F);
	JS_GL_CONSTANT(R32I);
	JS_GL_CONSTANT(R32UI);
	JS_GL_CONSTANT(R8_SNORM);
	JS_GL_CONSTANT(R8);
	JS_GL_CONSTANT(R8I);
	JS_GL_CONSTANT(R8UI);
	JS_GL_CONSTANT(RASTERIZER_DISCARD);
	JS_GL_CONSTANT(READ_BUFFER);
	JS_GL_CONSTANT(READ_FRAMEBUFFER_BINDING);
	JS_GL_CONSTANT(READ_FRAMEBUFFER);
	JS_GL_CONSTANT(RED_INTEGER);
	JS_GL_CONSTANT(RED);
	JS_GL_CONSTANT(RENDERBUFFER_SAMPLES);
	JS_GL_CONSTANT(RG_INTEGER);
	JS_GL_CONSTANT(RG);
	JS_GL_CONSTANT(RG16F);
	JS_GL_CONSTANT(RG16I);
	JS_GL_CONSTANT(RG16UI);
	JS_GL_CONSTANT(RG32F);
	JS_GL_CONSTANT(RG32I);
	JS_GL_CONSTANT(RG32UI);
	JS_GL_CONSTANT(RG8_SNORM);
	JS_GL_CONSTANT(RG8);
	JS_GL_CONSTANT(RG8I);
	JS_GL_CONSTANT(RG8UI);
	JS_GL_CONSTANT(RGB_INTEGER);
	JS_GL_CONSTANT(RGB10_A2);
	JS_GL_CONSTANT(RGB10_A2UI);
	JS_GL_CONSTANT(RGB16F);
	JS_GL_CONSTANT(RGB16I);
	JS_GL_CONSTANT(RGB16UI);
	JS_GL_CONSTANT(RGB32F);
	JS_GL_CONSTANT(RGB32I);
	JS_GL_CONSTANT(RGB32UI);
	JS_GL_CONSTANT(RGB8_SNORM);
	JS_GL_CONSTANT(RGB8);
	JS_GL_CONSTANT(RGB8I);
	JS_GL_CONSTANT(RGB8UI);
	JS_GL_CONSTANT(RGB9_E5);
	JS_GL_CONSTANT(RGBA_INTEGER);
	JS_GL_CONSTANT(RGBA16F);
	JS_GL_CONSTANT(RGBA16I);
	JS_GL_CONSTANT(RGBA16UI);
	JS_GL_CONSTANT(RGBA32F);
	JS_GL_CONSTANT(RGBA32I);
	JS_GL_CONSTANT(RGBA32UI);
	JS_GL_CONSTANT(RGBA8_SNORM);
	JS_GL_CONSTANT(RGBA8);
	JS_GL_CONSTANT(RGBA8I);
	JS_GL_CONSTANT(RGBA8UI);
	JS_GL_CONSTANT(SAMPLER_2D_ARRAY_SHADOW);
	JS_GL_CONSTANT(SAMPLER_2D_ARRAY);
	JS_GL_CONSTANT(SAMPLER_2D_SHADOW);
	JS_GL_CONSTANT(SAMPLER_3D);
	JS_GL_CONSTANT(SAMPLER_BINDING);
	JS_GL_CONSTANT(SAMPLER_CUBE_SHADOW);
	JS_GL_CONSTANT(SEPARATE_ATTRIBS);
	JS_GL_CONSTANT(SIGNALED);
	JS_GL_CONSTANT(SIGNED_NORMALIZED);
	JS_GL_CONSTANT(SRGB);
	JS_GL_CONSTANT(SRGB8_ALPHA8);
	JS_GL_CONSTANT(SRGB8);
	JS_GL_CONSTANT(STATIC_COPY);
	JS_GL_CONSTANT(STATIC_READ);
	JS_GL_CONSTANT(STENCIL);
	JS_GL_CONSTANT(STREAM_COPY);
	JS_GL_CONSTANT(STREAM_READ);
	JS_GL_CONSTANT(SYNC_CONDITION);
	JS_GL_CONSTANT(SYNC_FENCE);
	JS_GL_CONSTANT(SYNC_FLAGS);
	JS_GL_CONSTANT(SYNC_FLUSH_COMMANDS_BIT);
	JS_GL_CONSTANT(SYNC_GPU_COMMANDS_COMPLETE);
	JS_GL_CONSTANT(SYNC_STATUS);
	JS_GL_CONSTANT(TEXTURE_2D_ARRAY);
	JS_GL_CONSTANT(TEXTURE_3D);
	JS_GL_CONSTANT(TEXTURE_BASE_LEVEL);
	JS_GL_CONSTANT(TEXTURE_BINDING_2D_ARRAY);
	JS_GL_CONSTANT(TEXTURE_BINDING_3D);
	JS_GL_CONSTANT(TEXTURE_COMPARE_FUNC);
	JS_GL_CONSTANT(TEXTURE_COMPARE_MODE);
	JS_GL_CONSTANT(TEXTURE_IMMUTABLE_FORMAT);
	JS_GL_CONSTANT(TEXTURE_IMMUTABLE_LEVELS);
	JS_GL_CONSTANT(TEXTURE_MAX_LEVEL);
	JS_GL_CONSTANT(TEXTURE_MAX_LOD);
	JS_GL_CONSTANT(TEXTURE_MIN_LOD);
	JS_GL_CONSTANT(TEXTURE_WRAP_R);
	JS_GL_CONSTANT(TIMEOUT_EXPIRED);
	JS_GL_CONSTANT(TIMEOUT_IGNORED);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_ACTIVE);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BINDING);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BUFFER_BINDING);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BUFFER_MODE);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BUFFER_SIZE);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BUFFER_START);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_BUFFER);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_PAUSED);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK_VARYINGS);
	JS_GL_CONSTANT(TRANSFORM_FEEDBACK);
	JS_GL_CONSTANT(UNIFORM_ARRAY_STRIDE);
	JS_GL_CONSTANT(UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES);
	JS_GL_CONSTANT(UNIFORM_BLOCK_ACTIVE_UNIFORMS);
	JS_GL_CONSTANT(UNIFORM_BLOCK_BINDING);
	JS_GL_CONSTANT(UNIFORM_BLOCK_DATA_SIZE);
	JS_GL_CONSTANT(UNIFORM_BLOCK_INDEX);
	JS_GL_CONSTANT(UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER);
	JS_GL_CONSTANT(UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER);
	JS_GL_CONSTANT(UNIFORM_BUFFER_BINDING);
	JS_GL_CONSTANT(UNIFORM_BUFFER_OFFSET_ALIGNMENT);
	JS_GL_CONSTANT(UNIFORM_BUFFER_SIZE);
	JS_GL_CONSTANT(UNIFORM_BUFFER_START);
	JS_GL_CONSTANT(UNIFORM_BUFFER);
	JS_GL_CONSTANT(UNIFORM_IS_ROW_MAJOR);
	JS_GL_CONSTANT(UNIFORM_MATRIX_STRIDE);
	JS_GL_CONSTANT(UNIFORM_OFFSET);
	JS_GL_CONSTANT(UNIFORM_SIZE);
	JS_GL_CONSTANT(UNIFORM_TYPE);
	JS_GL_CONSTANT(UNPACK_IMAGE_HEIGHT);
	JS_GL_CONSTANT(UNPACK_ROW_LENGTH);
	JS_GL_CONSTANT(UNPACK_SKIP_IMAGES);
	JS_GL_CONSTANT(UNPACK_SKIP_PIXELS);
	JS_GL_CONSTANT(UNPACK_SKIP_ROWS);
	JS_GL_CONSTANT(UNSIGNALED);
	JS_GL_CONSTANT(UNSIGNED_INT_10F_11F_11F_REV);
	JS_GL_CONSTANT(UNSIGNED_INT_2_10_10_10_REV);
	JS_GL_CONSTANT(UNSIGNED_INT_24_8);
	JS_GL_CONSTANT(UNSIGNED_INT_5_9_9_9_REV);
	JS_GL_CONSTANT(UNSIGNED_INT_SAMPLER_2D_ARRAY);
	JS_GL_CONSTANT(UNSIGNED_INT_SAMPLER_2D);
	JS_GL_CONSTANT(UNSIGNED_INT_SAMPLER_3D);
	JS_GL_CONSTANT(UNSIGNED_INT_SAMPLER_CUBE);
	JS_GL_CONSTANT(UNSIGNED_INT_VEC2);
	JS_GL_CONSTANT(UNSIGNED_INT_VEC3);
	JS_GL_CONSTANT(UNSIGNED_INT_VEC4);
	JS_GL_CONSTANT(UNSIGNED_NORMALIZED);
	JS_GL_CONSTANT(VERTEX_ARRAY_BINDING);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_DIVISOR);
	JS_GL_CONSTANT(VERTEX_ATTRIB_ARRAY_INTEGER);
	JS_GL_CONSTANT(WAIT_FAILED);
}


static inline void initConstantsOther(Napi::Env env, Napi::Object exports) {
	JS_GL_CONSTANT(ACTIVE_ATTRIBUTE_MAX_LENGTH);
	JS_GL_CONSTANT(ACTIVE_UNIFORM_MAX_LENGTH);
	JS_GL_CONSTANT(CLAMP_TO_BORDER);
	JS_GL_CONSTANT(CLAMP);
	JS_GL_CONSTANT(EXTENSIONS);
	JS_GL_CONSTANT(FALSE);
	JS_GL_CONSTANT(FIXED);
	JS_GL_CONSTANT(NUM_COMPRESSED_TEXTURE_FORMATS);
	JS_GL_CONSTANT(NUM_SHADER_BINARY_FORMATS);
	JS_GL_CONSTANT(POINT_SPRITE);
	JS_GL_CONSTANT(PROGRAM_POINT_SIZE);
	JS_GL_CONSTANT(SHADER_BINARY_FORMATS);
	JS_GL_CONSTANT(SHADER_COMPILER);
	JS_GL_CONSTANT(SHADER_SOURCE_LENGTH);
	JS_GL_CONSTANT(TRUE);
}


Napi::Object initModule(Napi::Env env, Napi::Object exports) {
	webgl::undefined = env.Undefined();
	
	initMethods(env, exports);
	
	initConstantsWebgl103(env, exports);
	initConstantsWebgl200(env, exports);
	initConstantsOther(env, exports);
	
	return exports;
}


NODE_API_MODULE(webgl, initModule)
