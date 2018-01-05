'use strict';

const gl = require('../binary/webgl');

const Image = require('./image'); // jshint ignore: line


// WebGL constructors
gl.WebGLRenderingContext = function WebGLRenderingContext(_) { this._ = _; }
gl.WebGLProgram = function WebGLProgram(_) { this._ = _; }
gl.WebGLShader = function WebGLShader(_) { this._ = _; }
gl.WebGLBuffer = function WebGLBuffer(_) { this._ = _; }
gl.WebGLFramebuffer = function WebGLFramebuffer(_) { this._ = _; }
gl.WebGLRenderbuffer = function WebGLRenderbuffer(_) { this._ = _; }
gl.WebGLTexture = function WebGLTexture(_) { this._ = _; }
gl.WebGLUniformLocation = function WebGLUniformLocation(_) { this._ = _; }
gl.WebGLActiveInfo = function WebGLActiveInfo(_) {
	this._ = _;
	this.size = _.size;
	this.type = _.type;
	this.name = _.name;
}

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

////////////////////////////////////////////////////////////////////////////////


const _getSupportedExtensions = gl.getSupportedExtensions;
gl.getSupportedExtensions = () => _getSupportedExtensions().split(' ');


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
gl.deleteBuffer = (buffer) => _deleteBuffer(buffer ? buffer._ : 0);


const _deleteFramebuffer = gl.deleteFramebuffer;
gl.deleteFramebuffer = (framebuffer) => _deleteFramebuffer(framebuffer ? framebuffer._ : 0);


const _deleteProgram = gl.deleteProgram;
gl.deleteProgram = (program) => _deleteProgram(program ? program._ : 0);


const _deleteRenderbuffer = gl.deleteRenderbuffer;
gl.deleteRenderbuffer = (renderbuffer) => _deleteRenderbuffer(renderbuffer ? renderbuffer._ : 0);


const _deleteShader = gl.deleteShader;
gl.deleteShader = (shader) => _deleteShader(shader ? shader._ : 0);


const _deleteTexture = gl.deleteTexture;
gl.deleteTexture = (texture) => _deleteTexture(texture ? texture._ : 0);


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
gl.getAttachedShaders = (program) => _getAttachedShaders(program ? program._ : 0);


const _getAttribLocation = gl.getAttribLocation;
gl.getAttribLocation = (program, name) => _getAttribLocation(program ? program._ : 0, name);


const _getProgramParameter = gl.getProgramParameter;
gl.getProgramParameter = (program, pname) => _getProgramParameter(program ? program._ : 0, pname);

const _getProgramInfoLog = gl.getProgramInfoLog;
gl.getProgramInfoLog = (program) => _getProgramInfoLog(program ? program._ : 0);


const _getShaderParameter = gl.getShaderParameter;
gl.getShaderParameter = (shader, pname) => _getShaderParameter(shader ? shader._ : 0, pname);


const _getShaderInfoLog = gl.getShaderInfoLog;
gl.getShaderInfoLog = (shader) => _getShaderInfoLog(shader ? shader._ : 0);


const _getShaderSource = gl.getShaderSource;
gl.getShaderSource = (shader) => _getShaderSource(shader ? shader._ : 0);


const _getUniform = gl.getUniform;
gl.getUniform = (program, location) => _getUniform(program ? program._ : 0, location ? location._ : 0);


const _getUniformLocation = gl.getUniformLocation;
gl.getUniformLocation = (program, name) => new gl.WebGLUniformLocation(
	_getUniformLocation(program ? program._ : 0, name)
);


const _isBuffer = gl.isBuffer;
gl.isBuffer = (buffer) => _isBuffer(buffer ? buffer._ : 0);


const _isFramebuffer = gl.isFramebuffer;
gl.isFramebuffer = (framebuffer) => _isFramebuffer(framebuffer ? framebuffer._ : 0);


const _isProgram = gl.isProgram;
gl.isProgram = (program) => _isProgram(program ? program._ : 0);


const _isRenderbuffer = gl.isRenderbuffer;
gl.isRenderbuffer = (renderbuffer) => _isRenderbuffer(renderbuffer ? renderbuffer._ : 0);


const _isShader = gl.isShader;
gl.isShader = (shader) => _isShader(shader ? shader._ : 0);


const _isTexture = gl.isTexture;
gl.isTexture = (texture) => _isTexture(texture ? texture._ : 0);


const _linkProgram = gl.linkProgram;
gl.linkProgram = (program) => _linkProgram(program ? program._ : 0);


