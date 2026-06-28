import { createExtensions } from './extensions.ts';
import type { TExtensions } from './extensions.ts';
import { native } from './native.ts';
import type { TNativeSync } from './native.ts';
import {
	WebGL2RenderingContext as WebGL2RenderingContextImpl,
	WebGLActiveInfo as WebGLActiveInfoImpl,
	WebGLBuffer as WebGLBufferImpl,
	WebGLFramebuffer as WebGLFramebufferImpl,
	WebGLProgram as WebGLProgramImpl,
	WebGLQuery as WebGLQueryImpl,
	WebGLRenderbuffer as WebGLRenderbufferImpl,
	WebGLRenderingContext as WebGLRenderingContextImpl,
	WebGLSampler as WebGLSamplerImpl,
	WebGLShader as WebGLShaderImpl,
	WebGLSync as WebGLSyncImpl,
	WebGLTexture as WebGLTextureImpl,
	WebGLTransformFeedback as WebGLTransformFeedbackImpl,
	WebGLUniformLocation as WebGLUniformLocationImpl,
	WebGLVertexArrayObject as WebGLVertexArrayObjectImpl,
} from './classes.ts';
import type { WebGLObject } from './classes.ts';
import type { TArrayValue, TWebGLState } from './types.ts';
import type { TNativeMutable, TNativeTrimmed, TWebGLConstructors, TWebGLOverrides } from './overrides.ts';

// The native WebGL object is patched with browser-style constructors
// and wrappers at runtime.

// Private mutable view for use within this file
const gl = native as unknown as TNativeMutable;

// oxlint-disable no-underscore-dangle

export type TWebGL = TNativeTrimmed & Readonly<TWebGLOverrides> & Readonly<TWebGLConstructors> & TWebGLState;

// Public immutable API surface
export const webgl = native as unknown as TWebGL;

const wrapF32 = (v: TArrayValue): ArrayBufferView => (v.constructor === Float32Array ? v : new Float32Array(v));
const wrapI32 = (v: TArrayValue): ArrayBufferView => (v.constructor === Int32Array ? v : new Int32Array(v));
const wrapUi32 = (v: TArrayValue): ArrayBufferView => (v.constructor === Uint32Array ? v : new Uint32Array(v));

const extractSync = (x: WebGLSync): TNativeSync => (x as WebGLObject<TNativeSync>)._;

