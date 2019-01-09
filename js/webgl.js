'use strict';

const gl = require('../core');


// WebGL constructors
gl.WebGLRenderingContext = function WebGLRenderingContext(_) { this._ = _; };
gl.WebGLProgram = function WebGLProgram(_) { this._ = _; };
gl.WebGLShader = function WebGLShader(_) { this._ = _; };
gl.WebGLBuffer = function WebGLBuffer(_) { this._ = _; };
gl.WebGLFramebuffer = function WebGLFramebuffer(_) { this._ = _; };
gl.WebGLRenderbuffer = function WebGLRenderbuffer(_) { this._ = _; };
gl.WebGLTexture = function WebGLTexture(_) { this._ = _; };
gl.WebGLUniformLocation = function WebGLUniformLocation(_) { this._ = _; };
gl.WebGLActiveInfo = function WebGLActiveInfo(_) {
	this._ = _;
	this.size = _.size;
	this.type = _.type;
	this.name = _.name;
};

// Global scope constructors for browser-style libs
global.WebGLRenderingContext = gl.WebGLRenderingContext;
global.WebGLProgram = gl.WebGLProgram;
global.WebGLShader = gl.WebGLShader;
global.WebGLBuffer = gl.WebGLBuffer;
global.WebGLFramebuffer = gl.WebGLFramebuffer;
global.WebGLRenderbuffer = gl.WebGLRenderbuffer;
global.WebGLTexture = gl.WebGLTexture;
global.WebGLUniformLocation = gl.WebGLUniformLocation;
global.WebGLActiveInfo = gl.WebGLActiveInfo;


module.exports = gl;


