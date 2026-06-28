// oxlint-disable max-params
import { createRequire } from 'node:module';
import { createLogger, getBin } from '@node-3d/addon-tools';
import '@node-3d/segfault';
import '@node-3d/deps-opengl';

import type { TNativeArrayData, TNativeImageData } from './types';

export type TNativeSync = object & { readonly __webglSync: unique symbol };
type TNativeResource = { readonly _: number };
type TMaybeNativeResource = TNativeResource | null | undefined;
type TNativeActiveInfo = Readonly<{ name: string; size: number; type: number }>;
type TNativeProgramBinary = Readonly<{ binary: string; binaryFormat: number }>;
type TNativeRenderTarget = readonly [framebuffer: number, texture: number];
type TNativeShaderPrecisionFormat = Readonly<{
	precision: number;
	rangeMax: number;
	rangeMin: number;
}>;
type TNativeUniformValue = boolean | number | boolean[] | Float32Array | Int32Array | Uint32Array | null;

type TNativeFunctions = Readonly<{
	init: () => void;
	createQuery: () => number;
	deleteQuery: (query?: TMaybeNativeResource) => void;
	isQuery: (query?: TMaybeNativeResource) => boolean;
	beginQuery: (target: number, query?: TMaybeNativeResource) => void;
	endQuery: (target: number) => void;
	getQueryParameter: (query: TMaybeNativeResource, pname: number) => number | boolean | null;
	getQuery: (target: number, pname: number) => number | null;
	createSampler: () => number;
	deleteSampler: (sampler?: TMaybeNativeResource) => void;
	isSampler: (sampler?: TMaybeNativeResource) => boolean;
	bindSampler: (target: number, sampler?: TMaybeNativeResource) => void;
	samplerParameterf: (sampler: TMaybeNativeResource, pname: number, param: number) => void;
	samplerParameteri: (sampler: TMaybeNativeResource, pname: number, param: number) => void;
	getSamplerParameter: (sampler: TMaybeNativeResource, pname: number) => number | null | undefined;
	fenceSync: (condition: number, flags: number) => TNativeSync;
	deleteSync: (sync: TNativeSync) => void;
	isSync: (sync: TNativeSync) => boolean;
	clientWaitSync: (sync: TNativeSync, flags: number, nanosec?: number) => number;
	waitSync: (sync: TNativeSync, flags?: number, nanosec?: number) => void;
	getSyncParameter: (sync: TNativeSync, pname: number) => number | null;
	bindAttribLocation: (program: TMaybeNativeResource, index: number, name: string) => void;
	disableVertexAttribArray: (index: number) => void;
	enableVertexAttribArray: (id: number) => void;
	getActiveAttrib: (program: TMaybeNativeResource, index: number) => TNativeActiveInfo;
	getAttribLocation: (program: TMaybeNativeResource, name: string) => number;
	getVertexAttrib: (index: number, pname: number) => boolean | number | number[] | null;
	getVertexAttribOffset: (index: number, name: number) => number;
	vertexAttrib1f: (index: number, x: number) => void;
	vertexAttrib1fv: (index: number, abv: TNativeArrayData) => void;
	vertexAttrib2f: (index: number, x: number, y: number) => void;
	vertexAttrib2fv: (index: number, abv: TNativeArrayData) => void;
	vertexAttrib3f: (index: number, x: number, y: number, z: number) => void;
	vertexAttrib3fv: (index: number, abv: TNativeArrayData) => void;
	vertexAttrib4f: (index: number, x: number, y: number, z: number, w: number) => void;
	vertexAttrib4fv: (index: number, abv: TNativeArrayData) => void;
	vertexAttribPointer: (indx: number, size: number, type: number, normalized: boolean | undefined, stride: number, offset: number) => void;
	vertexAttribIPointer: (indx: number, size: number, type: number, stride: number, offset: number) => void;
	vertexAttribI4i: (index: number, x: number, y: number, z: number, w: number) => void;
	vertexAttribI4iv: (index: number, abv: TNativeArrayData) => void;
	vertexAttribI4ui: (index: number, x: number, y: number, z: number, w: number) => void;
	vertexAttribI4uiv: (index: number, abv: TNativeArrayData) => void;
	vertexAttribDivisor: (index: number, divisor: number) => void;
	blendColor: (red: number, green: number, blue: number, alpha: number) => void;
	blendEquation: (mode: number) => void;
	blendEquationSeparate: (modeRGB: number, modeAlpha: number) => void;
	blendFunc: (sfactor: number, dfactor: number) => void;
	blendFuncSeparate: (srcRGB: number, dstRGB: number, srcAlpha: number, dstAlpha: number) => void;
	createBuffer: () => number;
	deleteBuffer: (buffer?: TMaybeNativeResource) => void;
	isBuffer: (buffer?: TMaybeNativeResource) => boolean;
	bindBuffer: (target: number, buffer?: TMaybeNativeResource) => void;
	bindBufferBase: (target: number, index: number, buffer?: TMaybeNativeResource) => void;
	bindBufferRange: (target: number, index: number, buffer: TMaybeNativeResource, offset: number, size: number) => void;
	bufferData: ((target: number, data: TNativeArrayData, usage: number, srcOffset?: number, length?: number) => void) & ((target: number, size: number, usage: number) => void);
	bufferSubData: (target: number, offset: number, arr: TNativeArrayData) => void;
	copyBufferSubData: (readTarget: number, writeTarget: number, readOffset: number, writeOffset: number, size: number) => void;
	getBufferSubData: (readTarget: number, sourceByteOffset: number, dest: ArrayBufferView, destByteOffset?: number, length?: number) => void;
	getBufferParameter: (target: number, name: number) => number;
	readBuffer: (src: number) => void;
	createFramebuffer: () => number;
	deleteFramebuffer: (buffer?: TMaybeNativeResource) => void;
	invalidateFramebuffer: (target: number, jsAttachments: readonly number[]) => void;
	invalidateSubFramebuffer: (target: number, jsAttachments: readonly number[], x: number, y: number, w: number, h: number) => void;
	isFramebuffer: (buffer?: TMaybeNativeResource) => boolean;
	bindFramebuffer: (target: number, buffer?: TMaybeNativeResource) => void;
	blitFramebuffer: (srcX0: number, srcY0: number, srcX1: number, srcY1: number, dstX0: number, dstY0: number, dstX1: number, dstY1: number, mask: number, filter: number) => void;
	checkFramebufferStatus: (target: number) => number;
	framebufferRenderbuffer: (target: number, attachment: number, renderbuffertarget: number, renderbuffer?: TMaybeNativeResource) => void;
	framebufferTexture2D: (target: number, attachment: number, textarget: number, texture: TMaybeNativeResource, level: number) => void;
	framebufferTextureLayer: (target: number, attachment: number, texture: TMaybeNativeResource, level: number, layer: number) => void;
	getFramebufferAttachmentParameter: (target: number, attachment: number, name: number) => number;
	createProgram: () => number;
	deleteProgram: (program?: TMaybeNativeResource) => void;
	isProgram: (program?: TMaybeNativeResource) => boolean;
	getProgramInfoLog: (program?: TMaybeNativeResource) => string;
	getProgramParameter: (program: TMaybeNativeResource, name: number) => number | boolean | null;
	linkProgram: (program?: TMaybeNativeResource) => void;
	useProgram: (program?: TMaybeNativeResource) => void;
	validateProgram: (program?: TMaybeNativeResource) => void;
	programParameteri: (program: TMaybeNativeResource, pname: number, value: number) => void;
	getFragDataLocation: (program: TMaybeNativeResource, name: string) => number;
	getProgramBinary: (program?: TMaybeNativeResource) => TNativeProgramBinary;
	programBinary: (program: TMaybeNativeResource, binaryFormat: number, binary: string) => void;
	getUniformBlockIndex: (program: TMaybeNativeResource, name: string) => number;
	getUniformIndices: (program?: TMaybeNativeResource, names?: readonly string[]) => number[];
	drawArrays: (mode: number, first: number, count: number) => void;
	drawElements: (mode: number, count: number, type: number, ptr: number) => void;
	drawBuffers: (jsBuffers: readonly number[]) => void;
	drawArraysInstanced: (mode: number, first: number, count: number, primcount: number) => void;
	drawElementsInstanced: (mode: number, count: number, type: number, ptr: number, primcount: number) => void;
	drawRangeElements: (mode: number, start: number, end: number, count: number, type: number, ptr: number) => void;
	createRenderbuffer: () => number;
	deleteRenderbuffer: (buffer?: TMaybeNativeResource) => void;
	isRenderbuffer: (buffer?: TMaybeNativeResource) => boolean;
	bindRenderbuffer: (target: number, buffer?: TMaybeNativeResource) => void;
	getRenderbufferParameter: (target: number, name: number) => number;
	renderbufferStorage: (target: number, internalformat: number, width: number, height: number) => void;
	renderbufferStorageMultisample: (target: number, samples: number, internalformat: number, width: number, height: number) => void;
	deleteShader: (shader?: TMaybeNativeResource) => void;
	createShader: (shaderType: number) => number;
	isShader: (shader?: TMaybeNativeResource) => boolean;
	attachShader: (program?: TMaybeNativeResource, shader?: TMaybeNativeResource) => void;
	compileShader: (shader?: TMaybeNativeResource) => void;
	detachShader: (program?: TMaybeNativeResource, shader?: TMaybeNativeResource) => void;
	getAttachedShaders: (program?: TMaybeNativeResource) => number[];
	getShaderInfoLog: (shader?: TMaybeNativeResource) => string;
	getShaderParameter: (shader: TMaybeNativeResource, pname: number) => number | boolean | null;
	getShaderSource: (shader?: TMaybeNativeResource) => string;
	getShaderPrecisionFormat: (shaderType: number, precisionType: number) => TNativeShaderPrecisionFormat;
	shaderSource: (shader: TMaybeNativeResource, code: string) => void;
	releaseShaderCompiler: () => void;
	shaderBinary: (jsShaders: readonly TNativeResource[], binaryFormat: number, binary: string) => void;
	clearStencil: (index: number) => void;
	stencilFunc: (func: number, ref: number, mask: number) => void;
	stencilFuncSeparate: (face: number, func: number, ref: number, mask: number) => void;
	stencilMask: (mask: number) => void;
	stencilMaskSeparate: (face: number, mask: number) => void;
	stencilOp: (fail: number, zfail: number, zpass: number) => void;
	stencilOpSeparate: (face: number, fail: number, zfail: number, zpass: number) => void;
	createTexture: () => number;
	deleteTexture: (texture?: TMaybeNativeResource) => void;
	isTexture: (texture?: TMaybeNativeResource) => boolean;
	bindTexture: (target: number, texture?: TMaybeNativeResource) => void;
	activeTexture: (target: number) => void;
	copyTexImage2D: (target: number, level: number, internalformat: number, x: number, y: number, width: number, height: number, border: number) => void;
	copyTexSubImage2D: (target: number, level: number, xoffset: number, yoffset: number, x: number, y: number, width: number, height: number) => void;
	generateMipmap: (target: number) => void;
	getTexParameter: (target: number, name: number) => number;
	texImage2D: (target: number, level: number, internalformat: number, width: number, height: number, border: number, format: number, type: number, data?: number | TNativeImageData | null) => void;
	texImage3D: (target: number, level: number, internalformat: number, width: number, height: number, depth: number, border: number, format: number, type: number, data?: TNativeImageData | null) => void;
	texParameterf: (target: number, name: number, param: number) => void;
	texParameteri: (target: number, name: number, param: number) => void;
	texSubImage2D: ((target: number, level: number, xoffset: number, yoffset: number, format: number, type: number, image: TNativeImageData) => void) & ((target: number, level: number, xoffset: number, yoffset: number, width: number, height: number, format: number, type: number, image?: TNativeImageData | null) => void);
	compressedTexSubImage2D: (target: number, level: number, xoffset: number, yoffset: number, width: number, height: number, format: number, image: TNativeImageData) => void;
	texStorage2D: (target: number, levels: number, format: number, width: number, height: number) => void;
	compressedTexImage2D: (target: number, level: number, internalformat: number, width: number, height: number, border: number, image: TNativeImageData) => void;
	compressedTexImage3D: (target: number, level: number, internalformat: number, width: number, height: number, depth: number, border: number, image: TNativeImageData) => void;
	compressedTexSubImage3D: (target: number, level: number, xoffset: number, yoffset: number, zoffset: number, width: number, height: number, depth: number, format: number, image: TNativeImageData) => void;
	copyTexSubImage3D: (target: number, level: number, xoffset: number, yoffset: number, zoffset: number, x: number, y: number, width: number, height: number) => void;
	texStorage3D: (target: number, level: number, internalformat: number, width: number, height: number, depth: number) => void;
	texSubImage3D: (target: number, level: number, xoffset: number, yoffset: number, zoffset: number, width: number, height: number, depth: number, format: number, type: number, image: TNativeImageData) => void;
	getActiveUniform: (program: TMaybeNativeResource, index: number) => TNativeActiveInfo;
	getUniform: (program?: TMaybeNativeResource, location?: TMaybeNativeResource) => TNativeUniformValue;
	getUniformLocation: (program: TMaybeNativeResource, name: string) => number;
	uniform1f: (location: TMaybeNativeResource, x: number) => void;
	uniform1fv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform1i: (location?: TMaybeNativeResource, x?: number | boolean) => void;
	uniform1iv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform2f: (location: TMaybeNativeResource, x: number, y: number) => void;
	uniform2fv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform2i: (location: TMaybeNativeResource, x: number, y: number) => void;
	uniform2iv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform3f: (location: TMaybeNativeResource, x: number, y: number, z: number) => void;
	uniform3fv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform3i: (location: TMaybeNativeResource, x: number, y: number, z: number) => void;
	uniform3iv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform4f: (location: TMaybeNativeResource, x: number, y: number, z: number, w: number) => void;
	uniform4fv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform4i: (location: TMaybeNativeResource, x: number, y: number, z: number, w: number) => void;
	uniform4iv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniformMatrix2fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix3fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix4fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniform1ui: (location: TMaybeNativeResource, x: number) => void;
	uniform2ui: (location: TMaybeNativeResource, x: number, y: number) => void;
	uniform3ui: (location: TMaybeNativeResource, x: number, y: number, z: number) => void;
	uniform4ui: (location: TMaybeNativeResource, x: number, y: number, z: number, w: number) => void;
	uniform1uiv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform2uiv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform3uiv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniform4uiv: (location: TMaybeNativeResource, abv: TNativeArrayData) => void;
	uniformMatrix2x3fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix2x4fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix3x2fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix3x4fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix4x2fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	uniformMatrix4x3fv: (location: TMaybeNativeResource, transpose: boolean | undefined, abv: TNativeArrayData) => void;
	getUniformfv: (program?: TMaybeNativeResource, location?: TMaybeNativeResource) => number[] | undefined;
	getActiveUniforms: (program: TMaybeNativeResource, jsIndices: readonly number[], pname: number) => number[];
	uniformBlockBinding: (program: TMaybeNativeResource, uniformBlockIndex: number, uniformBlockBinding: number) => void;
	getActiveUniformBlockParameter: (program: TMaybeNativeResource, uniformBlockIndex: number, pname: number) => boolean | number | Uint32Array | null;
	getActiveUniformBlockName: (program: TMaybeNativeResource, uniformBlockIndex: number) => string;
	createVertexArray: () => number;
	deleteVertexArray: (vertexarray?: TMaybeNativeResource) => void;
	isVertexArray: (vertexarray?: TMaybeNativeResource) => boolean;
	bindVertexArray: (vertexarray?: TMaybeNativeResource) => void;
	createTransformFeedback: () => number;
	deleteTransformFeedback: (feedback?: TMaybeNativeResource) => void;
	isTransformFeedback: (feedback?: TMaybeNativeResource) => boolean;
	bindTransformFeedback: (target: number, feedback?: TMaybeNativeResource) => void;
	beginTransformFeedback: (mode: number) => void;
	endTransformFeedback: () => void;
	pauseTransformFeedback: () => void;
	resumeTransformFeedback: () => void;
	transformFeedbackVaryings: (program: TMaybeNativeResource, jsVaryings: readonly string[], bufferMode: number) => void;
	getTransformFeedbackVarying: (program: TMaybeNativeResource, index: number) => TNativeActiveInfo;
	clear: (target: number) => void;
	clearColor: (red: number, green: number, blue: number, alpha: number) => void;
	clearDepth: (depth: number) => void;
	clearBufferfv: (buffer: number, drawBuffer: number, jsValues: readonly number[]) => void;
	clearBufferiv: (buffer: number, drawBuffer: number, jsValues: readonly number[]) => void;
	clearBufferuiv: (buffer: number, drawBuffer: number, jsValues: readonly number[]) => void;
	clearBufferfi: (buffer: number, drawBuffer: number, depth: number, stencil: number) => void;
	colorMask: (red?: boolean, green?: boolean, blue?: boolean, alpha?: boolean) => void;
	cullFace: (mode: number) => void;
	depthFunc: (id: number) => void;
	depthMask: (flag?: boolean) => void;
	depthRange: (zNear: number, zFar: number) => void;
	disable: (id: number) => void;
	enable: (id: number) => void;
	finish: () => void;
	flush: () => void;
	frontFace: (id: number) => void;
	getError: () => number;
	getParameter: (name: number) => unknown;
	getInternalformatParameter: (target: number, internalformat: number, pname: number) => Int32Array | null;
	getRenderTarget: (width: number, height: number, samples: number) => TNativeRenderTarget | null;
	getSupportedExtensions: () => string;
	hint: (target: number, mode: number) => void;
	isEnabled: (capability: number) => boolean;
	lineWidth: (width: number) => void;
	pixelStorei: (name: number, param?: number | boolean) => void;
	polygonOffset: (factor: number, units: number) => void;
	readPixels: (x: number, y: number, width: number, height: number, format: number, type: number, image: TNativeImageData) => void;
	sampleCoverage: (value: number, invert?: boolean) => void;
	scissor: (x: number, y: number, width: number, height: number) => void;
	viewport: (x: number, y: number, w: number, h: number) => void;
	getIndexedParameter: (target: number, index: number) => number | null;
}>;

