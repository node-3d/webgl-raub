'use strict';

const platformPaths = {
	win32  : '../bin_windows/webgl',
	linux  : '../bin_linux/webgl'  ,
	darwin : '../bin_darwin/webgl' ,
};

const binPath = platformPaths[process.platform];

const gl = require(binPath);
module.exports = gl;


const Image = require('./image'); // jshint ignore: line


gl.WebGLProgram         = function (_) { this._ = _; }
gl.WebGLShader          = function (_) { this._ = _; }
gl.WebGLBuffer          = function (_) { this._ = _; }
gl.WebGLFramebuffer     = function (_) { this._ = _; }
gl.WebGLRenderbuffer    = function (_) { this._ = _; }
gl.WebGLTexture         = function (_) { this._ = _; }
gl.WebGLActiveInfo      = function (_) { this._=_; this.size=_.size; this.type=_.type; this.name=_.name; }
gl.WebGLUniformLocation = function (_) { this._ = _; }

global.WebGLRenderingContext = function(_) { this._ = _; }
global.WebGLProgram          = gl.WebGLProgram;
global.WebGLShader           = gl.WebGLShader;
global.WebGLBuffer           = gl.WebGLBuffer;
global.WebGLFramebuffer      = gl.WebGLFramebuffer;
global.WebGLRenderbuffer     = gl.WebGLRenderbuffer;
global.WebGLTexture          = gl.WebGLTexture;
global.WebGLActiveInfo       = gl.WebGLActiveInfo;
global.WebGLUniformLocation  = gl.WebGLUniformLocation;

////////////////////////////////////////////////////////////////////////////////

const c_al = (a, l) => a.length === l;
const c_pt = (p, t) => typeof p === t;
const c_pi = (p, c) => p === null || p instanceof c;



const _getSupportedExtensions = gl.getSupportedExtensions;
gl.getSupportedExtensions = function getSupportedExtensions() {
	return _getSupportedExtensions().split(' ');
}

const _getExtension = gl.getExtension;
gl.getExtension = function getExtension(name) {
	if ( ! (
			c_al(arguments, 1) && c_pt(name, 'string')
		) ) {
		throw new TypeError('Expected getExtension(string name)');
	}
	return _getExtension(name);
}

const _activeTexture = gl.activeTexture;
gl.activeTexture = function activeTexture(texture) {
	if ( ! (
			c_al(arguments, 1) && c_pt(texture, 'number')
		) ) {
		throw new TypeError('Expected activeTexture(number texture)');
	}
	return _activeTexture(texture);
}

const _attachShader = gl.attachShader;
gl.attachShader = function attachShader(program, shader) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected attachShader(WebGLProgram program, WebGLShader shader)');
	}
	return _attachShader(program ? program._ : 0, shader ? shader._ : 0);
}

const _bindAttribLocation = gl.bindAttribLocation;
gl.bindAttribLocation = function bindAttribLocation(program, index, name) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(index, 'number') && c_pt(name, 'string')
		) ) {
		throw new TypeError(
			'Expected bindAttribLocation(WebGLProgram program, number index, string name)'
		);
	}
	return _bindAttribLocation(program ? program._ : 0, index, name);
}

const _bindBuffer = gl.bindBuffer;
gl.bindBuffer = function bindBuffer(target, buffer) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pt(target, 'number') && c_pi(buffer, gl.WebGLBuffer)
		) ) {
		throw new TypeError('Expected bindBuffer(number target, WebGLBuffer buffer)');
	}
	return _bindBuffer(target, buffer ? buffer._ : 0);
}

const _bindFramebuffer = gl.bindFramebuffer;
gl.bindFramebuffer = function bindFramebuffer(target, framebuffer) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pt(target, 'number') &&
			c_pi(framebuffer, gl.WebGLFramebuffer)
		) ) {
		throw new TypeError(
			'Expected bindFramebuffer(number target, WebGLFramebuffer framebuffer)'
		);
	}
	return _bindFramebuffer(target, framebuffer ? framebuffer._ : 0);
}

const _bindRenderbuffer = gl.bindRenderbuffer;
gl.bindRenderbuffer = function bindRenderbuffer(target, renderbuffer) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pt(target, 'number') &&
			c_pi(renderbuffer, gl.WebGLRenderbuffer)
		) ) {
		throw new TypeError(
			'Expected bindRenderbuffer(number target, WebGLRenderbuffer renderbuffer)'
		);
	}
	return _bindRenderbuffer(target, renderbuffer ? renderbuffer._ : 0);
}

const _bindTexture = gl.bindTexture;
gl.bindTexture = function bindTexture(target, texture) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pt(target, 'number') &&
			c_pi(texture, gl.WebGLTexture)
		) ) {
		throw new TypeError('Expected bindTexture(number target, WebGLTexture texture)');
	}
	return _bindTexture(target, texture ? texture._ : 0);
}

const _blendColor = gl.blendColor;
gl.blendColor = function blendColor(red, green, blue, alpha) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(red, 'number') &&
			c_pt(green, 'number') && c_pt(blue, 'number') && c_pt(alpha, 'number')
		) ) {
		throw new TypeError(
			'Expected blendColor(number red, number green, number blue, number alpha)'
		);
	}
	return _blendColor(red, green, blue, alpha);
}

const _blendEquation = gl.blendEquation;
gl.blendEquation = function blendEquation(mode) {
	if ( ! (c_al(arguments, 1) && c_pt(mode, 'number')) ) {
		throw new TypeError('Expected blendEquation(number mode)');
	}
	return _blendEquation(mode);
}

const _blendEquationSeparate = gl.blendEquationSeparate;
gl.blendEquationSeparate = function blendEquationSeparate(modeRGB, modeAlpha) {
	if ( ! (
			c_al(arguments, 2) && c_pt(modeRGB, 'number') && c_pt(modeAlpha, 'number')
		) ) {
		throw new TypeError(
			'Expected blendEquationSeparate(number modeRGB, number modeAlpha)'
		);
	}
	return _blendEquationSeparate(modeRGB, modeAlpha);
}

