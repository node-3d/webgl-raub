/* eslint-disable func-names */
'use strict';

const gl = require('../core');
const { createExtensions } = require('./extensions');

module.exports = gl;

const wrapF32 = (v) => (v.constructor === Array ? new Float32Array(v) : v);
const wrapI32 = (v) => (v.constructor === Array ? new Int32Array(v) : v);
const wrapUi32 = (v) => (v.constructor === Array ? new Uint32Array(v) : v);

const extractId = (x) => (x ? x._ : 0);


if (!gl.__isInited) {
	gl.__isInited = true;
	
	// WebGL constructors
	gl.WebGLRenderingContext = function WebGLRenderingContext(_) { this._ = _; };
	gl.WebGLProgram = function WebGLProgram(_) { this._ = _; };
	gl.WebGLQuery  = function WebGLQuery(_) { this._ = _; };
	gl.WebGLShader = function WebGLShader(_) { this._ = _; };
	gl.WebGLBuffer = function WebGLBuffer(_) { this._ = _; };
	gl.WebGLVertexArray = function WebGLVertexArray(_) { this._ = _; };
	gl.WebGLFramebuffer = function WebGLFramebuffer(_) { this._ = _; };
	gl.WebGLRenderbuffer = function WebGLRenderbuffer(_) { this._ = _; };
	gl.WebGLTexture = function WebGLTexture(_) { this._ = _; };
	gl.WebGLUniformLocation = function WebGLUniformLocation(_) { this._ = _; };
	gl.WebGLSampler = function WebGLSampler(_) { this._ = _; };
	gl.WebGLSync = function WebGLSync(_) { this._ = _; };
	gl.WebGLVertexArrayObject = function WebGLVertexArrayObject(_) { this._ = _; };
	gl.WebGLActiveInfo = function WebGLActiveInfo(_) {
		this._ = _;
		this.size = _.size;
		this.type = _.type;
		this.name = _.name;
	};
	gl.WebGLTransformFeedback = function WebGLTransformFeedback(_) { this._ = _; };
	gl.WebGL2RenderingContext = function WebGL2RenderingContext(_) { this._ = _; };
	
	// Global scope constructors for browser-style libs
	global.WebGLRenderingContext = gl.WebGLRenderingContext;
	global.WebGLProgram = gl.WebGLProgram;
	global.WebGLQuery = gl.WebGLQuery;
	global.WebGLShader = gl.WebGLShader;
	global.WebGLBuffer = gl.WebGLBuffer;
	global.WebGLVertexArrayObject = gl.WebGLVertexArrayObject;
	global.WebGLFramebuffer = gl.WebGLFramebuffer;
	global.WebGLRenderbuffer = gl.WebGLRenderbuffer;
	global.WebGLTexture = gl.WebGLTexture;
	global.WebGLUniformLocation = gl.WebGLUniformLocation;
	global.WebGLActiveInfo = gl.WebGLActiveInfo;
	global.WebGLTransformFeedback = gl.WebGLTransformFeedback;
	
	gl._versionString = 'WebGL 1.0';
	gl.useWebGL2 = () => {
		global.WebGL2RenderingContext = gl.WebGL2RenderingContext;
		Object.setPrototypeOf(gl, gl.WebGL2RenderingContext.prototype);
		gl._versionString = 'WebGL 2.0';
	};
	
	gl.contextAttributes = {
		alpha: true,
		antialias: true,
		depth: true,
		failIfMajorPerformanceCaveat: false,
		powerPreference: 'high-performance',
		premultipliedAlpha: true,
		preserveDrawingBuffer: false,
		stencil: true,
		desynchronized: false,
	};
	gl.getContextAttributes = () => gl.contextAttributes;
	
	gl.isContextLost = () => false;
	
	if (gl.drawingBufferWidth === undefined) {
		Object.defineProperty(
			gl, 'drawingBufferWidth', { get: () => (gl.canvas ? gl.canvas.width : 800) },
		);
	}
	
	if (gl.drawingBufferHeight === undefined) {
		Object.defineProperty(
			gl, 'drawingBufferHeight', { get: () => (gl.canvas ? gl.canvas.height : 600) },
		);
	}
	
	// --------- Wrap some of the API calls for WebGL
	
	// Attrib
	
	const _getActiveAttrib = gl.getActiveAttrib;
	gl.getActiveAttrib = (program, idx) => new gl.WebGLActiveInfo(_getActiveAttrib(program, idx));
	
	const _vertexAttrib1fv = gl.vertexAttrib1fv;
	gl.vertexAttrib1fv = (idx, v) => _vertexAttrib1fv(idx, wrapF32(v));
	
	const _vertexAttrib2fv = gl.vertexAttrib2fv;
	gl.vertexAttrib2fv = (idx, v) => _vertexAttrib2fv(idx, wrapF32(v));
	
	const _vertexAttrib3fv = gl.vertexAttrib3fv;
	gl.vertexAttrib3fv = (idx, v) => _vertexAttrib3fv(idx, wrapF32(v));
	
	const _vertexAttrib4fv = gl.vertexAttrib4fv;
	gl.vertexAttrib4fv = (idx, v) => _vertexAttrib4fv(idx, wrapF32(v));
	
	const _vertexAttribI4iv = gl.vertexAttribI4iv;
	gl.vertexAttribI4iv = (idx, v) => _vertexAttribI4iv(idx, wrapI32(v));
	
	const _vertexAttribI4uiv = gl.vertexAttribI4uiv;
	gl.vertexAttribI4uiv = (idx, v) => _vertexAttribI4uiv(idx, wrapUi32(v));
	
	// VBO
	
	const _createBuffer = gl.createBuffer;
	gl.createBuffer = () => new gl.WebGLBuffer(_createBuffer());
	
	const _bufferSubData = gl.bufferSubData;
	gl.bufferSubData = (target, offset, v) => _bufferSubData(target, offset, wrapF32(v));
	
	// FBO
	
	const _createFramebuffer = gl.createFramebuffer;
	gl.createFramebuffer = () => new gl.WebGLFramebuffer(_createFramebuffer());
	
	// Program
	
	const _createProgram = gl.createProgram;
	gl.createProgram = () => new gl.WebGLProgram(_createProgram());
	
	// RBO
	
	const _createRenderbuffer = gl.createRenderbuffer;
	gl.createRenderbuffer = () => new gl.WebGLRenderbuffer(_createRenderbuffer());
	
	// Shader
	
	const _createShader = gl.createShader;
	gl.createShader = (type) => new gl.WebGLShader(_createShader(type));
	
	const _getAttachedShaders = gl.getAttachedShaders;
	gl.getAttachedShaders = (program) => (
		_getAttachedShaders(program).map((id) => new gl.WebGLShader(id))
	);
	
	// Texture
	
	const _createTexture = gl.createTexture;
	gl.createTexture = () => new gl.WebGLTexture(_createTexture());
	
	const _texImage2D = gl.texImage2D;
	gl.texImage2D = (...args) => {
		const [target, level, internalformat, width, height, border, format, type, pixels] = args;
		
		if (args.length === 6) {
			// `width` is now `format`, `height` is now `type`, and `border` is now `pixels`
			const pixels = border;
			const type = height;
			const format = width;
			return _texImage2D(
				target, level, internalformat, pixels.width, pixels.height, 0, format, type, pixels
			);
		}
		
		if (args.length === 9) {
			return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		}
		
		throw new TypeError('Function texImage2D() takes 6 or 9 arguments.');
	};
	
	// Uniform
	
	const _getActiveUniform = gl.getActiveUniform;
	gl.getActiveUniform = (program, index) => (
		new gl.WebGLActiveInfo(_getActiveUniform(program, index))
	);
	
	const _getUniformLocation = gl.getUniformLocation;
	gl.getUniformLocation = (program, name) => (
		new gl.WebGLUniformLocation(_getUniformLocation(program, name))
	);
	
	const _uniform1fv = gl.uniform1fv;
	gl.uniform1fv = (location, v) => _uniform1fv(location, wrapF32(v));
	
	const _uniform1iv = gl.uniform1iv;
	gl.uniform1iv = (location, v) => _uniform1iv(location, wrapI32(v));
	
	const _uniform2fv = gl.uniform2fv;
	gl.uniform2fv = (location, v) => _uniform2fv(location, wrapF32(v));
	
	const _uniform2iv = gl.uniform2iv;
	gl.uniform2iv = (location, v) => _uniform2iv(location, wrapI32(v));
	
	const _uniform3fv = gl.uniform3fv;
	gl.uniform3fv = (location, v) => _uniform3fv(location, wrapF32(v));
	
	const _uniform3iv = gl.uniform3iv;
	gl.uniform3iv = (location, v) => _uniform3iv(location, wrapI32(v));
	
	const _uniform4fv = gl.uniform4fv;
	gl.uniform4fv = (location, v) => _uniform4fv(location, wrapF32(v));
	
	const _uniform4iv = gl.uniform4iv;
	gl.uniform4iv = (location, v) => _uniform4iv(location, wrapI32(v));
	
	const _uniformMatrix2fv = gl.uniformMatrix2fv;
	gl.uniformMatrix2fv = (location, isT, v) => _uniformMatrix2fv(location, isT, wrapF32(v));
	
	const _uniformMatrix3fv = gl.uniformMatrix3fv;
	gl.uniformMatrix3fv = (location, isT, v) => _uniformMatrix3fv(location, isT, wrapF32(v));
	
	const _uniformMatrix4fv = gl.uniformMatrix4fv;
	gl.uniformMatrix4fv = (location, isT, v) => _uniformMatrix4fv(location, isT, wrapF32(v));
	
	const _uniform1uiv = gl.uniform1uiv;
	gl.uniform1uiv = (location, v) => _uniform1uiv(location, wrapUi32(v));
	
	const _uniform2uiv = gl.uniform2uiv;
	gl.uniform2uiv = (location, v) => _uniform2uiv(location, wrapUi32(v));
	
	const _uniform3uiv = gl.uniform3uiv;
	gl.uniform3uiv = (location, v) => _uniform3uiv(location, wrapUi32(v));
	
	const _uniform4uiv = gl.uniform4uiv;
	gl.uniform4uiv = (location, v) => _uniform4uiv(location, wrapUi32(v));
	
	const _uniformMatrix2x3fv = gl.uniformMatrix2x3fv;
	gl.uniformMatrix2x3fv = (location, isT, v) => _uniformMatrix2x3fv(location, isT, wrapF32(v));
	
	const _uniformMatrix2x4fv = gl.uniformMatrix2x4fv;
	gl.uniformMatrix2x4fv = (location, isT, v) => _uniformMatrix2x4fv(location, isT, wrapF32(v));
	
	const _uniformMatrix3x2fv = gl.uniformMatrix3x2fv;
	gl.uniformMatrix3x2fv = (location, isT, v) => _uniformMatrix3x2fv(location, isT, wrapF32(v));
	
	const _uniformMatrix3x4fv = gl.uniformMatrix3x4fv;
	gl.uniformMatrix3x4fv = (location, isT, v) => _uniformMatrix3x4fv(location, isT, wrapF32(v));
	
	const _uniformMatrix4x2fv = gl.uniformMatrix4x2fv;
	gl.uniformMatrix4x2fv = (location, isT, v) => _uniformMatrix4x2fv(location, isT, wrapF32(v));
	
	const _uniformMatrix4x3fv = gl.uniformMatrix4x3fv;
	gl.uniformMatrix4x3fv = (location, isT, v) => _uniformMatrix4x3fv(location, isT, wrapF32(v));
	
	// VAO
	
	const _createVertexArray = gl.createVertexArray;
	gl.createVertexArray = () => new gl.WebGLVertexArray(_createVertexArray());
	
	// Transform feedback
	
	const _createTransformFeedback = gl.createTransformFeedback;
	gl.createTransformFeedback = () => new gl.WebGLTransformFeedback(_createTransformFeedback());
	
	// Query
	
	const _createQuery = gl.createQuery;
	gl.createQuery = () => new gl.WebGLQuery(_createQuery());
	
	// Sync - keep extractId because it holds a pointer, not resource
	
	const _fenceSync = gl.fenceSync;
	gl.fenceSync = (condition, flags) => new gl.WebGLSync(_fenceSync(condition, flags));
	
	const _deleteSync = gl.deleteSync;
	gl.deleteSync = (sync) => _deleteSync(extractId(sync));
	
	const _isSync = gl.isSync;
	gl.isSync = (sync) => _isSync(extractId(sync));
	
	const _clientWaitSync = gl.clientWaitSync;
	gl.clientWaitSync = (sync, flags, timeout) => _clientWaitSync(extractId(sync), flags, timeout);
	
	const _waitSync = gl.waitSync;
	gl.waitSync = (sync, flags, timeout) => _waitSync(extractId(sync), flags, timeout);
	
	const _getSyncParameter = gl.getSyncParameter;
	gl.getSyncParameter = (sync, pname) => _getSyncParameter(extractId(sync), pname);
	
	// Sampler
	
	const _createSampler = gl.createSampler;
	gl.createSampler = () => new gl.WebGLSampler(_createSampler());
	
	// Misc OpenGL Functions
	
	// https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext/getParameter
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGet.xhtml
	const _getParameter = gl.getParameter;
	gl.getParameter = (pname) => {
		if (pname === gl.VERSION) {
			return gl._versionString;
		}
		
		// null
		// FIXME: Do these have OpenGL-based values?
		if (
			pname === gl.COPY_READ_BUFFER_BINDING ||
			pname === gl.COPY_WRITE_BUFFER_BINDING
		) {
			return null;
		}
		
		const result = _getParameter(pname);
		
		// Float32Array
		if (
			pname === gl.ALIASED_LINE_WIDTH_RANGE ||
			pname === gl.ALIASED_POINT_SIZE_RANGE ||
			pname === gl.BLEND_COLOR ||
			pname === gl.COLOR_CLEAR_VALUE ||
			pname === gl.DEPTH_RANGE
		) {
			return wrapF32(result);
		}
		
		// Uint32Array
		if (pname === gl.COMPRESSED_TEXTURE_FORMATS) {
			return wrapUi32(result);
		}
		
		// Int32Array
		if (pname === gl.MAX_VIEWPORT_DIMS || pname === gl.SCISSOR_BOX || pname === gl.VIEWPORT) {
			return wrapI32(result);
		}
		
		// WebGLFramebuffer
		if (
			pname === gl.FRAMEBUFFER_BINDING ||
			pname === gl.DRAW_FRAMEBUFFER_BINDING ||
			pname === gl.READ_FRAMEBUFFER_BINDING
		) {
			return result ? new gl.WebGLFramebuffer(result) : null;
		}
		
		// WebGLRenderbuffer
		if (pname === gl.RENDERBUFFER_BINDING) {
			return result ? new gl.WebGLRenderbuffer(result) : null;
		}
		
		// WebGLSampler
		if (pname === gl.SAMPLER_BINDING) {
			return result ? new gl.WebGLSampler(result) : null;
		}
		
		// WebGLTransformFeedback
		if (pname === gl.TRANSFORM_FEEDBACK_BINDING) {
			return result ? new gl.WebGLTransformFeedback(result) : null;
		}
		
		// WebGLVertexArrayObject
		if (pname === gl.VERTEX_ARRAY_BINDING) {
			return result ? new gl.WebGLVertexArrayObject(result) : null;
		}
		
		// WebGLProgram
		if (pname === gl.CURRENT_PROGRAM) {
			return result ? new gl.WebGLProgram(result) : null;
		}
		
		// WebGLBuffer
		if (
			pname === gl.ARRAY_BUFFER_BINDING ||
			pname === gl.ELEMENT_ARRAY_BUFFER_BINDING ||
			pname === gl.PIXEL_PACK_BUFFER_BINDING ||
			pname === gl.PIXEL_UNPACK_BUFFER_BINDING ||
			pname === gl.TRANSFORM_FEEDBACK_BUFFER_BINDING ||
			pname === gl.UNIFORM_BUFFER_BINDING
		) {
			return result ? new gl.WebGLBuffer(result) : null;
		}
		
		// WebGLTexture
		if (
			pname === gl.TEXTURE_BINDING_2D ||
			pname === gl.TEXTURE_BINDING_CUBE_MAP ||
			pname === gl.TEXTURE_BINDING_2D_ARRAY ||
			pname === gl.TEXTURE_BINDING_3D
		) {
			return result ? new gl.WebGLTexture(result) : null;
		}
		
		return result;
	};
	
	
	// ------------- Attach "Extensions"
	
	const extensions = createExtensions(gl);
	
	const _getSupportedExtensions = gl.getSupportedExtensions;
	gl.getSupportedExtensions = () => {
		gl._realExtensions = _getSupportedExtensions().split(' ');
		return Object.keys(extensions);
	};
	
	gl.getExtension = (name) => extensions[name];
}