const extensions = {
	'ANGLE_instanced_arrays': {
		'VERTEX_ATTRIB_ARRAY_DIVISOR_ANGLE' : 0x88FE,
		drawArraysInstancedANGLE() {},
		drawElementsInstancedANGLE() {},
		vertexAttribDivisorANGLE() {},
	},
	'EXT_blend_minmax': {
		'MIN_EXT' : 0x8007,
		'MAX_EXT' : 0x8008,
	},
	'EXT_color_buffer_float': {},
	'EXT_color_buffer_half_float': {
		'RGBA16F_EXT' : 0x881A,
		'RGB16F_EXT' : 0x881B,
		'FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT' : 0x8211,
		'UNSIGNED_NORMALIZED_EXT' : 0x8C17,
	},
	'EXT_disjoint_timer_query': {
		'QUERY_COUNTER_BITS_EXT' : 0x8864,
		'CURRENT_QUERY_EXT' : 0x8865,
		'QUERY_RESULT_EXT' : 0x8866,
		'QUERY_RESULT_AVAILABLE_EXT' : 0x8867,
		'TIME_ELAPSED_EXT' : 0x88BF,
		'TIMESTAMP_EXT' : 0x8E28,
		'GPU_DISJOINT_EXT' : 0x8FBB,
		createQueryEXT() {},
		deleteQueryEXT() {},
		isQueryEXT() {},
		beginQueryEXT() {},
		endQueryEXT() {},
		queryCounterEXT() {},
		getQueryEXT() {},
		getQueryObjectEXT() {},
	},
	'EXT_frag_depth': {},
	'EXT_sRGB': {
		'SRGB_EXT' : 0x8C40,
		'SRGB_ALPHA_EXT' : 0x8C42,
		'SRGB8_ALPHA8_EXT' : 0x8C43,
		'FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING_EXT' : 0x8210,
	},
	'EXT_shader_texture_lod': {},
	'EXT_texture_filter_anisotropic': {
		'MAX_TEXTURE_MAX_ANISOTROPY_EXT' : 0x84FF,
		'TEXTURE_MAX_ANISOTROPY_EXT' : 0x84FE,
	},
	'OES_element_index_uint': {},
	'OES_standard_derivatives': {
		'FRAGMENT_SHADER_DERIVATIVE_HINT_OES'	: 0x8B8B,
	},
	'OES_texture_float': {},
	'OES_texture_float_linear': {},
	'OES_texture_half_float': {
		'HALF_FLOAT_OES' : 0x8D61,
	},
	'OES_texture_half_float_linear': {},
	'OES_vertex_array_object': {
		'VERTEX_ARRAY_BINDING_OES' : 0x85B5,
	},
	'WEBGL_color_buffer_float': {
		'RGBA32F_EXT' : 0x8814,
		'RGB32F_EXT' : 0x8815,
		'FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE_EXT' : 0x8211,
		'UNSIGNED_NORMALIZED_EXT' : 0x8C17,
	},
	'WEBGL_compressed_texture_astc': {
		getSupportedProfiles() {},
		'COMPRESSED_RGBA_ASTC_4x4_KHR' : 0x93B0,
		'COMPRESSED_RGBA_ASTC_5x4_KHR' : 0x93B1,
		'COMPRESSED_RGBA_ASTC_5x5_KHR' : 0x93B2,
		'COMPRESSED_RGBA_ASTC_6x5_KHR' : 0x93B3,
		'COMPRESSED_RGBA_ASTC_6x6_KHR' : 0x93B4,
		'COMPRESSED_RGBA_ASTC_8x5_KHR' : 0x93B5,
		'COMPRESSED_RGBA_ASTC_8x6_KHR' : 0x93B6,
		'COMPRESSED_RGBA_ASTC_8x8_KHR' : 0x93B7,
		'COMPRESSED_RGBA_ASTC_10x5_KHR' : 0x93B8,
		'COMPRESSED_RGBA_ASTC_10x6_KHR' : 0x93B9,
		'COMPRESSED_RGBA_ASTC_10x8_KHR' : 0x93BA,
		'COMPRESSED_RGBA_ASTC_10x10_KHR' : 0x93BB,
		'COMPRESSED_RGBA_ASTC_12x10_KHR' : 0x93BC,
		'COMPRESSED_RGBA_ASTC_12x12_KHR' : 0x93BD,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_4x4_KHR' : 0x93D0,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_5x4_KHR' : 0x93D1,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_5x5_KHR' : 0x93D2,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_6x5_KHR' : 0x93D3,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_6x6_KHR' : 0x93D4,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_8x5_KHR' : 0x93D5,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_8x6_KHR' : 0x93D6,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_8x8_KHR' : 0x93D7,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_10x5_KHR' : 0x93D8,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_10x6_KHR' : 0x93D9,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_10x8_KHR' : 0x93DA,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_10x10_KHR' : 0x93DB,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_12x10_KHR' : 0x93DC,
		'COMPRESSED_SRGB8_ALPHA8_ASTC_12x12_KHR' : 0x93DD,
	},
	'WEBGL_compressed_texture_atc': {
		'COMPRESSED_RGB_ATC_WEBGL' : 0x8C92,
		'COMPRESSED_RGBA_ATC_EXPLICIT_ALPHA_WEBGL' : 0x8C92,
		'COMPRESSED_RGBA_ATC_INTERPOLATED_ALPHA_WEBGL' : 0x87EE,
	},
	'WEBGL_compressed_texture_etc': {
		'COMPRESSED_R11_EAC' : 0x9270,
		'COMPRESSED_SIGNED_R11_EAC' : 0x9271,
		'COMPRESSED_RG11_EAC' : 0x9272,
		'COMPRESSED_SIGNED_RG11_EAC' : 0x9273,
		'COMPRESSED_RGB8_ETC2' : 0x9274,
		'COMPRESSED_RGBA8_ETC2_EAC' : 0x9275,
		'COMPRESSED_SRGB8_ETC2' : 0x9276,
		'COMPRESSED_SRGB8_ALPHA8_ETC2_EAC' : 0x9277,
		'COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2' : 0x9278,
		'COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2' : 0x9279,
	},
	'WEBGL_compressed_texture_etc1': {
		'COMPRESSED_RGB_ETC1_WEBGL' : 0x8D64,
	},
	'WEBGL_compressed_texture_pvrtc': {
		'COMPRESSED_RGB_PVRTC_4BPPV1_IMG' : 0x8C00,
		'COMPRESSED_RGBA_PVRTC_4BPPV1_IMG' : 0x8C02,
		'COMPRESSED_RGB_PVRTC_2BPPV1_IMG' : 0x8C01,
		'COMPRESSED_RGBA_PVRTC_2BPPV1_IMG' : 0x8C03,
	},
	'WEBGL_compressed_texture_s3tc': {
		'COMPRESSED_RGB_S3TC_DXT1_EXT' : 0x83F0,
		'COMPRESSED_RGBA_S3TC_DXT1_EXT' : 0x83F1,
		'COMPRESSED_RGBA_S3TC_DXT3_EXT' : 0x83F2,
		'COMPRESSED_RGBA_S3TC_DXT5_EXT' : 0x83F3,
	},
	'WEBGL_compressed_texture_s3tc_srgb': {
		'COMPRESSED_SRGB_S3TC_DXT1_EXT' : 0x8C4C,
		'COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT' : 0x8C4D,
		'COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT' : 0x8C4E,
		'COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT' : 0x8C4F,
	},
	'WEBGL_debug_renderer_info': {
		'UNMASKED_VENDOR_WEBGL' : 0x9245,
		'UNMASKED_RENDERER_WEBGL' : 0x9246,
	},
	'WEBGL_debug_shaders': {
		getTranslatedShaderSource() {},
	},
	'WEBGL_depth_texture': {
		'UNSIGNED_INT_24_8_WEBGL' : 0x84FA,
	},
	'WEBGL_draw_buffers': {
		'COLOR_ATTACHMENT0_WEBGL' : 0x8CE0,
		'COLOR_ATTACHMENT1_WEBGL' : 0x8CE1,
		'COLOR_ATTACHMENT2_WEBGL' : 0x8CE2,
		'COLOR_ATTACHMENT3_WEBGL' : 0x8CE3,
		'COLOR_ATTACHMENT4_WEBGL' : 0x8CE4,
		'COLOR_ATTACHMENT5_WEBGL' : 0x8CE5,
		'COLOR_ATTACHMENT6_WEBGL' : 0x8CE6,
		'COLOR_ATTACHMENT7_WEBGL' : 0x8CE7,
		'COLOR_ATTACHMENT8_WEBGL' : 0x8CE8,
		'COLOR_ATTACHMENT9_WEBGL' : 0x8CE9,
		'COLOR_ATTACHMENT10_WEBGL' : 0x8CEA,
		'COLOR_ATTACHMENT11_WEBGL' : 0x8CEB,
		'COLOR_ATTACHMENT12_WEBGL' : 0x8CEC,
		'COLOR_ATTACHMENT13_WEBGL' : 0x8CED,
		'COLOR_ATTACHMENT14_WEBGL' : 0x8CEE,
		'COLOR_ATTACHMENT15_WEBGL' : 0x8CEF,
		'DRAW_BUFFER0_WEBGL' : 0x8825,
		'DRAW_BUFFER1_WEBGL' : 0x8826,
		'DRAW_BUFFER2_WEBGL' : 0x8827,
		'DRAW_BUFFER3_WEBGL' : 0x8828,
		'DRAW_BUFFER4_WEBGL' : 0x8829,
		'DRAW_BUFFER5_WEBGL' : 0x882A,
		'DRAW_BUFFER6_WEBGL' : 0x882B,
		'DRAW_BUFFER7_WEBGL' : 0x882C,
		'DRAW_BUFFER8_WEBGL' : 0x882D,
		'DRAW_BUFFER9_WEBGL' : 0x882E,
		'DRAW_BUFFER10_WEBGL' : 0x882F,
		'DRAW_BUFFER11_WEBGL' : 0x8830,
		'DRAW_BUFFER12_WEBGL' : 0x8831,
		'DRAW_BUFFER13_WEBGL' : 0x8832,
		'DRAW_BUFFER14_WEBGL' : 0x8833,
		'DRAW_BUFFER15_WEBGL' : 0x8834,
		'MAX_COLOR_ATTACHMENTS_WEBGL' : 0x8CDF,
		'MAX_DRAW_BUFFERS_WEBGL' : 0x8824,
	},
	'WEBGL_lose_context': {
		loseContext() {},
		restoreContext() {},
	},
};

