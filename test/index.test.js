'use strict';

const webgl = require('..');


const constants = [
	'DEPTH_BUFFER_BIT','STENCIL_BUFFER_BIT','COLOR_BUFFER_BIT','FALSE','TRUE',
	'POINTS','LINES','LINE_LOOP','LINE_STRIP','TRIANGLES','TRIANGLE_STRIP',
	'TRIANGLE_FAN','ZERO','ONE','SRC_COLOR','ONE_MINUS_SRC_COLOR','SRC_ALPHA',
	'ONE_MINUS_SRC_ALPHA','DST_ALPHA','ONE_MINUS_DST_ALPHA','DST_COLOR',
	'ONE_MINUS_DST_COLOR','SRC_ALPHA_SATURATE','FUNC_ADD','BLEND_EQUATION',
	'BLEND_EQUATION_RGB','BLEND_EQUATION_ALPHA','FUNC_SUBTRACT',
	'FUNC_REVERSE_SUBTRACT','BLEND_DST_RGB','BLEND_SRC_RGB','BLEND_DST_ALPHA',
	'BLEND_SRC_ALPHA','CONSTANT_COLOR','ONE_MINUS_CONSTANT_COLOR',
	'CONSTANT_ALPHA','ONE_MINUS_CONSTANT_ALPHA','BLEND_COLOR','ARRAY_BUFFER',
	'ELEMENT_ARRAY_BUFFER','ARRAY_BUFFER_BINDING','ELEMENT_ARRAY_BUFFER_BINDING',
	'STREAM_DRAW','STATIC_DRAW','DYNAMIC_DRAW','BUFFER_SIZE','BUFFER_USAGE',
	'CURRENT_VERTEX_ATTRIB','FRONT','BACK','FRONT_AND_BACK','TEXTURE_2D',
	'CULL_FACE','BLEND','DITHER','STENCIL_TEST','DEPTH_TEST','SCISSOR_TEST',
	'POLYGON_OFFSET_FILL','SAMPLE_ALPHA_TO_COVERAGE','SAMPLE_COVERAGE',
	'NO_ERROR','INVALID_ENUM','INVALID_VALUE','INVALID_OPERATION','OUT_OF_MEMORY',
	'CW','CCW','LINE_WIDTH','ALIASED_POINT_SIZE_RANGE','ALIASED_LINE_WIDTH_RANGE',
	'CULL_FACE_MODE','FRONT_FACE','DEPTH_RANGE','DEPTH_WRITEMASK',
	'DEPTH_CLEAR_VALUE','DEPTH_FUNC','STENCIL_CLEAR_VALUE','STENCIL_FUNC',
	'STENCIL_FAIL','STENCIL_PASS_DEPTH_FAIL','STENCIL_PASS_DEPTH_PASS','STENCIL_REF',
	'STENCIL_VALUE_MASK','STENCIL_WRITEMASK','STENCIL_BACK_FUNC','STENCIL_BACK_FAIL',
	'STENCIL_BACK_PASS_DEPTH_FAIL','STENCIL_BACK_PASS_DEPTH_PASS','STENCIL_BACK_REF',
	'STENCIL_BACK_VALUE_MASK','STENCIL_BACK_WRITEMASK','VIEWPORT','SCISSOR_BOX',
	'COLOR_CLEAR_VALUE','COLOR_WRITEMASK','UNPACK_ALIGNMENT','PACK_ALIGNMENT',
	'MAX_TEXTURE_SIZE','MAX_VIEWPORT_DIMS','SUBPIXEL_BITS','RED_BITS','GREEN_BITS',
	'BLUE_BITS','ALPHA_BITS','DEPTH_BITS','STENCIL_BITS','POLYGON_OFFSET_UNITS',
	'POLYGON_OFFSET_FACTOR','TEXTURE_BINDING_2D','SAMPLE_BUFFERS','SAMPLES',
	'SAMPLE_COVERAGE_VALUE','SAMPLE_COVERAGE_INVERT','NUM_COMPRESSED_TEXTURE_FORMATS',
	'COMPRESSED_TEXTURE_FORMATS','DONT_CARE','FASTEST','NICEST',
	'GENERATE_MIPMAP_HINT','BYTE','UNSIGNED_BYTE','SHORT','UNSIGNED_SHORT',
	'INT','UNSIGNED_INT','FLOAT','FIXED','DEPTH_COMPONENT','ALPHA','RGB','RGBA',
	'LUMINANCE','LUMINANCE_ALPHA','UNSIGNED_SHORT_4_4_4_4','UNSIGNED_SHORT_5_5_5_1',
	'UNSIGNED_SHORT_5_6_5','FRAGMENT_SHADER','VERTEX_SHADER','MAX_VERTEX_ATTRIBS',
	'MAX_VERTEX_UNIFORM_VECTORS','MAX_VARYING_VECTORS',
	'MAX_COMBINED_TEXTURE_IMAGE_UNITS','MAX_VERTEX_TEXTURE_IMAGE_UNITS',
	'MAX_TEXTURE_IMAGE_UNITS','MAX_FRAGMENT_UNIFORM_VECTORS','SHADER_TYPE',
	'DELETE_STATUS','LINK_STATUS','VALIDATE_STATUS','ATTACHED_SHADERS',
	'ACTIVE_UNIFORMS','ACTIVE_UNIFORM_MAX_LENGTH','ACTIVE_ATTRIBUTES',
	'ACTIVE_ATTRIBUTE_MAX_LENGTH','SHADING_LANGUAGE_VERSION','CURRENT_PROGRAM',
	'NEVER','LESS','EQUAL','LEQUAL','GREATER','NOTEQUAL','GEQUAL','ALWAYS',
	'KEEP','REPLACE','INCR','DECR','INVERT','INCR_WRAP','DECR_WRAP',
	'PROGRAM_POINT_SIZE','POINT_SPRITE','VENDOR','RENDERER','VERSION',
	'EXTENSIONS','NEAREST','LINEAR','NEAREST_MIPMAP_NEAREST','LINEAR_MIPMAP_NEAREST',
	'NEAREST_MIPMAP_LINEAR','LINEAR_MIPMAP_LINEAR','TEXTURE_MAG_FILTER',
	'TEXTURE_MIN_FILTER','TEXTURE_WRAP_S','TEXTURE_WRAP_T','TEXTURE',
	'TEXTURE_CUBE_MAP','TEXTURE_BINDING_CUBE_MAP','TEXTURE_CUBE_MAP_POSITIVE_X',
	'TEXTURE_CUBE_MAP_NEGATIVE_X','TEXTURE_CUBE_MAP_POSITIVE_Y',
	'TEXTURE_CUBE_MAP_NEGATIVE_Y','TEXTURE_CUBE_MAP_POSITIVE_Z',
	'TEXTURE_CUBE_MAP_NEGATIVE_Z','MAX_CUBE_MAP_TEXTURE_SIZE','TEXTURE0',
	'TEXTURE1','TEXTURE2','TEXTURE3','TEXTURE4','TEXTURE5','TEXTURE6',
	'TEXTURE7','TEXTURE8','TEXTURE9','TEXTURE10','TEXTURE11','TEXTURE12',
	'TEXTURE13','TEXTURE14','TEXTURE15','TEXTURE16','TEXTURE17','TEXTURE18',
	'TEXTURE19','TEXTURE20','TEXTURE21','TEXTURE22','TEXTURE23','TEXTURE24',
	'TEXTURE25','TEXTURE26','TEXTURE27','TEXTURE28','TEXTURE29','TEXTURE30',
	'TEXTURE31','ACTIVE_TEXTURE','CLAMP','CLAMP_TO_BORDER','CLAMP_TO_EDGE',
	'MIRRORED_REPEAT','REPEAT','FLOAT_VEC2','FLOAT_VEC3','FLOAT_VEC4','INT_VEC2',
	'INT_VEC3','INT_VEC4','BOOL','BOOL_VEC2','BOOL_VEC3','BOOL_VEC4','FLOAT_MAT2',
	'FLOAT_MAT3','FLOAT_MAT4','SAMPLER_2D','SAMPLER_CUBE',
	'VERTEX_ATTRIB_ARRAY_ENABLED','VERTEX_ATTRIB_ARRAY_SIZE',
	'VERTEX_ATTRIB_ARRAY_STRIDE','VERTEX_ATTRIB_ARRAY_TYPE',
	'VERTEX_ATTRIB_ARRAY_NORMALIZED','VERTEX_ATTRIB_ARRAY_POINTER',
	'VERTEX_ATTRIB_ARRAY_BUFFER_BINDING','IMPLEMENTATION_COLOR_READ_TYPE',
	'IMPLEMENTATION_COLOR_READ_FORMAT','COMPILE_STATUS','INFO_LOG_LENGTH',
	'SHADER_SOURCE_LENGTH','SHADER_COMPILER','SHADER_BINARY_FORMATS',
	'NUM_SHADER_BINARY_FORMATS','LOW_FLOAT','MEDIUM_FLOAT','HIGH_FLOAT',
	'LOW_INT','MEDIUM_INT','HIGH_INT','FRAMEBUFFER','RENDERBUFFER','RGBA4',
	'RGB5_A1','DEPTH_COMPONENT16','STENCIL_INDEX','STENCIL_INDEX8',
	'DEPTH_STENCIL','DEPTH24_STENCIL8','RENDERBUFFER_WIDTH',
	'RENDERBUFFER_HEIGHT','RENDERBUFFER_INTERNAL_FORMAT','RENDERBUFFER_RED_SIZE',
	'RENDERBUFFER_GREEN_SIZE','RENDERBUFFER_BLUE_SIZE','RENDERBUFFER_ALPHA_SIZE',
	'RENDERBUFFER_DEPTH_SIZE','RENDERBUFFER_STENCIL_SIZE',
	'FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE','FRAMEBUFFER_ATTACHMENT_OBJECT_NAME',
	'FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL',
	'FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE','COLOR_ATTACHMENT0',
	'DEPTH_ATTACHMENT','STENCIL_ATTACHMENT','DEPTH_STENCIL_ATTACHMENT',
	'NONE','FRAMEBUFFER_COMPLETE','FRAMEBUFFER_INCOMPLETE_ATTACHMENT',
	'FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT',
	'FRAMEBUFFER_UNSUPPORTED',
	'FRAMEBUFFER_BINDING','RENDERBUFFER_BINDING','MAX_RENDERBUFFER_SIZE',
	'INVALID_FRAMEBUFFER_OPERATION','UNPACK_FLIP_Y_WEBGL',
	'UNPACK_PREMULTIPLY_ALPHA_WEBGL','CONTEXT_LOST_WEBGL',
	'UNPACK_COLORSPACE_CONVERSION_WEBGL','BROWSER_DEFAULT_WEBGL',
	'PIXEL_PACK_BUFFER','PIXEL_UNPACK_BUFFER','PIXEL_PACK_BUFFER_BINDING',
	'PIXEL_UNPACK_BUFFER_BINDING',
];