const _blendFunc = gl.blendFunc;
gl.blendFunc = function blendFunc(sfactor, dfactor) {
	if ( ! (
			c_al(arguments, 2) && c_pt(sfactor, 'number') && c_pt(dfactor, 'number')
		) ) {
		throw new TypeError('Expected blendFunc(number sfactor, number dfactor)');
	}
	return _blendFunc(sfactor, dfactor);
}

const _blendFuncSeparate = gl.blendFuncSeparate;
gl.blendFuncSeparate = function blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(srcRGB, 'number') && c_pt(dstRGB, 'number') &&
			c_pt(srcAlpha, 'number') && c_pt(dstAlpha, 'number')
		) ) {
		throw new TypeError(
			'Expected blendFuncSeparate(number srcRGB, number ' +
			'dstRGB, number srcAlpha, number dstAlpha)'
		);
	}
	return _blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

const _bufferData = gl.bufferData;
gl.bufferData = function bufferData(target, data, usage) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pt(target, 'number') &&
			(c_pt(data, 'object') || c_pt(data, 'number')) &&
			c_pt(usage, 'number')
		) ) {
		throw new TypeError(
			'Expected bufferData(number target, ArrayBuffer data, number usage) ' +
			'or bufferData(number target, number size, number usage)'
		);
	}
	return _bufferData(target, data, usage);
}

const _bufferSubData = gl.bufferSubData;
gl.bufferSubData = function bufferSubData(target, offset, data) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pt(target, 'number') && c_pt(offset, 'number') && c_pt(data, 'object')
		) ) {
		throw new TypeError(
			'Expected bufferSubData(number target, number offset, ArrayBuffer data)'
		);
	}
	return _bufferSubData(target, offset, data);
}

const _checkFramebufferStatus = gl.checkFramebufferStatus;
gl.checkFramebufferStatus = function checkFramebufferStatus(target) {
	if ( ! (
			c_al(arguments, 1) && c_pt(target, 'number')
		) ) {
		throw new TypeError('Expected checkFramebufferStatus(number target)');
	}
	return _checkFramebufferStatus(target);
}

const _clear = gl.clear;
gl.clear = function clear(mask) {
	if ( ! (
			c_al(arguments, 1) && c_pt(mask, 'number')
		) ) {
		throw new TypeError('Expected clear(number mask)');
	}
	return _clear(mask);
}

const _clearColor = gl.clearColor;
gl.clearColor = function clearColor(red, green, blue, alpha) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(red, 'number') && c_pt(green, 'number') &&
			c_pt(blue, 'number') && c_pt(alpha, 'number')
		) ) {
		throw new TypeError(
			'Expected clearColor(number red, number green, number blue, number alpha)'
		);
	}
	return _clearColor(red, green, blue, alpha);
}

const _clearDepth = gl.clearDepth;
gl.clearDepth = function clearDepth(depth) {
	if ( ! (
			c_al(arguments, 1) && c_pt(depth, 'number')
		) ) {
		throw new TypeError('Expected clearDepth(number depth)');
	}
	return _clearDepth(depth);
}

const _clearStencil = gl.clearStencil;
gl.clearStencil = function clearStencil(s) {
	if ( ! (
			c_al(arguments, 1) && c_pt(s, 'number')
		) ) {
		throw new TypeError('Expected clearStencil(number s)');
	}
	return _clearStencil(s);
}

const _colorMask = gl.colorMask;
gl.colorMask = function colorMask(red, green, blue, alpha) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(red, 'boolean') &&
			c_pt(green, 'boolean') &&
			c_pt(blue, 'boolean') &&
			c_pt(alpha, 'boolean')
		) ) {
		throw new TypeError('Expected colorMask(boolean red, boolean green, boolean blue, boolean alpha)');
	}
	return _colorMask(red, green, blue, alpha);
}

const _compileShader = gl.compileShader;
gl.compileShader = function compileShader(shader) {
	if ( ! (
			c_al(arguments, 1) && c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected compileShader(WebGLShader shader)');
	}
	return _compileShader(shader ? shader._ : 0);
}

const _copyTexImage2D = gl.copyTexImage2D;
gl.copyTexImage2D = function copyTexImage2D(target, level, internalformat, x, y, width, height, border) {
	if ( ! (
			c_al(arguments, 8) &&
			c_pt(target, 'number') &&
			c_pt(level, 'number') &&
			c_pt(internalformat, 'number') &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(width, 'number') && c_pt(height, 'number') &&
			c_pt(border, 'number')
		) ) {
		throw new TypeError(
			'Expected copyTexImage2D(number target, number level, number ' +
			'internalformat, number x, number y, number width, number height, number border)'
		);
	}
	return _copyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

const _copyTexSubImage2D = gl.copyTexSubImage2D;
gl.copyTexSubImage2D = function copyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height) {
	if ( ! (
			c_al(arguments, 8) &&
			c_pt(target, 'number') &&
			c_pt(level, 'number') &&
			c_pt(xoffset, 'number') &&
			c_pt(yoffset, 'number') &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(width, 'number') && c_pt(height, 'number')
		) ) {
		throw new TypeError(
			'Expected copyTexSubImage2D(number target, number level, number ' +
			'xoffset, number yoffset, number x, number y, number width, number height)'
		);
	}
	return _copyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

const _createBuffer = gl.createBuffer;
gl.createBuffer = function createBuffer() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected createBuffer()');
	}
	return new gl.WebGLBuffer(_createBuffer());
}

const _createFramebuffer = gl.createFramebuffer;
gl.createFramebuffer = function () {
	if (arguments.length !== 0) {
		throw new TypeError('Expected createFramebuffer()');
	}
	return new gl.WebGLFramebuffer(_createFramebuffer());
}

const _createProgram = gl.createProgram;
gl.createProgram = function createProgram() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected createProgram()');
	}
	return new gl.WebGLProgram(_createProgram());
}

const _createRenderbuffer = gl.createRenderbuffer;
gl.createRenderbuffer = function createRenderbuffer() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected createRenderbuffer()');
	}
	return new gl.WebGLRenderbuffer(_createRenderbuffer());
}

const _createShader = gl.createShader;
gl.createShader = function createShader(type) {
	if ( ! (
			c_al(arguments, 1) && c_pt(type, 'number')
		) ) {
		throw new TypeError('Expected createShader(number type)');
	}
	return new gl.WebGLShader(_createShader(type));
}