const _getSupportedExtensions = gl.getSupportedExtensions;
gl.getSupportedExtensions = () => {
	gl._realExtensions = _getSupportedExtensions();
	return Object.keys(extensions);
};

gl.getExtension = name => {
	return extensions[name];
};


////////////////////////////////////////////////////////////////////////////////

const _getParameter = gl.getParameter;
gl.getParameter = pname => pname === gl.VERSION ? 'WebGL 1.0' : _getParameter(pname);


const _attachShader = gl.attachShader;
gl.attachShader = (program, shader) => _attachShader(
	program ? program._ : 0, shader ? shader._ : 0
);


const _bindAttribLocation = gl.bindAttribLocation;
gl.bindAttribLocation = (program, index, name) => _bindAttribLocation(
	program ? program._ : 0, index, name
);


const _bindBuffer = gl.bindBuffer;
gl.bindBuffer = (target, buffer) => _bindBuffer(target, buffer ? buffer._ : 0);


const _bindFramebuffer = gl.bindFramebuffer;
gl.bindFramebuffer = (target, framebuffer) => _bindFramebuffer(target, framebuffer ? framebuffer._ : 0);


const _bindRenderbuffer = gl.bindRenderbuffer;
gl.bindRenderbuffer = (target, renderbuffer) => _bindRenderbuffer(target, renderbuffer ? renderbuffer._ : 0);