type TNativeConstantName =
	| 'BROWSER_DEFAULT_WEBGL' | 'CONTEXT_LOST_WEBGL' | 'FRAMEBUFFER_INCOMPLETE_DIMENSIONS' | 'UNPACK_COLORSPACE_CONVERSION_WEBGL'
	| 'UNPACK_FLIP_Y_WEBGL' | 'UNPACK_PREMULTIPLY_ALPHA_WEBGL' | 'ACTIVE_ATTRIBUTES'
	| 'ACTIVE_TEXTURE' | 'ACTIVE_UNIFORMS' | 'ALIASED_LINE_WIDTH_RANGE' | 'ALIASED_POINT_SIZE_RANGE'
	| 'ALPHA_BITS' | 'ALPHA' | 'ALWAYS' | 'ARRAY_BUFFER_BINDING'
	| 'ARRAY_BUFFER' | 'ATTACHED_SHADERS' | 'BACK' | 'BLEND_COLOR'
	| 'BLEND_DST_ALPHA' | 'BLEND_DST_RGB' | 'BLEND_EQUATION_ALPHA' | 'BLEND_EQUATION_RGB'
	| 'BLEND_EQUATION' | 'BLEND_SRC_ALPHA' | 'BLEND_SRC_RGB' | 'BLEND'
	| 'BLUE_BITS' | 'BOOL_VEC2' | 'BOOL_VEC3' | 'BOOL_VEC4'
	| 'BOOL' | 'BUFFER_SIZE' | 'BUFFER_USAGE' | 'BYTE'
	| 'CCW' | 'CLAMP_TO_EDGE' | 'COLOR_ATTACHMENT0' | 'COLOR_BUFFER_BIT'
	| 'COLOR_CLEAR_VALUE' | 'COLOR_WRITEMASK' | 'COMPILE_STATUS' | 'COMPRESSED_TEXTURE_FORMATS'
	| 'CONSTANT_ALPHA' | 'CONSTANT_COLOR' | 'CULL_FACE_MODE' | 'CULL_FACE'
	| 'CURRENT_PROGRAM' | 'CURRENT_VERTEX_ATTRIB' | 'CW' | 'DECR_WRAP'
	| 'DECR' | 'DELETE_STATUS' | 'DEPTH_ATTACHMENT' | 'DEPTH_BITS'
	| 'DEPTH_BUFFER_BIT' | 'DEPTH_CLEAR_VALUE' | 'DEPTH_COMPONENT' | 'DEPTH_COMPONENT16'
	| 'DEPTH_FUNC' | 'DEPTH_RANGE' | 'DEPTH_STENCIL_ATTACHMENT' | 'DEPTH_STENCIL'
	| 'DEPTH_TEST' | 'DEPTH_WRITEMASK' | 'DITHER' | 'DONT_CARE'
	| 'DST_ALPHA' | 'DST_COLOR' | 'DYNAMIC_DRAW' | 'ELEMENT_ARRAY_BUFFER_BINDING'
	| 'ELEMENT_ARRAY_BUFFER' | 'EQUAL' | 'FASTEST' | 'FLOAT_MAT2'
	| 'FLOAT_MAT3' | 'FLOAT_MAT4' | 'FLOAT_VEC2' | 'FLOAT_VEC3'
	| 'FLOAT_VEC4' | 'FLOAT' | 'FRAGMENT_SHADER' | 'FRAMEBUFFER_ATTACHMENT_OBJECT_NAME'
	| 'FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE' | 'FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE' | 'FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL' | 'FRAMEBUFFER_BINDING'
	| 'FRAMEBUFFER_COMPLETE' | 'FRAMEBUFFER_INCOMPLETE_ATTACHMENT' | 'FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT' | 'FRAMEBUFFER_UNSUPPORTED'
	| 'FRAMEBUFFER' | 'FRONT_AND_BACK' | 'FRONT_FACE' | 'FRONT'
	| 'FUNC_ADD' | 'FUNC_REVERSE_SUBTRACT' | 'FUNC_SUBTRACT' | 'GENERATE_MIPMAP_HINT'
	| 'GEQUAL' | 'GREATER' | 'GREEN_BITS' | 'HIGH_FLOAT'
	| 'HIGH_INT' | 'IMPLEMENTATION_COLOR_READ_FORMAT' | 'IMPLEMENTATION_COLOR_READ_TYPE' | 'INCR_WRAP'
	| 'INCR' | 'INT_VEC2' | 'INT_VEC3' | 'INT_VEC4'
	| 'INT' | 'INVALID_ENUM' | 'INVALID_FRAMEBUFFER_OPERATION' | 'INVALID_OPERATION'
	| 'INVALID_VALUE' | 'INVERT' | 'KEEP' | 'LEQUAL'
	| 'LESS' | 'LINE_LOOP' | 'LINE_STRIP' | 'LINE_WIDTH'
	| 'LINEAR_MIPMAP_LINEAR' | 'LINEAR_MIPMAP_NEAREST' | 'LINEAR' | 'LINES'
	| 'LINK_STATUS' | 'LOW_FLOAT' | 'LOW_INT' | 'LUMINANCE_ALPHA'
	| 'LUMINANCE' | 'MAX_COMBINED_TEXTURE_IMAGE_UNITS' | 'MAX_CUBE_MAP_TEXTURE_SIZE' | 'MAX_FRAGMENT_UNIFORM_VECTORS'
	| 'MAX_RENDERBUFFER_SIZE' | 'MAX_TEXTURE_IMAGE_UNITS' | 'MAX_TEXTURE_SIZE' | 'MAX_VARYING_VECTORS'
	| 'MAX_VERTEX_ATTRIBS' | 'MAX_VERTEX_TEXTURE_IMAGE_UNITS' | 'MAX_VERTEX_UNIFORM_VECTORS' | 'MAX_VIEWPORT_DIMS'
	| 'MEDIUM_FLOAT' | 'MEDIUM_INT' | 'MIRRORED_REPEAT' | 'NEAREST_MIPMAP_LINEAR'
	| 'NEAREST_MIPMAP_NEAREST' | 'NEAREST' | 'NEVER' | 'NICEST'
	| 'NO_ERROR' | 'NONE' | 'NOTEQUAL' | 'ONE_MINUS_CONSTANT_ALPHA'
	| 'ONE_MINUS_CONSTANT_COLOR' | 'ONE_MINUS_DST_ALPHA' | 'ONE_MINUS_DST_COLOR' | 'ONE_MINUS_SRC_ALPHA'
	| 'ONE_MINUS_SRC_COLOR' | 'ONE' | 'OUT_OF_MEMORY' | 'PACK_ALIGNMENT'
	| 'POINTS' | 'POLYGON_OFFSET_FACTOR' | 'POLYGON_OFFSET_FILL' | 'POLYGON_OFFSET_UNITS'
	| 'RED_BITS' | 'RENDERBUFFER_ALPHA_SIZE' | 'RENDERBUFFER_BINDING' | 'RENDERBUFFER_BLUE_SIZE'
	| 'RENDERBUFFER_DEPTH_SIZE' | 'RENDERBUFFER_GREEN_SIZE' | 'RENDERBUFFER_HEIGHT' | 'RENDERBUFFER_INTERNAL_FORMAT'
	| 'RENDERBUFFER_RED_SIZE' | 'RENDERBUFFER_STENCIL_SIZE' | 'RENDERBUFFER_WIDTH' | 'RENDERBUFFER'
	| 'RENDERER' | 'REPEAT' | 'REPLACE' | 'RGB'
	| 'RGB5_A1' | 'RGB565' | 'RGBA' | 'RGBA4'
	| 'SAMPLE_ALPHA_TO_COVERAGE' | 'SAMPLE_BUFFERS' | 'SAMPLE_COVERAGE_INVERT' | 'SAMPLE_COVERAGE_VALUE'
	| 'SAMPLE_COVERAGE' | 'SAMPLER_2D' | 'SAMPLER_CUBE' | 'SAMPLES'
	| 'SCISSOR_BOX' | 'SCISSOR_TEST' | 'SHADER_TYPE' | 'SHADING_LANGUAGE_VERSION'
	| 'SHORT' | 'SRC_ALPHA_SATURATE' | 'SRC_ALPHA' | 'SRC_COLOR'
	| 'STATIC_DRAW' | 'STENCIL_ATTACHMENT' | 'STENCIL_BACK_FAIL' | 'STENCIL_BACK_FUNC'
	| 'STENCIL_BACK_PASS_DEPTH_FAIL' | 'STENCIL_BACK_PASS_DEPTH_PASS' | 'STENCIL_BACK_REF' | 'STENCIL_BACK_VALUE_MASK'
	| 'STENCIL_BACK_WRITEMASK' | 'STENCIL_BITS' | 'STENCIL_BUFFER_BIT' | 'STENCIL_CLEAR_VALUE'
	| 'STENCIL_FAIL' | 'STENCIL_FUNC' | 'STENCIL_INDEX' | 'STENCIL_INDEX8'
	| 'STENCIL_PASS_DEPTH_FAIL' | 'STENCIL_PASS_DEPTH_PASS' | 'STENCIL_REF' | 'STENCIL_TEST'
	| 'STENCIL_VALUE_MASK' | 'STENCIL_WRITEMASK' | 'STREAM_DRAW' | 'SUBPIXEL_BITS'
	| 'TEXTURE_2D' | 'TEXTURE_BINDING_2D' | 'TEXTURE_BINDING_CUBE_MAP' | 'TEXTURE_CUBE_MAP_NEGATIVE_X'
	| 'TEXTURE_CUBE_MAP_NEGATIVE_Y' | 'TEXTURE_CUBE_MAP_NEGATIVE_Z' | 'TEXTURE_CUBE_MAP_POSITIVE_X' | 'TEXTURE_CUBE_MAP_POSITIVE_Y'
	| 'TEXTURE_CUBE_MAP_POSITIVE_Z' | 'TEXTURE_CUBE_MAP' | 'TEXTURE_MAG_FILTER' | 'TEXTURE_MIN_FILTER'
	| 'TEXTURE_WRAP_S' | 'TEXTURE_WRAP_T' | 'TEXTURE' | 'TEXTURE0'
	| 'TEXTURE1' | 'TEXTURE10' | 'TEXTURE11' | 'TEXTURE12'
	| 'TEXTURE13' | 'TEXTURE14' | 'TEXTURE15' | 'TEXTURE16'
	| 'TEXTURE17' | 'TEXTURE18' | 'TEXTURE19' | 'TEXTURE2'
	| 'TEXTURE20' | 'TEXTURE21' | 'TEXTURE22' | 'TEXTURE23'
	| 'TEXTURE24' | 'TEXTURE25' | 'TEXTURE26' | 'TEXTURE27'
	| 'TEXTURE28' | 'TEXTURE29' | 'TEXTURE3' | 'TEXTURE30'
	| 'TEXTURE31' | 'TEXTURE4' | 'TEXTURE5' | 'TEXTURE6'
	| 'TEXTURE7' | 'TEXTURE8' | 'TEXTURE9' | 'TRIANGLE_FAN'
	| 'TRIANGLE_STRIP' | 'TRIANGLES' | 'UNPACK_ALIGNMENT' | 'UNSIGNED_BYTE'
	| 'UNSIGNED_INT' | 'UNSIGNED_SHORT_4_4_4_4' | 'UNSIGNED_SHORT_5_5_5_1' | 'UNSIGNED_SHORT_5_6_5'
	| 'UNSIGNED_SHORT' | 'VALIDATE_STATUS' | 'VENDOR' | 'VERSION'
	| 'VERTEX_ATTRIB_ARRAY_BUFFER_BINDING' | 'VERTEX_ATTRIB_ARRAY_ENABLED' | 'VERTEX_ATTRIB_ARRAY_NORMALIZED' | 'VERTEX_ATTRIB_ARRAY_POINTER'
	| 'VERTEX_ATTRIB_ARRAY_SIZE' | 'VERTEX_ATTRIB_ARRAY_STRIDE' | 'VERTEX_ATTRIB_ARRAY_TYPE' | 'VERTEX_SHADER'
	| 'VIEWPORT' | 'ZERO' | 'MAX_CLIENT_WAIT_TIMEOUT_WEBGL' | 'ACTIVE_UNIFORM_BLOCKS'
	| 'ALREADY_SIGNALED' | 'ANY_SAMPLES_PASSED_CONSERVATIVE' | 'ANY_SAMPLES_PASSED' | 'COLOR_ATTACHMENT1'
	| 'COLOR_ATTACHMENT10' | 'COLOR_ATTACHMENT11' | 'COLOR_ATTACHMENT12' | 'COLOR_ATTACHMENT13'
	| 'COLOR_ATTACHMENT14' | 'COLOR_ATTACHMENT15' | 'COLOR_ATTACHMENT2' | 'COLOR_ATTACHMENT3'
	| 'COLOR_ATTACHMENT4' | 'COLOR_ATTACHMENT5' | 'COLOR_ATTACHMENT6' | 'COLOR_ATTACHMENT7'
	| 'COLOR_ATTACHMENT8' | 'COLOR_ATTACHMENT9' | 'COLOR' | 'COMPARE_REF_TO_TEXTURE'
	| 'CONDITION_SATISFIED' | 'COPY_READ_BUFFER_BINDING' | 'COPY_READ_BUFFER' | 'COPY_WRITE_BUFFER_BINDING'
	| 'COPY_WRITE_BUFFER' | 'CURRENT_QUERY' | 'DEPTH_COMPONENT24' | 'DEPTH_COMPONENT32F'
	| 'DEPTH' | 'DEPTH24_STENCIL8' | 'DEPTH32F_STENCIL8' | 'DRAW_BUFFER0'
	| 'DRAW_BUFFER1' | 'DRAW_BUFFER10' | 'DRAW_BUFFER11' | 'DRAW_BUFFER12'
	| 'DRAW_BUFFER13' | 'DRAW_BUFFER14' | 'DRAW_BUFFER15' | 'DRAW_BUFFER2'
	| 'DRAW_BUFFER3' | 'DRAW_BUFFER4' | 'DRAW_BUFFER5' | 'DRAW_BUFFER6'
	| 'DRAW_BUFFER7' | 'DRAW_BUFFER8' | 'DRAW_BUFFER9' | 'DRAW_FRAMEBUFFER_BINDING'
	| 'DRAW_FRAMEBUFFER' | 'DYNAMIC_COPY' | 'DYNAMIC_READ' | 'FLOAT_32_UNSIGNED_INT_24_8_REV'
	| 'FLOAT_MAT2x3' | 'FLOAT_MAT2x4' | 'FLOAT_MAT3x2' | 'FLOAT_MAT3x4'
	| 'FLOAT_MAT4x2' | 'FLOAT_MAT4x3' | 'FRAGMENT_SHADER_DERIVATIVE_HINT' | 'FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE'
	| 'FRAMEBUFFER_ATTACHMENT_BLUE_SIZE' | 'FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING' | 'FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE' | 'FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE'
	| 'FRAMEBUFFER_ATTACHMENT_GREEN_SIZE' | 'FRAMEBUFFER_ATTACHMENT_RED_SIZE' | 'FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE' | 'FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER'
	| 'FRAMEBUFFER_DEFAULT' | 'FRAMEBUFFER_INCOMPLETE_MULTISAMPLE' | 'HALF_FLOAT' | 'INT_2_10_10_10_REV'
	| 'INT_SAMPLER_2D_ARRAY' | 'INT_SAMPLER_2D' | 'INT_SAMPLER_3D' | 'INT_SAMPLER_CUBE'
	| 'INTERLEAVED_ATTRIBS' | 'INVALID_INDEX' | 'MAX_3D_TEXTURE_SIZE' | 'MAX_ARRAY_TEXTURE_LAYERS'
	| 'MAX_COLOR_ATTACHMENTS' | 'MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS' | 'MAX_COMBINED_UNIFORM_BLOCKS' | 'MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS'
	| 'MAX_DRAW_BUFFERS' | 'MAX_ELEMENT_INDEX' | 'MAX_ELEMENTS_INDICES' | 'MAX_ELEMENTS_VERTICES'
	| 'MAX_FRAGMENT_INPUT_COMPONENTS' | 'MAX_FRAGMENT_UNIFORM_BLOCKS' | 'MAX_FRAGMENT_UNIFORM_COMPONENTS' | 'MAX_PROGRAM_TEXEL_OFFSET'
	| 'MAX_SAMPLES' | 'MAX_SERVER_WAIT_TIMEOUT' | 'MAX_TEXTURE_LOD_BIAS' | 'MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS'
	| 'MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS' | 'MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS' | 'MAX_UNIFORM_BLOCK_SIZE' | 'MAX_UNIFORM_BUFFER_BINDINGS'
	| 'MAX_VARYING_COMPONENTS' | 'MAX_VERTEX_OUTPUT_COMPONENTS' | 'MAX_VERTEX_UNIFORM_BLOCKS' | 'MAX_VERTEX_UNIFORM_COMPONENTS'
	| 'MAX' | 'MIN_PROGRAM_TEXEL_OFFSET' | 'MIN' | 'OBJECT_TYPE'
	| 'PACK_ROW_LENGTH' | 'PACK_SKIP_PIXELS' | 'PACK_SKIP_ROWS' | 'PIXEL_PACK_BUFFER_BINDING'
	| 'PIXEL_PACK_BUFFER' | 'PIXEL_UNPACK_BUFFER_BINDING' | 'PIXEL_UNPACK_BUFFER' | 'QUERY_RESULT_AVAILABLE'
	| 'QUERY_RESULT' | 'R11F_G11F_B10F' | 'R16F' | 'R16I'
	| 'R16UI' | 'R32F' | 'R32I' | 'R32UI'
	| 'R8_SNORM' | 'R8' | 'R8I' | 'R8UI'
	| 'RASTERIZER_DISCARD' | 'READ_BUFFER' | 'READ_FRAMEBUFFER_BINDING' | 'READ_FRAMEBUFFER'
	| 'RED_INTEGER' | 'RED' | 'RENDERBUFFER_SAMPLES' | 'RG_INTEGER'
	| 'RG' | 'RG16F' | 'RG16I' | 'RG16UI'
	| 'RG32F' | 'RG32I' | 'RG32UI' | 'RG8_SNORM'
	| 'RG8' | 'RG8I' | 'RG8UI' | 'RGB_INTEGER'
	| 'RGB10_A2' | 'RGB10_A2UI' | 'RGB16F' | 'RGB16I'
	| 'RGB16UI' | 'RGB32F' | 'RGB32I' | 'RGB32UI'
	| 'RGB8_SNORM' | 'RGB8' | 'RGB8I' | 'RGB8UI'
	| 'RGB9_E5' | 'RGBA_INTEGER' | 'RGBA16F' | 'RGBA16I'
	| 'RGBA16UI' | 'RGBA32F' | 'RGBA32I' | 'RGBA32UI'
	| 'RGBA8_SNORM' | 'RGBA8' | 'RGBA8I' | 'RGBA8UI'
	| 'SAMPLER_2D_ARRAY_SHADOW' | 'SAMPLER_2D_ARRAY' | 'SAMPLER_2D_SHADOW' | 'SAMPLER_3D'
	| 'SAMPLER_BINDING' | 'SAMPLER_CUBE_SHADOW' | 'SEPARATE_ATTRIBS' | 'SIGNALED'
	| 'SIGNED_NORMALIZED' | 'SRGB' | 'SRGB8_ALPHA8' | 'SRGB8'
	| 'STATIC_COPY' | 'STATIC_READ' | 'STENCIL' | 'STREAM_COPY'
	| 'STREAM_READ' | 'SYNC_CONDITION' | 'SYNC_FENCE' | 'SYNC_FLAGS'
	| 'SYNC_FLUSH_COMMANDS_BIT' | 'SYNC_GPU_COMMANDS_COMPLETE' | 'SYNC_STATUS' | 'TEXTURE_2D_ARRAY'
	| 'TEXTURE_3D' | 'TEXTURE_BASE_LEVEL' | 'TEXTURE_BINDING_2D_ARRAY' | 'TEXTURE_BINDING_3D'
	| 'TEXTURE_COMPARE_FUNC' | 'TEXTURE_COMPARE_MODE' | 'TEXTURE_IMMUTABLE_FORMAT' | 'TEXTURE_IMMUTABLE_LEVELS'
	| 'TEXTURE_MAX_LEVEL' | 'TEXTURE_MAX_LOD' | 'TEXTURE_MIN_LOD' | 'TEXTURE_WRAP_R'
	| 'TIMEOUT_EXPIRED' | 'TIMEOUT_IGNORED' | 'TRANSFORM_FEEDBACK_ACTIVE' | 'TRANSFORM_FEEDBACK_BINDING'
	| 'TRANSFORM_FEEDBACK_BUFFER_BINDING' | 'TRANSFORM_FEEDBACK_BUFFER_MODE' | 'TRANSFORM_FEEDBACK_BUFFER_SIZE' | 'TRANSFORM_FEEDBACK_BUFFER_START'
	| 'TRANSFORM_FEEDBACK_BUFFER' | 'TRANSFORM_FEEDBACK_PAUSED' | 'TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN' | 'TRANSFORM_FEEDBACK_VARYINGS'
	| 'TRANSFORM_FEEDBACK' | 'UNIFORM_ARRAY_STRIDE' | 'UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES' | 'UNIFORM_BLOCK_ACTIVE_UNIFORMS'
	| 'UNIFORM_BLOCK_BINDING' | 'UNIFORM_BLOCK_DATA_SIZE' | 'UNIFORM_BLOCK_INDEX' | 'UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER'
	| 'UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER' | 'UNIFORM_BUFFER_BINDING' | 'UNIFORM_BUFFER_OFFSET_ALIGNMENT' | 'UNIFORM_BUFFER_SIZE'
	| 'UNIFORM_BUFFER_START' | 'UNIFORM_BUFFER' | 'UNIFORM_IS_ROW_MAJOR' | 'UNIFORM_MATRIX_STRIDE'
	| 'UNIFORM_OFFSET' | 'UNIFORM_SIZE' | 'UNIFORM_TYPE' | 'UNPACK_IMAGE_HEIGHT'
	| 'UNPACK_ROW_LENGTH' | 'UNPACK_SKIP_IMAGES' | 'UNPACK_SKIP_PIXELS' | 'UNPACK_SKIP_ROWS'
	| 'UNSIGNALED' | 'UNSIGNED_INT_10F_11F_11F_REV' | 'UNSIGNED_INT_2_10_10_10_REV' | 'UNSIGNED_INT_24_8'
	| 'UNSIGNED_INT_5_9_9_9_REV' | 'UNSIGNED_INT_SAMPLER_2D_ARRAY' | 'UNSIGNED_INT_SAMPLER_2D' | 'UNSIGNED_INT_SAMPLER_3D'
	| 'UNSIGNED_INT_SAMPLER_CUBE' | 'UNSIGNED_INT_VEC2' | 'UNSIGNED_INT_VEC3' | 'UNSIGNED_INT_VEC4'
	| 'UNSIGNED_NORMALIZED' | 'VERTEX_ARRAY_BINDING' | 'VERTEX_ATTRIB_ARRAY_DIVISOR' | 'VERTEX_ATTRIB_ARRAY_INTEGER'
	| 'WAIT_FAILED' | 'ACTIVE_ATTRIBUTE_MAX_LENGTH' | 'ACTIVE_UNIFORM_MAX_LENGTH' | 'CLAMP_TO_BORDER'
	| 'CLAMP' | 'EXTENSIONS' | 'FALSE' | 'FIXED'
	| 'NUM_COMPRESSED_TEXTURE_FORMATS' | 'NUM_SHADER_BINARY_FORMATS' | 'POINT_SPRITE' | 'PROGRAM_POINT_SIZE'
	| 'SHADER_BINARY_FORMATS' | 'SHADER_COMPILER' | 'SHADER_SOURCE_LENGTH' | 'TRUE';

type TNativeConstants = Record<TNativeConstantName, number>;

export type TNative = TNativeFunctions & TNativeConstants;

createLogger({ name: 'webgl' });

const loadAddon = createRequire(import.meta.url);

export const native = loadAddon(`../${getBin()}/webgl.node`) as TNative;