const _createTexture = gl.createTexture;
gl.createTexture = function createTexture() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected createTexture()');
	}
	return new gl.WebGLTexture(_createTexture());
}

const _cullFace = gl.cullFace;
gl.cullFace = function cullFace(mode) {
	if ( ! (
			c_al(arguments, 1) && c_pt(mode, 'number')
		) ) {
		throw new TypeError('Expected cullFace(number mode)');
	}
	return _cullFace(mode);
}

const _deleteBuffer = gl.deleteBuffer;
gl.deleteBuffer = function deleteBuffer(buffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(buffer, gl.WebGLBuffer)
		) ) {
		throw new TypeError('Expected deleteBuffer(WebGLBuffer buffer)');
	}
	return _deleteBuffer(buffer ? buffer._ : 0);
}

const _deleteFramebuffer = gl.deleteFramebuffer;
gl.deleteFramebuffer = function deleteFramebuffer(framebuffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(framebuffer, gl.WebGLFramebuffer)
		) ) {
		throw new TypeError('Expected deleteFramebuffer(WebGLFramebuffer framebuffer)');
	}
	return _deleteFramebuffer(framebuffer ? framebuffer._ : 0);
}

const _deleteProgram = gl.deleteProgram;
gl.deleteProgram = function deleteProgram(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected deleteProgram(WebGLProgram program)');
	}
	return _deleteProgram(program ? program._ : 0);
}

const _deleteRenderbuffer = gl.deleteRenderbuffer;
gl.deleteRenderbuffer = function deleteRenderbuffer(renderbuffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(renderbuffer, gl.WebGLRenderbuffer)
		) ) {
		throw new TypeError('Expected deleteRenderbuffer(WebGLRenderbuffer renderbuffer)');
	}
	return _deleteRenderbuffer(renderbuffer ? renderbuffer._ : 0);
}

const _deleteShader = gl.deleteShader;
gl.deleteShader = function deleteShader(shader) {
	if ( ! (
			c_al(arguments, 1) && c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected deleteShader(WebGLShader shader)');
	}
	return _deleteShader(shader ? shader._ : 0);
}

const _deleteTexture = gl.deleteTexture;
gl.deleteTexture = function deleteTexture(texture) {
	if ( ! (
			c_al(arguments, 1) && c_pi(texture, gl.WebGLTexture)
		) ) {
		throw new TypeError('Expected deleteTexture(WebGLTexture texture)');
	}
	return _deleteTexture(texture ? texture._ : 0);
}

const _depthFunc = gl.depthFunc;
gl.depthFunc = function depthFunc(func) {
	if ( ! (
			c_al(arguments, 1) && c_pt(func, 'number')
		) ) {
		throw new TypeError('Expected depthFunc(number func)');
	}
	return _depthFunc(func);
}

const _depthMask = gl.depthMask;
gl.depthMask = function depthMask(flag) {
	if ( ! (
			c_al(arguments, 1) && c_pt(flag, 'boolean')
		) ) {
		throw new TypeError('Expected depthMask(boolean flag)');
	}
	return _depthMask(flag);
}

const _depthRange = gl.depthRange;
gl.depthRange = function depthRange(zNear, zFar) {
	if ( ! (
			c_al(arguments, 2) && c_pt(zNear, 'number') && c_pt(zFar, 'number')
		) ) {
		throw new TypeError('Expected depthRange(number zNear, number zFar)');
	}
	return _depthRange(zNear, zFar);
}

const _detachShader = gl.detachShader;
gl.detachShader = function detachShader(program, shader) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected detachShader(WebGLProgram program, WebGLShader shader)');
	}
	return _detachShader(program ? program._ : 0, shader ? shader._ : 0);
}

const _disable = gl.disable;
gl.disable = function disable(cap) {
	if ( ! (
			c_al(arguments, 1) && c_pt(cap, 'number')
		) ) {
		throw new TypeError('Expected disable(number cap)');
	}
	return _disable(cap);
}

const _disableVertexAttribArray = gl.disableVertexAttribArray;
gl.disableVertexAttribArray = function disableVertexAttribArray(index) {
	if ( ! (
			c_al(arguments, 1) && c_pt(index, 'number')
		) ) {
		throw new TypeError('Expected disableVertexAttribArray(number index)');
	}
	return _disableVertexAttribArray(index);
}

const _drawArrays = gl.drawArrays;
gl.drawArrays = function drawArrays(mode, first, count) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pt(mode, 'number') && c_pt(first, 'number') && c_pt(count, 'number')
		) ) {
		throw new TypeError('Expected drawArrays(number mode, number first, number count)');
	}
	return _drawArrays(mode, first, count);
}

const _drawElements = gl.drawElements;
gl.drawElements = function drawElements(mode, count, type, offset) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(mode, 'number') && c_pt(count, 'number') &&
			c_pt(type, 'number') && c_pt(offset, 'number')
		) ) {
		throw new TypeError(
			'Expected drawElements(number mode, number count, number type, number offset)'
		);
	}
	return _drawElements(mode, count, type, offset);
}

const _enable = gl.enable;
gl.enable = function enable(cap) {
	if ( ! (
			c_al(arguments, 1) && c_pt(cap, 'number')
		) ) {
		throw new TypeError('Expected enable(number cap)');
	}
	return _enable(cap);
}

const _enableVertexAttribArray = gl.enableVertexAttribArray;
gl.enableVertexAttribArray = function enableVertexAttribArray(index) {
	if ( ! (
			c_al(arguments, 1) && c_pt(index, 'number')
		) ) {
		throw new TypeError('Expected enableVertexAttribArray(number index)');
	}
	return _enableVertexAttribArray(index);
}

const _finish = gl.finish;
gl.finish = function finish() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected finish()');
	}
	return _finish();
}

const _flush = gl.flush;
gl.flush = function flush() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected flush()');
	}
	return _flush();
}

const _framebufferRenderbuffer = gl.framebufferRenderbuffer;
gl.framebufferRenderbuffer = function framebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(target, 'number') &&
			c_pt(attachment, 'number') &&
			c_pt(renderbuffertarget, 'number') &&
			c_pi(renderbuffer, gl.WebGLRenderbuffer)
		) ) {
		throw new TypeError(
			'Expected framebufferRenderbuffer(number target, number attachment, ' +
			'number renderbuffertarget, WebGLRenderbuffer renderbuffer)'
		);
	}
	return _framebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer ? renderbuffer._ : 0);
}