const _bindTexture = gl.bindTexture;
gl.bindTexture = (target, texture) => _bindTexture(target, texture ? texture._ : 0);


const _compileShader = gl.compileShader;
gl.compileShader = shader => _compileShader(shader ? shader._ : 0);


const _createBuffer = gl.createBuffer;
gl.createBuffer = () => new gl.WebGLBuffer(_createBuffer());


const _createFramebuffer = gl.createFramebuffer;
gl.createFramebuffer = () => new gl.WebGLFramebuffer(_createFramebuffer());


const _createProgram = gl.createProgram;
gl.createProgram = () => new gl.WebGLProgram(_createProgram());


const _createRenderbuffer = gl.createRenderbuffer;
gl.createRenderbuffer = () => new gl.WebGLRenderbuffer(_createRenderbuffer());


const _createShader = gl.createShader;
gl.createShader = type => new gl.WebGLShader(_createShader(type));


const _createTexture = gl.createTexture;
gl.createTexture = () => new gl.WebGLTexture(_createTexture());


const _deleteBuffer = gl.deleteBuffer;
gl.deleteBuffer = buffer => _deleteBuffer(buffer ? buffer._ : 0);


const _deleteFramebuffer = gl.deleteFramebuffer;
gl.deleteFramebuffer = framebuffer => _deleteFramebuffer(framebuffer ? framebuffer._ : 0);


const _deleteProgram = gl.deleteProgram;
gl.deleteProgram = program => _deleteProgram(program ? program._ : 0);


const _deleteRenderbuffer = gl.deleteRenderbuffer;
gl.deleteRenderbuffer = renderbuffer => _deleteRenderbuffer(renderbuffer ? renderbuffer._ : 0);


const _deleteShader = gl.deleteShader;
gl.deleteShader = shader => _deleteShader(shader ? shader._ : 0);


const _deleteTexture = gl.deleteTexture;
gl.deleteTexture = texture => _deleteTexture(texture ? texture._ : 0);


const _detachShader = gl.detachShader;
gl.detachShader = (program, shader) => _detachShader(program ? program._ : 0, shader ? shader._ : 0);