if (!gl.__isInited) {
	gl.__isInited = true;
	
	// WebGL constructors
	gl.WebGLRenderingContext = WebGLRenderingContextImpl;
	gl.WebGLProgram = WebGLProgramImpl;
	gl.WebGLQuery  = WebGLQueryImpl;
	gl.WebGLShader = WebGLShaderImpl;
	gl.WebGLBuffer = WebGLBufferImpl;
	gl.WebGLFramebuffer = WebGLFramebufferImpl;
	gl.WebGLRenderbuffer = WebGLRenderbufferImpl;
	gl.WebGLTexture = WebGLTextureImpl;
	gl.WebGLUniformLocation = WebGLUniformLocationImpl;
	gl.WebGLSampler = WebGLSamplerImpl;
	gl.WebGLSync = WebGLSyncImpl;
	gl.WebGLVertexArrayObject = WebGLVertexArrayObjectImpl;
	gl.WebGLActiveInfo = WebGLActiveInfoImpl;
	gl.WebGLTransformFeedback = WebGLTransformFeedbackImpl;
	gl.WebGL2RenderingContext = WebGL2RenderingContextImpl;
	
	// Global scope constructors for browser-style libs
	global.WebGLRenderingContext = gl.WebGLRenderingContext as unknown as typeof WebGLRenderingContext;
	global.WebGLProgram = gl.WebGLProgram as unknown as typeof WebGLProgram;
	global.WebGLQuery = gl.WebGLQuery as unknown as typeof WebGLQuery;
	global.WebGLShader = gl.WebGLShader as unknown as typeof WebGLShader;
	global.WebGLBuffer = gl.WebGLBuffer as unknown as typeof WebGLBuffer;
	global.WebGLVertexArrayObject = gl.WebGLVertexArrayObject as unknown as typeof WebGLVertexArrayObject;
	global.WebGLFramebuffer = gl.WebGLFramebuffer as unknown as typeof WebGLFramebuffer;
	global.WebGLRenderbuffer = gl.WebGLRenderbuffer as unknown as typeof WebGLRenderbuffer;
	global.WebGLTexture = gl.WebGLTexture as unknown as typeof WebGLTexture;
	global.WebGLUniformLocation = gl.WebGLUniformLocation as unknown as typeof WebGLUniformLocation;
	global.WebGLActiveInfo = gl.WebGLActiveInfo as unknown as typeof WebGLActiveInfo;
	global.WebGLTransformFeedback = gl.WebGLTransformFeedback as unknown as typeof WebGLTransformFeedback;
	
	gl._versionString = 'WebGL 1.0';
	gl.useWebGL2 = () => {
		global.WebGL2RenderingContext = gl.WebGL2RenderingContext as unknown as typeof WebGL2RenderingContext;
		Object.setPrototypeOf(gl, gl.WebGL2RenderingContext.prototype);
		gl._versionString = 'WebGL 2.0';
	};
	
	gl.extractId = (x: { _?: number }): number => (x as WebGLObject<number>)._;
	
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
			gl, 'drawingBufferWidth', { get: () => (gl.canvas ? gl.canvas.width : 1280) },
		);
	}
	
	if (gl.drawingBufferHeight === undefined) {
		Object.defineProperty(
			gl, 'drawingBufferHeight', { get: () => (gl.canvas ? gl.canvas.height : 720) },
		);
	}
	
	// --------- Wrap some of the API calls for WebGL
	
	// Attrib
	
	const _getActiveAttrib = native.getActiveAttrib;
	gl.getActiveAttrib = (program: WebGLProgram, idx: number) => new gl.WebGLActiveInfo(_getActiveAttrib(program as WebGLProgramImpl, idx));
	
	const _vertexAttrib1fv = native.vertexAttrib1fv;
	gl.vertexAttrib1fv = (idx: number, v: TArrayValue) => _vertexAttrib1fv(idx, wrapF32(v));
	
	const _vertexAttrib2fv = native.vertexAttrib2fv;
	gl.vertexAttrib2fv = (idx: number, v: TArrayValue) => _vertexAttrib2fv(idx, wrapF32(v));
	
	const _vertexAttrib3fv = native.vertexAttrib3fv;
	gl.vertexAttrib3fv = (idx: number, v: TArrayValue) => _vertexAttrib3fv(idx, wrapF32(v));
	
	const _vertexAttrib4fv = native.vertexAttrib4fv;
	gl.vertexAttrib4fv = (idx: number, v: TArrayValue) => _vertexAttrib4fv(idx, wrapF32(v));
	
	const _vertexAttribI4iv = native.vertexAttribI4iv;
	gl.vertexAttribI4iv = (idx: number, v: TArrayValue) => _vertexAttribI4iv(idx, wrapI32(v));
	
	const _vertexAttribI4uiv = native.vertexAttribI4uiv;
	gl.vertexAttribI4uiv = (idx: number, v: TArrayValue) => _vertexAttribI4uiv(idx, wrapUi32(v));
	
	// VBO
	
	const _createBuffer = native.createBuffer;
	gl.createBuffer = () => new gl.WebGLBuffer(_createBuffer());
	
	const _bufferSubData = native.bufferSubData;
	gl.bufferSubData = (target, offset, v: TArrayValue) => _bufferSubData(target, offset, wrapF32(v));
	
	// FBO
	
	const _createFramebuffer = native.createFramebuffer;
	gl.createFramebuffer = () => new gl.WebGLFramebuffer(_createFramebuffer());
	
	// Program
	
	const _createProgram = native.createProgram;
	gl.createProgram = () => new gl.WebGLProgram(_createProgram());
	
	// RBO
	
	const _createRenderbuffer = native.createRenderbuffer;
	gl.createRenderbuffer = () => new gl.WebGLRenderbuffer(_createRenderbuffer());
	
	// Shader
	
	const _createShader = native.createShader;
	gl.createShader = (shaderType: number) => new gl.WebGLShader(_createShader(shaderType));
	
	const _getAttachedShaders = native.getAttachedShaders;
	gl.getAttachedShaders = (program) => (
		_getAttachedShaders(program as WebGLProgramImpl).map((id) => new gl.WebGLShader(id))
	);
	
	// Texture
	
	const _createTexture = native.createTexture;
	gl.createTexture = () => new gl.WebGLTexture(_createTexture());
	
	const _texImage2D = native.texImage2D;
	gl.texImage2D = (...args) => {
		// oxlint-disable-next-line no-magic-numbers
		if (args.length === 6) {
			const [target, level, internalformat, format, type, pixels] = args;
			return _texImage2D(
				target, level, internalformat, pixels.width, pixels.height, 0, format, type, pixels
			);
		}
		
		// oxlint-disable-next-line no-magic-numbers
		if (args.length === 9) {
			const [target, level, internalformat, width, height, border, format, type, pixels] = args;
			return _texImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		}
		
		throw new TypeError('Function texImage2D() takes 6 or 9 arguments.');
	};
	
	// Uniform
	
	const _getActiveUniform = native.getActiveUniform;
	gl.getActiveUniform = (program, index) => (
		new gl.WebGLActiveInfo(_getActiveUniform(program as WebGLProgramImpl, index))
	);
	
	const _getUniformLocation = native.getUniformLocation;
	gl.getUniformLocation = (program, name) => (
		new gl.WebGLUniformLocation(_getUniformLocation(program as WebGLProgramImpl, name))
	);
	
	const _uniform1fv = native.uniform1fv;
	gl.uniform1fv = (location, v: TArrayValue) => _uniform1fv(location as WebGLUniformLocationImpl, wrapF32(v));
	
	const _uniform1iv = native.uniform1iv;
	gl.uniform1iv = (location, v: TArrayValue) => _uniform1iv(location as WebGLUniformLocationImpl, wrapI32(v));
	
	const _uniform2fv = native.uniform2fv;
	gl.uniform2fv = (location, v: TArrayValue) => _uniform2fv(location as WebGLUniformLocationImpl, wrapF32(v));
	
	const _uniform2iv = native.uniform2iv;
	gl.uniform2iv = (location, v: TArrayValue) => _uniform2iv(location as WebGLUniformLocationImpl, wrapI32(v));
	
	const _uniform3fv = native.uniform3fv;
	gl.uniform3fv = (location, v: TArrayValue) => _uniform3fv(location as WebGLUniformLocationImpl, wrapF32(v));
	
	const _uniform3iv = native.uniform3iv;
	gl.uniform3iv = (location, v: TArrayValue) => _uniform3iv(location as WebGLUniformLocationImpl, wrapI32(v));
	
	const _uniform4fv = native.uniform4fv;
	gl.uniform4fv = (location, v: TArrayValue) => _uniform4fv(location as WebGLUniformLocationImpl, wrapF32(v));
	
	const _uniform4iv = native.uniform4iv;
	gl.uniform4iv = (location, v: TArrayValue) => _uniform4iv(location as WebGLUniformLocationImpl, wrapI32(v));
	
	const _uniformMatrix2fv = native.uniformMatrix2fv;
	gl.uniformMatrix2fv = (location, isT, v: TArrayValue) => _uniformMatrix2fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix3fv = native.uniformMatrix3fv;
	gl.uniformMatrix3fv = (location, isT, v: TArrayValue) => _uniformMatrix3fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix4fv = native.uniformMatrix4fv;
	gl.uniformMatrix4fv = (location, isT, v: TArrayValue) => _uniformMatrix4fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniform1uiv = native.uniform1uiv;
	gl.uniform1uiv = (location, v: TArrayValue) => _uniform1uiv(location as WebGLUniformLocationImpl, wrapUi32(v));
	
	const _uniform2uiv = native.uniform2uiv;
	gl.uniform2uiv = (location, v: TArrayValue) => _uniform2uiv(location as WebGLUniformLocationImpl, wrapUi32(v));
	
	const _uniform3uiv = native.uniform3uiv;
	gl.uniform3uiv = (location, v: TArrayValue) => _uniform3uiv(location as WebGLUniformLocationImpl, wrapUi32(v));
	
	const _uniform4uiv = native.uniform4uiv;
	gl.uniform4uiv = (location, v: TArrayValue) => _uniform4uiv(location as WebGLUniformLocationImpl, wrapUi32(v));
	
	const _uniformMatrix2x3fv = native.uniformMatrix2x3fv;
	gl.uniformMatrix2x3fv = (location, isT, v: TArrayValue) => _uniformMatrix2x3fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix2x4fv = native.uniformMatrix2x4fv;
	gl.uniformMatrix2x4fv = (location, isT, v: TArrayValue) => _uniformMatrix2x4fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix3x2fv = native.uniformMatrix3x2fv;
	gl.uniformMatrix3x2fv = (location, isT, v: TArrayValue) => _uniformMatrix3x2fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix3x4fv = native.uniformMatrix3x4fv;
	gl.uniformMatrix3x4fv = (location, isT, v: TArrayValue) => _uniformMatrix3x4fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix4x2fv = native.uniformMatrix4x2fv;
	gl.uniformMatrix4x2fv = (location, isT, v: TArrayValue) => _uniformMatrix4x2fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	const _uniformMatrix4x3fv = native.uniformMatrix4x3fv;
	gl.uniformMatrix4x3fv = (location, isT, v: TArrayValue) => _uniformMatrix4x3fv(location as WebGLUniformLocationImpl, isT, wrapF32(v));
	
	// VAO
	
	const _createVertexArray = native.createVertexArray;
	gl.createVertexArray = () => new gl.WebGLVertexArrayObject(_createVertexArray());
	
	// Transform feedback
	
	const _createTransformFeedback = native.createTransformFeedback;
	gl.createTransformFeedback = () => new gl.WebGLTransformFeedback(_createTransformFeedback());
	
	// Query
	
	const _createQuery = native.createQuery;
	gl.createQuery = () => new gl.WebGLQuery(_createQuery());
	
	// Sync - keep extractId because it holds a pointer, not resource
	
	const _fenceSync = native.fenceSync;
	gl.fenceSync = (condition, flags) => new gl.WebGLSync(_fenceSync(condition, flags));
	
	const _deleteSync = native.deleteSync;
	gl.deleteSync = (sync) => _deleteSync(extractSync(sync as WebGLSyncImpl));
	
	const _isSync = native.isSync;
	gl.isSync = (sync) => _isSync(extractSync(sync));
	
	const _clientWaitSync = native.clientWaitSync;
	gl.clientWaitSync = (sync, flags, timeout) => _clientWaitSync(extractSync(sync), flags, timeout);
	
	const _waitSync = native.waitSync;
	gl.waitSync = (sync, flags, timeout) => _waitSync(extractSync(sync), flags, timeout);
	
	const _getSyncParameter = native.getSyncParameter;
	gl.getSyncParameter = (sync, pname) => _getSyncParameter(extractSync(sync), pname);
	
	// Sampler
	
	const _createSampler = native.createSampler;
	gl.createSampler = () => new gl.WebGLSampler(_createSampler());
	
	// Misc OpenGL Functions
	
	// https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext/getParameter
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGet.xhtml
	const _getParameter = native.getParameter;
	// oxlint-disable-next-line complexity
	gl.getParameter = (pname) => {
		if (pname === gl.VERSION) {
			return gl._versionString;
		}
		
		// FIXME: Do these have OpenGL-based values?
		if (
			pname === gl.COPY_READ_BUFFER_BINDING ||
			pname === gl.COPY_WRITE_BUFFER_BINDING
		) {
			return null;
		}
		
		const result = _getParameter(pname);
		
		// null is null
		if (result === undefined || result === null) {
			return null;
		}
		
		// Float32Array
		if (
			pname === gl.ALIASED_LINE_WIDTH_RANGE ||
			pname === gl.ALIASED_POINT_SIZE_RANGE ||
			pname === gl.BLEND_COLOR ||
			pname === gl.COLOR_CLEAR_VALUE ||
			pname === gl.DEPTH_RANGE
		) {
			return wrapF32(result as TArrayValue);
		}
		
		// Uint32Array
		if (pname === gl.COMPRESSED_TEXTURE_FORMATS) {
			return wrapUi32(result as TArrayValue);
		}
		
		// Int32Array
		if (pname === gl.MAX_VIEWPORT_DIMS || pname === gl.SCISSOR_BOX || pname === gl.VIEWPORT) {
			return wrapI32(result as TArrayValue);
		}
		
		// WebGLFramebuffer
		if (
			pname === gl.FRAMEBUFFER_BINDING ||
			pname === gl.DRAW_FRAMEBUFFER_BINDING ||
			pname === gl.READ_FRAMEBUFFER_BINDING
		) {
			return new gl.WebGLFramebuffer(result as number);
		}
		
		// WebGLRenderbuffer
		if (pname === gl.RENDERBUFFER_BINDING) {
			return new gl.WebGLRenderbuffer(result as number);
		}
		
		// WebGLSampler
		if (pname === gl.SAMPLER_BINDING) {
			return new gl.WebGLSampler(result as number);
		}
		
		// WebGLTransformFeedback
		if (pname === gl.TRANSFORM_FEEDBACK_BINDING) {
			return new gl.WebGLTransformFeedback(result as number);
		}
		
		// WebGLVertexArrayObject
		if (pname === gl.VERTEX_ARRAY_BINDING) {
			return new gl.WebGLVertexArrayObject(result as number);
		}
		
		// WebGLProgram
		if (pname === gl.CURRENT_PROGRAM) {
			return new gl.WebGLProgram(result as number);
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
			return new gl.WebGLBuffer(result as number);
		}
		
		// WebGLTexture
		if (
			pname === gl.TEXTURE_BINDING_2D ||
			pname === gl.TEXTURE_BINDING_CUBE_MAP ||
			pname === gl.TEXTURE_BINDING_2D_ARRAY ||
			pname === gl.TEXTURE_BINDING_3D
		) {
			return new gl.WebGLTexture(result as number);
		}
		
		return result;
	};
	
	
	// ------------- Attach "Extensions"
	
	const extensions: TExtensions = createExtensions(gl);
	const extKeys = Object.keys(extensions);
	
	const _getSupportedExtensions = native.getSupportedExtensions;
	gl.getSupportedExtensions = () => extKeys;
	gl.getGLExtensions = () => _getSupportedExtensions().split(' ');
	
	gl.getExtension = <T extends keyof TExtensions>(name: T): TExtensions[T] => extensions[name];
}