const _framebufferTexture2D = gl.framebufferTexture2D;
gl.framebufferTexture2D = function framebufferTexture2D(target, attachment, textarget, texture, level) {
	if ( ! (
			c_al(arguments, 5) &&
			c_pt(target, 'number') &&
			c_pt(attachment, 'number') &&
			c_pt(textarget, 'number') &&
			c_pi(texture, gl.WebGLTexture) &&
			c_pt(level, 'number')
		) ) {
		throw new TypeError(
			'Expected framebufferTexture2D(number target, number attachment, number ' +
			'textarget, WebGLTexture texture, number level)'
		);
	}
	return _framebufferTexture2D(target, attachment, textarget, texture ? texture._ : 0, level);
}

const _frontFace = gl.frontFace;
gl.frontFace = function frontFace(mode) {
	if ( ! (
			c_al(arguments, 1) && c_pt(mode, 'number')
		) ) {
		throw new TypeError('Expected frontFace(number mode)');
	}
	return _frontFace(mode);
}

const _generateMipmap = gl.generateMipmap;
gl.generateMipmap = function generateMipmap(target) {
	if ( ! (
			c_al(arguments, 1) && c_pt(target, 'number')
		) ) {
		throw new TypeError('Expected generateMipmap(number target)');
	}
	return _generateMipmap(target);
}

const _getActiveAttrib = gl.getActiveAttrib;
gl.getActiveAttrib = function getActiveAttrib(program, index) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(index, 'number')
		) ) {
		throw new TypeError('Expected getActiveAttrib(WebGLProgram program, number index)');
	}
	return new gl.WebGLActiveInfo(_getActiveAttrib(program ? program._ : 0, index));
}

const _getActiveUniform = gl.getActiveUniform;
gl.getActiveUniform = function getActiveUniform(program, index) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(index, 'number')
		) ) {
		throw new TypeError('Expected getActiveUniform(WebGLProgram program, number index)');
	}
	return new gl.WebGLActiveInfo(_getActiveUniform(program ? program._ : 0, index));
}

const _getAttachedShaders = gl.getAttachedShaders;
gl.getAttachedShaders = function getAttachedShaders(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected getAttachedShaders(WebGLProgram program)');
	}
	return _getAttachedShaders(program ? program._ : 0);
}

const _getAttribLocation = gl.getAttribLocation;
gl.getAttribLocation = function getAttribLocation(program, name) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(name, 'string')
		) ) {
		throw new TypeError('Expected getAttribLocation(WebGLProgram program, string name)');
	}
	return _getAttribLocation(program ? program._ : 0, name);
}

const _getParameter = gl.getParameter;
gl.getParameter = function getParameter(pname) {
	if ( ! (
			c_al(arguments, 1) && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getParameter(number pname)');
	}
	if (pname === gl.VERSION) {
		return 'WebGL 1';
	}
	return _getParameter(pname);
}

const _getBufferParameter = gl.getBufferParameter;
gl.getBufferParameter = function getBufferParameter(target, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pt(target, 'number') && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getBufferParameter(number target, number pname)');
	}
	return _getBufferParameter(target, pname);
}

const _getError = gl.getError;
gl.getError = function getError() {
	if (arguments.length !== 0) {
		throw new TypeError('Expected getError()');
	}
	return _getError();
}

const _getFramebufferAttachmentParameter = gl.getFramebufferAttachmentParameter;
gl.getFramebufferAttachmentParameter = function getFramebufferAttachmentParameter(target, attachment, pname) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pt(target, 'number') &&
			c_pt(attachment, 'number') &&
			c_pt(pname, 'number')
		) ) {
		throw new TypeError(
			'Expected getFramebufferAttachmentParameter(number ' +
			'target, number attachment, number pname)'
		);
	}
	return _getFramebufferAttachmentParameter(target, attachment, pname);
}

const _getProgramParameter = gl.getProgramParameter;
gl.getProgramParameter = function getProgramParameter(program, pname) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(pname, 'number')
		) ) {
		throw new TypeError(
			'Expected getProgramParameter(WebGLProgram program, number pname)'
		);
	}
	return _getProgramParameter(program ? program._ : 0, pname);
}

const _getProgramInfoLog = gl.getProgramInfoLog;
gl.getProgramInfoLog = function getProgramInfoLog(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected getProgramInfoLog(WebGLProgram program)');
	}
	return _getProgramInfoLog(program ? program._ : 0);
}

const _getRenderbufferParameter = gl.getRenderbufferParameter;
gl.getRenderbufferParameter = function getRenderbufferParameter(target, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pt(target, 'number') && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getRenderbufferParameter(number target, number pname)');
	}
	return _getRenderbufferParameter(target, pname);
}

const _getShaderParameter = gl.getShaderParameter;
gl.getShaderParameter = function getShaderParameter(shader, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pi(shader, gl.WebGLShader) && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getShaderParameter(WebGLShader shader, number pname)');
	}
	return _getShaderParameter(shader ? shader._ : 0, pname);
}

const _getShaderInfoLog = gl.getShaderInfoLog;
gl.getShaderInfoLog = function getShaderInfoLog(shader) {
	if ( ! (
			c_al(arguments, 1) && c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected getShaderInfoLog(WebGLShader shader)');
	}
	return _getShaderInfoLog(shader ? shader._ : 0);
}

const _getShaderSource = gl.getShaderSource;
gl.getShaderSource = function getShaderSource(shader) {
	if ( ! (
			c_al(arguments, 1) && c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected getShaderSource(WebGLShader shader)');
	}
	return _getShaderSource(shader ? shader._ : 0);
}

const _getTexParameter = gl.getTexParameter;
gl.getTexParameter = function getTexParameter(target, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pt(target, 'number') && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getTexParameter(number target, number pname)');
	}
	return _getTexParameter(target, pname);
}

const _getUniform = gl.getUniform;
gl.getUniform = function getUniform(program, location) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pi(location, gl.WebGLUniformLocation)
		) ) {
		throw new TypeError('Expected getUniform(WebGLProgram program, WebGLUniformLocation location)');
	}
	return _getUniform(program ? program._ : 0, location ? location._ : 0);
}