const _shaderSource = gl.shaderSource;
gl.shaderSource = (shader, source) => _shaderSource(shader ? shader._ : 0, source);


const _texImage2D = gl.texImage2D;
gl.texImage2D = (target, level, internalformat, width, height, border, format, type, pixels) => {
	if (arguments.length === 6) {
		// width is now format, height is now type, and border is now pixels
		pixels = border;
		type = height;
		format = width;
		return _texImage2D(target, level, internalformat, pixels.width, pixels.height, 0, format, type, pixels);
	} else if (arguments.length === 9) {
		return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	} else {
		throw new TypeError('Function texImage2D() takes 6 or 9 arguments.');
	}
}


const _uniform1f = gl.uniform1f;
gl.uniform1f = (location, x) => _uniform1f(location ? location._ : 0, x);


const _uniform1fv = gl.uniform1fv;
gl.uniform1fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform1fv(location ? location._ : 0, v);
}


const _uniform1i = gl.uniform1i;
gl.uniform1i = (location, x) => {
	if (c_pt(x, 'boolean')) {
		x = x ? 1 : 0;
	}
	return _uniform1i(location ? location._ : 0, x);
}

const _uniform1iv = gl.uniform1iv;
gl.uniform1iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform1iv(location ? location._ : 0, v);
}


const _uniform2f = gl.uniform2f;
gl.uniform2f = (location, x, y) => _uniform2f(location ? location._ : 0, x, y);


const _uniform2fv = gl.uniform2fv;
gl.uniform2fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform2fv(location ? location._ : 0, v);
}


const _uniform2i = gl.uniform2i;
gl.uniform2i = (location, x, y) => _uniform2i(location ? location._ : 0, x, y);


const _uniform2iv = gl.uniform2iv;
gl.uniform2iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform2iv(location ? location._ : 0, v);
}


const _uniform3f = gl.uniform3f;
gl.uniform3f = (location, x, y, z) => _uniform3f(location ? location._ : 0, x, y, z);



const _uniform3fv = gl.uniform3fv;
gl.uniform3fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform3fv(location ? location._ : 0, v);
}


const _uniform3i = gl.uniform3i;
gl.uniform3i = (location, x, y, z) => _uniform3i(location ? location._ : 0, x, y, z);


const _uniform3iv = gl.uniform3iv;
gl.uniform3iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform3iv(location ? location._ : 0, v);
}

const _uniform4f = gl.uniform4f;
gl.uniform4f = (location, x, y, z, w) => _uniform4f(location ? location._ : 0, x, y, z, w);


const _uniform4fv = gl.uniform4fv;
gl.uniform4fv = (location, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform4fv(location ? location._ : 0, v);
}

const _uniform4i = gl.uniform4i;
gl.uniform4i = (location, x, y, z, w) => _uniform4i(location ? location._ : 0, x, y, z, w);


const _uniform4iv = gl.uniform4iv;
gl.uniform4iv = (location, v) => {
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform4iv(location ? location._ : 0, v);
}

const _uniformMatrix2fv = gl.uniformMatrix2fv;
gl.uniformMatrix2fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix2fv(location ? location._ : 0, transpose, v);
}

const _uniformMatrix3fv = gl.uniformMatrix3fv;
gl.uniformMatrix3fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix3fv(location ? location._ : 0, transpose, v);
}

const _uniformMatrix4fv = gl.uniformMatrix4fv;
gl.uniformMatrix4fv = (location, transpose, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix4fv(location ? location._ : 0, transpose, v);
}

const _useProgram = gl.useProgram;
gl.useProgram = (program) => _useProgram(program ? program._ : 0);


const _validateProgram = gl.validateProgram;
gl.validateProgram = (program) => _validateProgram(program ? program._ : 0);


const _vertexAttrib1fv = gl.vertexAttrib1fv;
gl.vertexAttrib1fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib1fv(indx, v);
}

const _vertexAttrib2fv = gl.vertexAttrib2fv;
gl.vertexAttrib2fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib2fv(indx, v);
}

const _vertexAttrib3fv = gl.vertexAttrib3fv;
gl.vertexAttrib3fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib3fv(indx, v);
}

const _vertexAttrib4fv = gl.vertexAttrib4fv;
gl.vertexAttrib4fv = (indx, v) => {
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib4fv(indx, v);
}

const _viewport = gl.viewport;
gl.viewport = (x, y, width, height) => _viewport(x, y, width, height);