const methods = [
	'init',
	'uniform1f','uniform2f','uniform3f','uniform4f',
	'uniform1i','uniform2i','uniform3i','uniform4i',
	'uniform1fv','uniform2fv','uniform3fv','uniform4fv',
	'uniform1iv','uniform2iv','uniform3iv','uniform4iv',
	'pixelStorei','bindAttribLocation','getError','drawArrays',
	'uniformMatrix2fv','uniformMatrix3fv','uniformMatrix4fv',
	'generateMipmap','getAttribLocation','depthFunc','viewport',
	'createShader','shaderSource','compileShader',
	'getShaderParameter','getShaderInfoLog',
	'createProgram','attachShader','linkProgram',
	'getProgramParameter','getUniformLocation',
	'clearColor','clearDepth','disable',
	'createTexture','bindTexture','texImage2D','texParameteri','texParameterf',
	'clear','useProgram',
	'createFramebuffer','bindFramebuffer','framebufferTexture2D',
	'createBuffer','bindBuffer','bufferData','bufferSubData',
	'enable','blendEquation','blendFunc',
	'enableVertexAttribArray','vertexAttribPointer',
	'activeTexture','drawElements','flush','finish',
	'vertexAttrib1f','vertexAttrib2f','vertexAttrib3f','vertexAttrib4f',
	'vertexAttrib1fv','vertexAttrib2fv','vertexAttrib3fv','vertexAttrib4fv',
	'blendColor','blendEquationSeparate','blendFuncSeparate',
	'clearStencil','colorMask',
	'copyTexImage2D','copyTexSubImage2D',
	'cullFace','depthMask','depthRange','disableVertexAttribArray',
	'hint','isEnabled','lineWidth','polygonOffset','scissor',
	'stencilFunc','stencilFuncSeparate','stencilMask',
	'stencilMaskSeparate','stencilOp','stencilOpSeparate',
	'bindRenderbuffer','createRenderbuffer',
	'deleteBuffer','deleteFramebuffer','deleteProgram','deleteRenderbuffer',
	'deleteShader','deleteTexture','detachShader',
	'framebufferRenderbuffer','getVertexAttribOffset',
	'isBuffer','isFramebuffer','isProgram','isRenderbuffer','isShader','isTexture',
	'renderbufferStorage','getShaderSource','validateProgram',
	'texSubImage2D','readPixels','getTexParameter',
	'getActiveAttrib','getActiveUniform','getAttachedShaders','getParameter',
	'getBufferParameter','getFramebufferAttachmentParameter','getProgramInfoLog',
	'getRenderbufferParameter','getVertexAttrib','getSupportedExtensions','getExtension',
	'checkFramebufferStatus','frontFace',
];


describe('WebGL', () => {
	it('exports an object', () => {
		expect(typeof webgl).toBe('object');
	});
	
	constants.forEach((constant) => {
		it(`#${constant} constant exposed`, () => {
			expect(webgl).toHaveProperty(constant);
		});
	});
	
	methods.forEach((method) => {
		it(`#${method}() method exposed`, () => {
			expect(typeof webgl[method]).toBe('function');
		});
	});
});