const _getUniformLocation = gl.getUniformLocation;
gl.getUniformLocation = function getUniformLocation(program, name) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(program, gl.WebGLProgram) &&
			c_pt(name, 'string')
		) ) {
		throw new TypeError('Expected getUniformLocation(WebGLProgram program, string name)');
	}
	return new gl.WebGLUniformLocation(_getUniformLocation(program ? program._ : 0, name));
}

const _getVertexAttrib = gl.getVertexAttrib;
gl.getVertexAttrib = function getVertexAttrib(index, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pt(index, 'number') && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getVertexAttrib(number index, number pname)');
	}
	return _getVertexAttrib(index, pname);
}

const _getVertexAttribOffset = gl.getVertexAttribOffset;
gl.getVertexAttribOffset = function getVertexAttribOffset(index, pname) {
	if ( ! (
			c_al(arguments, 2) && c_pt(index, 'number') && c_pt(pname, 'number')
		) ) {
		throw new TypeError('Expected getVertexAttribOffset(number index, number pname)');
	}
	
	if(pname === gl.CURRENT_VERTEX_ATTRIB) {
		const buf=_getVertexAttribOffset(index, pname);
		return new Float32Array(buf);
	}
	return _getVertexAttribOffset(index, pname);
}

const _hint = gl.hint;
gl.hint = function hint(target, mode) {
	if ( ! (
			c_al(arguments, 2) && c_pt(target, 'number') && c_pt(mode, 'number')
		) ) {
		throw new TypeError('Expected hint(number target, number mode)');
	}
	return _hint(target, mode);
}

const _isBuffer = gl.isBuffer;
gl.isBuffer = function isBuffer(buffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(buffer, gl.WebGLBuffer)
		) ) {
		throw new TypeError('Expected isBuffer(WebGLBuffer buffer)');
	}
	return _isBuffer(buffer ? buffer._ : 0);
}

const _isEnabled = gl.isEnabled;
gl.isEnabled = function isEnabled(cap) {
	if ( ! (
			c_al(arguments, 1) && c_pt(cap, 'number')
		) ) {
		throw new TypeError('Expected isEnabled(number cap)');
	}
	return _isEnabled(cap);
}

const _isFramebuffer = gl.isFramebuffer;
gl.isFramebuffer = function isFramebuffer(framebuffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(framebuffer, gl.WebGLFramebuffer)
		) ) {
		throw new TypeError('Expected isFramebuffer(WebGLFramebuffer framebuffer)');
	}
	return _isFramebuffer(framebuffer ? framebuffer._ : 0);
}

const _isProgram = gl.isProgram;
gl.isProgram = function isProgram(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected isProgram(WebGLProgram program)');
	}
	return _isProgram(program ? program._ : 0);
}

const _isRenderbuffer = gl.isRenderbuffer;
gl.isRenderbuffer = function isRenderbuffer(renderbuffer) {
	if ( ! (
			c_al(arguments, 1) && c_pi(renderbuffer, gl.WebGLRenderbuffer)
		) ) {
		throw new TypeError('Expected isRenderbuffer(WebGLRenderbuffer renderbuffer)');
	}
	return _isRenderbuffer(renderbuffer ? renderbuffer._ : 0);
}

const _isShader = gl.isShader;
gl.isShader = function isShader(shader) {
	if ( ! (
			c_al(arguments, 1) && c_pi(shader, gl.WebGLShader)
		) ) {
		throw new TypeError('Expected isShader(WebGLShader shader)');
	}
	return _isShader(shader ? shader._ : 0);
}

const _isTexture = gl.isTexture;
gl.isTexture = function isTexture(texture) {
	if ( ! (
			c_al(arguments, 1) && c_pi(texture, gl.WebGLTexture)
		) ) {
		throw new TypeError('Expected isTexture(WebGLTexture texture)');
	}
	return _isTexture(texture ? texture._ : 0);
}

const _lineWidth = gl.lineWidth;
gl.lineWidth = function lineWidth(width) {
	if ( ! (
			c_al(arguments, 1) && c_pt(width, 'number')
		) ) {
		throw new TypeError('Expected lineWidth(number width)');
	}
	return _lineWidth(width);
}

const _linkProgram = gl.linkProgram;
gl.linkProgram = function linkProgram(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected linkProgram(WebGLProgram program)');
	}
	return _linkProgram(program ? program._ : 0);
}

const _pixelStorei = gl.pixelStorei;
gl.pixelStorei = function pixelStorei(pname, param) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pt(pname, 'number') &&
			(c_pt(param, 'number') || c_pt(param, 'boolean'))
		) ) {
		throw new TypeError('Expected pixelStorei(number pname, number param)');
	}
	
	if(c_pt(param, 'boolean'))
		param= param ? 1 : 0;
	return _pixelStorei(pname, param);
}

const _polygonOffset = gl.polygonOffset;
gl.polygonOffset = function polygonOffset(factor, units) {
	if ( ! (
			c_al(arguments, 2) && c_pt(factor, 'number') && c_pt(units, 'number')
		) ) {
		throw new TypeError('Expected polygonOffset(number factor, number units)');
	}
	return _polygonOffset(factor, units);
}

const _readPixels = gl.readPixels;
gl.readPixels = function readPixels(x, y, width, height, format, type, pixels) {
	if ( ! (
			c_al(arguments, 7) &&
			c_pt(x, 'number') &&
			c_pt(y, 'number') &&
			c_pt(width, 'number') &&
			c_pt(height, 'number') &&
			c_pt(format, 'number') &&
			c_pt(type, 'number') &&
			c_pt(pixels, 'object')
		) ) {
		throw new TypeError(
			'Expected readPixels(number x, number y, number width, number ' +
			'height, number format, number type, ArrayBufferView pixels)'
		);
	}
	return _readPixels(x, y, width, height, format, type, pixels);
}