const _framebufferRenderbuffer = gl.framebufferRenderbuffer;
gl.framebufferRenderbuffer = (
	target, attachment, renderbuffertarget, renderbuffer
) => _framebufferRenderbuffer(
	target, attachment, renderbuffertarget, renderbuffer ? renderbuffer._ : 0
);


const _framebufferTexture2D = gl.framebufferTexture2D;
gl.framebufferTexture2D = (
	target, attachment, textarget, texture, level
) => _framebufferTexture2D(
	target, attachment, textarget, texture ? texture._ : 0, level
);


const _getActiveAttrib = gl.getActiveAttrib;
gl.getActiveAttrib = (program, index) => new gl.WebGLActiveInfo(
	_getActiveAttrib(program ? program._ : 0, index)
);


const _getActiveUniform = gl.getActiveUniform;
gl.getActiveUniform = (program, index) => new gl.WebGLActiveInfo(
	_getActiveUniform(program ? program._ : 0, index)
);


const _getAttachedShaders = gl.getAttachedShaders;
gl.getAttachedShaders = program => _getAttachedShaders(program ? program._ : 0);


const _getAttribLocation = gl.getAttribLocation;
gl.getAttribLocation = (program, name) => _getAttribLocation(program ? program._ : 0, name);


const _getProgramParameter = gl.getProgramParameter;
gl.getProgramParameter = (program, pname) => _getProgramParameter(program ? program._ : 0, pname);

const _getProgramInfoLog = gl.getProgramInfoLog;
gl.getProgramInfoLog = program => _getProgramInfoLog(program ? program._ : 0);


const _getShaderParameter = gl.getShaderParameter;
gl.getShaderParameter = (shader, pname) => _getShaderParameter(shader ? shader._ : 0, pname);


const _getShaderInfoLog = gl.getShaderInfoLog;
gl.getShaderInfoLog = shader => _getShaderInfoLog(shader ? shader._ : 0);


const _getShaderSource = gl.getShaderSource;
gl.getShaderSource = shader => _getShaderSource(shader ? shader._ : 0);


const _getUniform = gl.getUniform;
gl.getUniform = (program, location) => _getUniform(program ? program._ : 0, location ? location._ : 0);


const _getUniformLocation = gl.getUniformLocation;
gl.getUniformLocation = (program, name) => new gl.WebGLUniformLocation(
	_getUniformLocation(program ? program._ : 0, name)
);


const _isBuffer = gl.isBuffer;
gl.isBuffer = buffer => _isBuffer(buffer ? buffer._ : 0);


const _isFramebuffer = gl.isFramebuffer;
gl.isFramebuffer = framebuffer => _isFramebuffer(framebuffer ? framebuffer._ : 0);


const _isProgram = gl.isProgram;
gl.isProgram = program => _isProgram(program ? program._ : 0);


const _isRenderbuffer = gl.isRenderbuffer;
gl.isRenderbuffer = renderbuffer => _isRenderbuffer(renderbuffer ? renderbuffer._ : 0);


const _isShader = gl.isShader;
gl.isShader = shader => _isShader(shader ? shader._ : 0);


const _isTexture = gl.isTexture;
gl.isTexture = texture => _isTexture(texture ? texture._ : 0);


const _linkProgram = gl.linkProgram;
gl.linkProgram = program => _linkProgram(program ? program._ : 0);


const _shaderSource = gl.shaderSource;
gl.shaderSource = (shader, source) => _shaderSource(shader ? shader._ : 0, source);


const _texImage2D = gl.texImage2D;
gl.texImage2D = function (
	target, level, internalformat, width, height, border, format, type, pixels
) {
	
	if (arguments.length === 6) {
		// width is now format, height is now type, and border is now pixels
		pixels = border;
		type = height;
		format = width;
		return _texImage2D(
			target, level, internalformat, pixels.width, pixels.height, 0, format, type, pixels
		);
	}
	
	if (arguments.length === 9) {
		return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}
	
	throw new TypeError('Function texImage2D() takes 6 or 9 arguments.');
	
};