const _renderbufferStorage = gl.renderbufferStorage;
gl.renderbufferStorage = function renderbufferStorage(target, internalformat, width, height) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(target, 'number') &&
			c_pt(internalformat, 'number') && c_pt(width, 'number') && c_pt(height, 'number')
		) ) {
		throw new TypeError(
			'Expected renderbufferStorage(number target, number ' +
			'internalformat, number width, number height)'
		);
	}
	return _renderbufferStorage(target, internalformat, width, height);
}

const _sampleCoverage = gl.sampleCoverage;
gl.sampleCoverage = function sampleCoverage(value, invert) {
	if ( ! (
			c_al(arguments, 2) && c_pt(value, 'number') && c_pt(invert, 'boolean')
		) ) {
		throw new TypeError('Expected sampleCoverage(number value, boolean invert)');
	}
	return _sampleCoverage(value, invert);
}

const _scissor = gl.scissor;
gl.scissor = function scissor(x, y, width, height) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(width, 'number') && c_pt(height, 'number')
		) ) {
		throw new TypeError(
			'Expected scissor(number x, number y, number width, number height)'
		);
	}
	return _scissor(x, y, width, height);
}

const _shaderSource = gl.shaderSource;
gl.shaderSource = function shaderSource(shader, source) {
	if ( ! (
			c_al(arguments, 2) && c_pi(shader, gl.WebGLShader) && c_pt(source, 'string')
		) ) {
		throw new TypeError('Expected shaderSource(WebGLShader shader, string source)');
	}
	return _shaderSource(shader ? shader._ : 0, source);
}

const _stencilFunc = gl.stencilFunc;
gl.stencilFunc = function stencilFunc(func, ref, mask) {
	if ( ! (
			c_al(arguments, 3) && c_pt(func, 'number') && c_pt(ref, 'number') && c_pt(mask, 'number')
		) ) {
		throw new TypeError('Expected stencilFunc(number func, number ref, number mask)');
	}
	return _stencilFunc(func, ref, mask);
}

const _stencilFuncSeparate = gl.stencilFuncSeparate;
gl.stencilFuncSeparate = function stencilFuncSeparate(face, func, ref, mask) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(face, 'number') && c_pt(func, 'number') &&
			c_pt(ref, 'number') && c_pt(mask, 'number')
		) ) {
		throw new TypeError(
			'Expected stencilFuncSeparate(number face, number func, number ref, number mask)'
		);
	}
	return _stencilFuncSeparate(face, func, ref, mask);
}

const _stencilMask = gl.stencilMask;
gl.stencilMask = function stencilMask(mask) {
	if ( ! (
			c_al(arguments, 1) && c_pt(mask, 'number')
		) ) {
		throw new TypeError('Expected stencilMask(number mask)');
	}
	return _stencilMask(mask);
}

const _stencilMaskSeparate = gl.stencilMaskSeparate;
gl.stencilMaskSeparate = function stencilMaskSeparate(face, mask) {
	if ( ! (
			c_al(arguments, 2) && c_pt(face, 'number') && c_pt(mask, 'number')
		) ) {
		throw new TypeError('Expected stencilMaskSeparate(number face, number mask)');
	}
	return _stencilMaskSeparate(face, mask);
}

const _stencilOp = gl.stencilOp;
gl.stencilOp = function stencilOp(fail, zfail, zpass) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pt(fail, 'number') &&
			c_pt(zfail, 'number') &&
			c_pt(zpass, 'number')
		) ) {
		throw new TypeError('Expected stencilOp(number fail, number zfail, number zpass)');
	}
	return _stencilOp(fail, zfail, zpass);
}

const _stencilOpSeparate = gl.stencilOpSeparate;
gl.stencilOpSeparate = function stencilOpSeparate(face, fail, zfail, zpass) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(face, 'number') &&
			c_pt(fail, 'number') &&
			c_pt(zfail, 'number') && c_pt(zpass, 'number')
		) ) {
		throw new TypeError('Expected stencilOpSeparate(number face, number fail, number zfail, number zpass)');
	}
	return _stencilOpSeparate(face, fail, zfail, zpass);
}

const _texImage2D = gl.texImage2D;
gl.texImage2D = function texImage2D(target, level, internalformat, width, height, border, format, type, pixels) {
	if( ! (
			c_al(arguments, 9) || c_al(arguments, 6)
		) ) {
		throw new TypeError(
			'Expected texImage2D(number target, number level, number internalformat, ' +
			'number width, number height, number border, number format, number type, ' +
			'ArrayBufferView pixels) or texImage2D(number target, number level, ' +
			'number internalformat, number format, number type, Image pixels)'
		);
	}

	if (c_al(arguments, 6)) {
		// width is now format, height is now type, and border is now pixels
		if( 	! (
			
 			
				c_pt(target, 'number') && 
				c_pt(level, 'number') && c_pt(internalformat, 'number') && 
				c_pt(width, 'number') && c_pt(height, 'number') && 
				c_pi(border, Image))) {
			throw new TypeError(
				'Expected texImage2D(number target, number level, number ' +
				'internalformat, number format, number type, Image pixels)'
			);
		}
		pixels=border;
		type=height;
		format=width;
		return _texImage2D(target, level, internalformat, pixels.width, pixels.height, 0, format, type, pixels);
	}
	else if (c_al(arguments, 9)) {
		if( ! (
				c_pt(target, 'number') && 
				c_pt(level, 'number') && c_pt(internalformat, 'number') && 
				c_pt(width, 'number') && c_pt(height, 'number') &&
				c_pt(border, 'number') && 
				c_pt(format, 'number') &&
				c_pt(type, 'number') && 
				(pixels==null || c_pt(pixels, 'object')))) {
			throw new TypeError(
				'Expected texImage2D(number target, number level, ' +
				'number internalformat, number width, number height, number ' +
				'border, number format, number type, ArrayBufferView pixels)'
			);
		}
		return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
	}
}

const _texParameterf = gl.texParameterf;
gl.texParameterf = function texParameterf(target, pname, param) {
	if ( ! (
			c_al(arguments, 3) && c_pt(target, 'number') && c_pt(pname, 'number') && c_pt(param, 'number')
		) ) {
		throw new TypeError('Expected texParameterf(number target, number pname, number param)');
	}
	return _texParameterf(target, pname, param);
}

const _texParameteri = gl.texParameteri;
gl.texParameteri = function texParameteri(target, pname, param) {
	if ( ! (
			c_al(arguments, 3) && c_pt(target, 'number') && c_pt(pname, 'number') && c_pt(param, 'number')
		) ) {
		throw new TypeError('Expected texParameteri(number target, number pname, number param)');
	}
	return _texParameteri(target, pname, param);
}

const _texSubImage2D = gl.texSubImage2D;
gl.texSubImage2D = function texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels) {
	if ( ! (
			c_al(arguments, 9) &&
			c_pt(target, 'number') &&
			c_pt(level, 'number') && 
			c_pt(xoffset, 'number') && c_pt(yoffset, 'number') && 
			c_pt(width, 'number') && c_pt(height, 'number') && 
			c_pt(format, 'number') && c_pt(type, 'number') && 
			(pixels==null || c_pt(pixels, 'object'))
		) ) {
		throw new TypeError(
			'Expected texSubImage2D(number target, number level, ' +
			'number xoffset, number yoffset, number width, number height, ' +
			'number format, number type, ArrayBufferView pixels)'
		);
	}
	return _texSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

const _uniform1f = gl.uniform1f;
gl.uniform1f = function uniform1f(location, x) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			(c_pt(x, 'number') || c_pt(x, 'boolean'))
		) ) {
		throw new TypeError('Expected uniform1f(WebGLUniformLocation location, number x)');
	}
	return _uniform1f(location ? location._ : 0, x);
}

const _uniform1fv = gl.uniform1fv;
gl.uniform1fv = function uniform1fv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform1fv(WebGLUniformLocation location, FloatArray v)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform1fv(location ? location._ : 0, v);
}

const _uniform1i = gl.uniform1i;
gl.uniform1i = function uniform1i(location, x) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			(c_pt(x, 'number') || c_pt(x, 'boolean'))
		) ) {
		throw new TypeError('Expected uniform1i(WebGLUniformLocation location, number x)');
	}
	if (c_pt(x, 'boolean')) {
		x= x ? 1 : 0;
	}
	return _uniform1i(location ? location._ : 0, x);
}

const _uniform1iv = gl.uniform1iv;
gl.uniform1iv = function uniform1iv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform1iv(WebGLUniformLocation location, Int32Array v)');
	}
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform1iv(location ? location._ : 0, v);
}

const _uniform2f = gl.uniform2f;
gl.uniform2f = function uniform2f(location, x, y) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number')
		) ) {
		throw new TypeError('Expected uniform2f(WebGLUniformLocation location, number x, number y)');
	}
	return _uniform2f(location ? location._ : 0, x, y);
}

const _uniform2fv = gl.uniform2fv;
gl.uniform2fv = function uniform2fv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform2fv(WebGLUniformLocation location, FloatArray v)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform2fv(location ? location._ : 0, v);
}

const _uniform2i = gl.uniform2i;
gl.uniform2i = function uniform2i(location, x, y) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number')
		) ) {
		throw new TypeError('Expected uniform2i(WebGLUniformLocation location, number x, number y)');
	}
	return _uniform2i(location ? location._ : 0, x, y);
}

const _uniform2iv = gl.uniform2iv;
gl.uniform2iv = function uniform2iv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform2iv(WebGLUniformLocation location, Int32Array v)');
	}
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform2iv(location ? location._ : 0, v);
}

const _uniform3f = gl.uniform3f;
gl.uniform3f = function uniform3f(location, x, y, z) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number') && c_pt(z, 'number')
		) ) {
		throw new TypeError(
			'Expected uniform3f(WebGLUniformLocation location, number x, number y, number z)'
		);
	}
	return _uniform3f(location ? location._ : 0, x, y, z);
}

const _uniform3fv = gl.uniform3fv;
gl.uniform3fv = function uniform3fv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform3fv(WebGLUniformLocation location, FloatArray v)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform3fv(location ? location._ : 0, v);
}

const _uniform3i = gl.uniform3i;
gl.uniform3i = function uniform3i(location, x, y, z) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number') && c_pt(z, 'number')
		) ) {
		throw new TypeError(
			'Expected uniform3i(WebGLUniformLocation location, number x, number y, number z)'
		);
	}
	return _uniform3i(location ? location._ : 0, x, y, z);
}

const _uniform3iv = gl.uniform3iv;
gl.uniform3iv = function uniform3iv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform3iv(WebGLUniformLocation location, Int32Array v)');
	}
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform3iv(location ? location._ : 0, v);
}

const _uniform4f = gl.uniform4f;
gl.uniform4f = function uniform4f(location, x, y, z, w) {
	if ( ! (
			c_al(arguments, 5) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(z, 'number') && c_pt(w, 'number')
		) ) {
		throw new TypeError(
			'Expected uniform4f(WebGLUniformLocation location, ' +
			'number x, number y, number z, number w)'
		);
	}
	return _uniform4f(location ? location._ : 0, x, y, z, w);
}

const _uniform4fv = gl.uniform4fv;
gl.uniform4fv = function uniform4fv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform4fv(WebGLUniformLocation location, FloatArray v)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniform4fv(location ? location._ : 0, v);
}

const _uniform4i = gl.uniform4i;
gl.uniform4i = function uniform4i(location, x, y, z, w) {
	if ( ! (
			c_al(arguments, 5) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(z, 'number') && c_pt(w, 'number')
		) ) {
		throw new TypeError(
			'Expected uniform4i(WebGLUniformLocation location, ' +
			'number x, number y, number z, number w)'
		);
	}
	return _uniform4i(location ? location._ : 0, x, y, z, w);
}

const _uniform4iv = gl.uniform4iv;
gl.uniform4iv = function uniform4iv(location, v) {
	if ( ! (
			c_al(arguments, 2) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected uniform4iv(WebGLUniformLocation location, Int32Array v)');
	}
	v = v instanceof Array ? new Int32Array(v) : v;
	return _uniform4iv(location ? location._ : 0, v);
}

const _uniformMatrix2fv = gl.uniformMatrix2fv;
gl.uniformMatrix2fv = function uniformMatrix2fv(location, transpose, v) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(transpose, 'boolean') &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError(
			'Expected uniformMatrix2fv(WebGLUniformLocation ' +
			'location, boolean transpose, FloatArray value)'
		);
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix2fv(location ? location._ : 0, transpose, v);
}