const _uniform1f = gl.uniform1f;
gl.uniform1f = (location, x) => _uniform1f(location ? location._ : 0, x);


const _uniform1fv = gl.uniform1fv;
gl.uniform1fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform1fv(location ? location._ : 0, v);
};


const _pixelStorei = gl.pixelStorei;
gl.pixelStorei = (pname, param) =>_pixelStorei(
	pname, typeof param === 'boolean' ? (param ? 1 : 0) : param
);


const _uniform1i = gl.uniform1i;
gl.uniform1i = (location, x) => _uniform1i(
	location ? location._ : 0, typeof x === 'boolean' ? (x ? 1 : 0) : x
);


const _uniform1iv = gl.uniform1iv;
gl.uniform1iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform1iv(location ? location._ : 0, v);
};


const _uniform2f = gl.uniform2f;
gl.uniform2f = (location, x, y) => _uniform2f(location ? location._ : 0, x, y);


const _uniform2fv = gl.uniform2fv;
gl.uniform2fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform2fv(location ? location._ : 0, v);
};


const _uniform2i = gl.uniform2i;
gl.uniform2i = (location, x, y) => _uniform2i(location ? location._ : 0, x, y);


const _uniform2iv = gl.uniform2iv;
gl.uniform2iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform2iv(location ? location._ : 0, v);
};


const _uniform3f = gl.uniform3f;
gl.uniform3f = (location, x, y, z) => _uniform3f(location ? location._ : 0, x, y, z);



const _uniform3fv = gl.uniform3fv;
gl.uniform3fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform3fv(location ? location._ : 0, v);
};


const _uniform3i = gl.uniform3i;
gl.uniform3i = (location, x, y, z) => _uniform3i(location ? location._ : 0, x, y, z);


const _uniform3iv = gl.uniform3iv;
gl.uniform3iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform3iv(location ? location._ : 0, v);
};

const _uniform4f = gl.uniform4f;
gl.uniform4f = (location, x, y, z, w) => _uniform4f(location ? location._ : 0, x, y, z, w);


const _uniform4fv = gl.uniform4fv;
gl.uniform4fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform4fv(location ? location._ : 0, v);
};

const _uniform4i = gl.uniform4i;
gl.uniform4i = (location, x, y, z, w) => _uniform4i(location ? location._ : 0, x, y, z, w);


const _uniform4iv = gl.uniform4iv;
gl.uniform4iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform4iv(location ? location._ : 0, v);
};

const _uniformMatrix2fv = gl.uniformMatrix2fv;
gl.uniformMatrix2fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix2fv(location ? location._ : 0, transpose, v);
};

const _uniformMatrix3fv = gl.uniformMatrix3fv;
gl.uniformMatrix3fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix3fv(location ? location._ : 0, transpose, v);
};

const _uniformMatrix4fv = gl.uniformMatrix4fv;
gl.uniformMatrix4fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix4fv(location ? location._ : 0, transpose, v);
};

const _useProgram = gl.useProgram;
gl.useProgram = program => _useProgram(program ? program._ : 0);


const _validateProgram = gl.validateProgram;
gl.validateProgram = program => _validateProgram(program ? program._ : 0);


const _vertexAttrib1fv = gl.vertexAttrib1fv;
gl.vertexAttrib1fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib1fv(indx, v);
};

const _vertexAttrib2fv = gl.vertexAttrib2fv;
gl.vertexAttrib2fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib2fv(indx, v);
};

const _vertexAttrib3fv = gl.vertexAttrib3fv;
gl.vertexAttrib3fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib3fv(indx, v);
};

const _vertexAttrib4fv = gl.vertexAttrib4fv;
gl.vertexAttrib4fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib4fv(indx, v);
};

const _viewport = gl.viewport;
gl.viewport = (x, y, width, height) => _viewport(x, y, width, height);