const _uniformMatrix3fv = gl.uniformMatrix3fv;
gl.uniformMatrix3fv = function uniformMatrix3fv(location, transpose, v) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(transpose, 'boolean') &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError(
			'Expected uniformMatrix3fv(WebGLUniformLocation location, ' +
			'boolean transpose, FloatArray value)'
		);
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix3fv(location ? location._ : 0, transpose, v);
}

const _uniformMatrix4fv = gl.uniformMatrix4fv;
gl.uniformMatrix4fv = function uniformMatrix4fv(location, transpose, v) {
	if ( ! (
			c_al(arguments, 3) &&
			c_pi(location, gl.WebGLUniformLocation) &&
			c_pt(transpose, 'boolean') &&
			c_pt(v, 'object')
		) ) {
		throw new TypeError(
			'Expected uniformMatrix4fv(WebGLUniformLocation location, ' +
			'boolean transpose, FloatArray value)'
		);
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _uniformMatrix4fv(location ? location._ : 0, transpose, v);
}

const _useProgram = gl.useProgram;
gl.useProgram = function useProgram(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected useProgram(WebGLProgram program)');
	}
	return _useProgram(program ? program._ : 0);
}

const _validateProgram = gl.validateProgram;
gl.validateProgram = function validateProgram(program) {
	if ( ! (
			c_al(arguments, 1) && c_pi(program, gl.WebGLProgram)
		) ) {
		throw new TypeError('Expected validateProgram(WebGLProgram program)');
	}
	return _validateProgram(program ? program._ : 0);
}

const _vertexAttrib1f = gl.vertexAttrib1f;
gl.vertexAttrib1f = function vertexAttrib1f(indx, x) {
	if ( ! (
			c_al(arguments, 2) && c_pt(indx, 'number') && c_pt(x, 'number')
		) ) {
		throw new TypeError('Expected vertexAttrib1f(number indx, number x)');
	}
	return _vertexAttrib1f(indx, x);
}

const _vertexAttrib1fv = gl.vertexAttrib1fv;
gl.vertexAttrib1fv = function vertexAttrib1fv(indx, v) {
	if ( ! (
			c_al(arguments, 2) && c_pt(indx, 'number') && c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected vertexAttrib1fv(number indx, FloatArray values)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib1fv(indx, v);
}

const _vertexAttrib2f = gl.vertexAttrib2f;
gl.vertexAttrib2f = function vertexAttrib2f(indx, x, y) {
	if ( ! (
			c_al(arguments, 3) && c_pt(indx, 'number') &&
			c_pt(x, 'number') && c_pt(y, 'number')
		) ) {
		throw new TypeError('Expected vertexAttrib2f(number indx, number x, number y)');
	}
	return _vertexAttrib2f(indx, x, y);
}

const _vertexAttrib2fv = gl.vertexAttrib2fv;
gl.vertexAttrib2fv = function vertexAttrib2fv(indx, v) {
	if ( ! (
			c_al(arguments, 2) && c_pt(indx, 'number') && c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected vertexAttrib2fv(number indx, FloatArray values)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib2fv(indx, v);
}

const _vertexAttrib3f = gl.vertexAttrib3f;
gl.vertexAttrib3f = function vertexAttrib3f(indx, x, y, z) {
	if ( ! (
			c_al(arguments, 4) && c_pt(indx, 'number') &&
			c_pt(x, 'number') && c_pt(y, 'number') && c_pt(z, 'number')
		) ) {
		throw new TypeError('Expected vertexAttrib3f(number indx, number x, number y, number z)');
	}
	return _vertexAttrib3f(indx, x, y, z);
}

const _vertexAttrib3fv = gl.vertexAttrib3fv;
gl.vertexAttrib3fv = function vertexAttrib3fv(indx, v) {
	if ( ! (
			c_al(arguments, 2) && c_pt(indx, 'number') && c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected vertexAttrib3fv(number indx, FloatArray values)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib3fv(indx, v);
}

const _vertexAttrib4f = gl.vertexAttrib4f;
gl.vertexAttrib4f = function vertexAttrib4f(indx, x, y, z, w) {
	if ( ! (
			c_al(arguments, 5) &&
			c_pt(indx, 'number') &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(z, 'number') && c_pt(w, 'number')
		) ) {
		throw new TypeError('Expected vertexAttrib4f(number indx, number x, number y, number z, number w)');
	}
	return _vertexAttrib4f(indx, x, y, z, w);
}

const _vertexAttrib4fv = gl.vertexAttrib4fv;
gl.vertexAttrib4fv = function vertexAttrib4fv(indx, v) {
	if ( ! (
			c_al(arguments, 2) && c_pt(indx, 'number') && c_pt(v, 'object')
		) ) {
		throw new TypeError('Expected vertexAttrib4fv(number indx, FloatArray values)');
	}
	v = v instanceof Array ? new Float32Array(v) : v;
	return _vertexAttrib4fv(indx, v);
}

const _vertexAttribPointer = gl.vertexAttribPointer;
gl.vertexAttribPointer = function vertexAttribPointer(indx, size, type, normalized, stride, offset) {
	if ( ! (
			c_al(arguments, 6) &&
			c_pt(indx, 'number') &&
			c_pt(size, 'number') &&
			c_pt(type, 'number') &&
			(c_pt(normalized, 'boolean') || c_pt(normalized, 'number')) &&
			c_pt(stride, 'number') && c_pt(offset, 'number')
		) ) {
		console.error('vertexAttribPointer args:', arguments);
		throw new TypeError(
			'Expected vertexAttribPointer(number indx, number size, number type, ' +
			'boolean normalized, number stride, number offset)'
		);
	}
	return _vertexAttribPointer(indx, size, type, normalized, stride, offset);
}

const _viewport = gl.viewport;
gl.viewport = function viewport(x, y, width, height) {
	if ( ! (
			c_al(arguments, 4) &&
			c_pt(x, 'number') && c_pt(y, 'number') &&
			c_pt(width, 'number') && c_pt(height, 'number')
		) ) {
		throw new TypeError('Expected viewport(number x, number y, number width, number height)');
	}
	return _viewport(x, y, width, height);
}

