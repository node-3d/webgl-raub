import type { TNative } from './native.ts';
import type {
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
import type { TArrayValue, TFloatArray, TImage, TIntArray, TNativeImageData, TProgramBinary, TShaderPrecisionFormat, TUintArray, TWebGLState } from './types.ts';

type TMutable<T> = {
  -readonly [P in keyof T]: T[P];
};

export type TWebGLConstructors = {
	WebGLRenderingContext: typeof WebGLRenderingContextImpl;
	WebGLProgram: typeof WebGLProgramImpl;
	WebGLQuery: typeof WebGLQueryImpl;
	WebGLShader: typeof WebGLShaderImpl;
	WebGLBuffer: typeof WebGLBufferImpl;
	WebGLFramebuffer: typeof WebGLFramebufferImpl;
	WebGLRenderbuffer: typeof WebGLRenderbufferImpl;
	WebGLTexture: typeof WebGLTextureImpl;
	WebGLUniformLocation: typeof WebGLUniformLocationImpl;
	WebGLSampler: typeof WebGLSamplerImpl;
	WebGLSync: typeof WebGLSyncImpl;
	WebGLVertexArrayObject: typeof WebGLVertexArrayObjectImpl;
	WebGLActiveInfo: typeof WebGLActiveInfoImpl;
	WebGLTransformFeedback: typeof WebGLTransformFeedbackImpl;
	WebGL2RenderingContext: typeof WebGL2RenderingContextImpl;
};

type TOptional<T> = T | null | undefined;

export type TWebGLOverrides = {
	attachShader: (program?: TOptional<WebGLProgram>, shader?: TOptional<WebGLShader>) => void;
	beginQuery: (target: number, query?: TOptional<WebGLQuery>) => void;
	bindAttribLocation: (program: TOptional<WebGLProgram>, index: number, name: string) => void;
	bindBuffer: (target: number, buffer?: TOptional<WebGLBuffer>) => void;
	bindBufferBase: (target: number, index: number, buffer?: TOptional<WebGLBuffer>) => void;
	bindBufferRange: (
		target: number,
		index: number,
		buffer: TOptional<WebGLBuffer>,
		offset: number,
		size: number,
	) => void;
	bindFramebuffer: (target: number, buffer?: TOptional<WebGLFramebuffer>) => void;
	bindRenderbuffer: (target: number, buffer?: TOptional<WebGLRenderbuffer>) => void;
	bindSampler: (target: number, sampler?: TOptional<WebGLSampler>) => void;
	bindTexture: (target: number, texture?: TOptional<WebGLTexture>) => void;
	bindTransformFeedback: (target: number, feedback?: TOptional<WebGLTransformFeedback>) => void;
	bindVertexArray: (vertexArray?: TOptional<WebGLVertexArrayObject>) => void;
	bufferData: {
		(target: number, data: ArrayBufferView, usage: number, srcOffset?: number, length?: number): void;
		(target: number, size: number, usage: number): void;
	};
	bufferSubData: (target: number, offset: number, data: TArrayValue) => void;
	clientWaitSync: (sync: WebGLSync, flags: number, timeout?: number) => number;
	compileShader: (shader?: WebGLShader) => void;
	createBuffer: () => WebGLBuffer;
	createFramebuffer: () => WebGLFramebuffer;
	createProgram: () => WebGLProgram;
	createQuery: () => WebGLQuery;
	createRenderbuffer: () => WebGLRenderbuffer;
	createSampler: () => WebGLSampler;
	createShader: (type: number) => WebGLShader;
	createTexture: () => WebGLTexture;
	createTransformFeedback: () => WebGLTransformFeedback;
	createVertexArray: () => WebGLVertexArrayObject;
	deleteBuffer: (buffer?: TOptional<WebGLBuffer>) => void;
	deleteFramebuffer: (buffer?: TOptional<WebGLFramebuffer>) => void;
	deleteProgram: (program?: TOptional<WebGLProgram>) => void;
	deleteQuery: (query?: TOptional<WebGLQuery>) => void;
	deleteRenderbuffer: (buffer?: TOptional<WebGLRenderbuffer>) => void;
	deleteSampler: (sampler?: TOptional<WebGLSampler>) => void;
	deleteShader: (shader?: TOptional<WebGLShader>) => void;
	deleteSync: (sync: WebGLSync | null) => void;
	deleteTexture: (texture?: TOptional<WebGLTexture>) => void;
	deleteTransformFeedback: (feedback?: TOptional<WebGLTransformFeedback>) => void;
	deleteVertexArray: (vertexArray?: TOptional<WebGLVertexArrayObject>) => void;
	detachShader: (program?: TOptional<WebGLProgram>, shader?: TOptional<WebGLShader>) => void;
	fenceSync: (condition: number, flags: number) => WebGLSync;
	getActiveAttrib: (program: WebGLProgram, index: number) => WebGLActiveInfo;
	getActiveUniform: (program: WebGLProgram, index: number) => WebGLActiveInfo;
	getActiveUniformBlockName: (program: WebGLProgram, uniformBlockIndex: number) => string;
	getActiveUniformBlockParameter: (
		program: WebGLProgram,
		uniformBlockIndex: number,
		pname: number,
	) => boolean | number | Uint32Array | null;
	getActiveUniforms: (program: WebGLProgram, indices: readonly number[], pname: number) => number[];
	getAttachedShaders: (program: WebGLProgram) => WebGLShader[];
	getAttribLocation: (program: TOptional<WebGLProgram>, name: string) => number;
	getFragDataLocation: (program: TOptional<WebGLProgram>, name: string) => number;
	getParameter: (name: number) => unknown;
	getProgramBinary: (program?: TOptional<WebGLProgram>) => TProgramBinary;
	getProgramInfoLog: (program?: TOptional<WebGLProgram>) => string;
	getProgramParameter: (program: TOptional<WebGLProgram>, name: number) => number | boolean | null;
	getQueryParameter: (query: TOptional<WebGLQuery>, pname: number) => number | boolean | null;
	getSamplerParameter: (sampler: TOptional<WebGLSampler>, pname: number) => number | null | undefined;
	getShaderInfoLog: (shader?: TOptional<WebGLShader>) => string;
	getShaderParameter: (shader: TOptional<WebGLShader>, pname: number) => number | boolean | null;
	getShaderPrecisionFormat: (shaderType: number, precisionType: number) => TShaderPrecisionFormat;
	getShaderSource: (shader?: TOptional<WebGLShader>) => string;
	getSupportedExtensions: () => string[];
	getSyncParameter: (sync: WebGLSync, pname: number) => number | null;
	getTransformFeedbackVarying: (program: WebGLProgram, index: number) => WebGLActiveInfo;
	getUniform: (program?: TOptional<WebGLProgram>, location?: TOptional<WebGLUniformLocation>) => unknown;
	getUniformBlockIndex: (program: TOptional<WebGLProgram>, name: string) => number;
	getUniformfv: (program?: TOptional<WebGLProgram>, location?: TOptional<WebGLUniformLocation>) => number[] | undefined;
	getUniformIndices: (program?: TOptional<WebGLProgram>, names?: readonly string[]) => number[];
	getUniformLocation: (program: WebGLProgram, name: string) => WebGLUniformLocation;
	isBuffer: (buffer?: TOptional<WebGLBuffer>) => boolean;
	isFramebuffer: (buffer?: TOptional<WebGLFramebuffer>) => boolean;
	isProgram: (program?: TOptional<WebGLProgram>) => boolean;
	isQuery: (query?: TOptional<WebGLQuery>) => boolean;
	isRenderbuffer: (buffer?: TOptional<WebGLRenderbuffer>) => boolean;
	isSampler: (sampler?: TOptional<WebGLSampler>) => boolean;
	isShader: (shader?: TOptional<WebGLShader>) => boolean;
	isSync: (sync: WebGLSync) => boolean;
	isTexture: (texture?: TOptional<WebGLTexture>) => boolean;
	isTransformFeedback: (feedback?: TOptional<WebGLTransformFeedback>) => boolean;
	isVertexArray: (vertexArray?: TOptional<WebGLVertexArrayObject>) => boolean;
	linkProgram: (program?: TOptional<WebGLProgram>) => void;
	pixelStorei: (name: number, param: number | boolean) => void;
	programBinary: (program: TOptional<WebGLProgram>, binaryFormat: number, binary: string) => void;
	programParameteri: (program: TOptional<WebGLProgram>, pname: number, value: number) => void;
	samplerParameterf: (sampler: TOptional<WebGLSampler>, pname: number, param: number) => void;
	samplerParameteri: (sampler: TOptional<WebGLSampler>, pname: number, param: number) => void;
	shaderBinary: (shaders: readonly WebGLShader[], binaryFormat: number, binary: string) => void;
	shaderSource: (shader: TOptional<WebGLShader>, code: string) => void;
	texImage2D: (...args: [target: number, level: number, internalformat: number, width: number, height: number, border: number, format: number, type: number, data?: number | TNativeImageData | null] | [target: number, level: number, internalformat: number, format: number, type: number, data: TImage]) => void;
	transformFeedbackVaryings: (program: WebGLProgram, varyings: readonly string[], bufferMode: number) => void;
	uniform1f: (location: WebGLUniformLocation, x: number) => void;
	uniform1fv: (location: WebGLUniformLocation, values: TFloatArray) => void;
	uniform1i: (location: WebGLUniformLocation, value: number | boolean) => void;
	uniform1iv: (location: WebGLUniformLocation, values: TIntArray) => void;
	uniform1ui: (location: WebGLUniformLocation, x: number) => void;
	uniform1uiv: (location: WebGLUniformLocation, values: TUintArray) => void;
	uniform2f: (location: WebGLUniformLocation, x: number, y: number) => void;
	uniform2fv: (location: WebGLUniformLocation, values: TFloatArray) => void;
	uniform2i: (location: WebGLUniformLocation, x: number, y: number) => void;
	uniform2iv: (location: WebGLUniformLocation, values: TIntArray) => void;
	uniform2ui: (location: WebGLUniformLocation, x: number, y: number) => void;
	uniform2uiv: (location: WebGLUniformLocation, values: TUintArray) => void;
	uniform3f: (location: WebGLUniformLocation, x: number, y: number, z: number) => void;
	uniform3fv: (location: WebGLUniformLocation, values: TFloatArray) => void;
	uniform3i: (location: WebGLUniformLocation, x: number, y: number, z: number) => void;
	uniform3iv: (location: WebGLUniformLocation, values: TIntArray) => void;
	uniform3ui: (location: WebGLUniformLocation, x: number, y: number, z: number) => void;
	uniform3uiv: (location: WebGLUniformLocation, values: TUintArray) => void;
	uniform4f: (location: WebGLUniformLocation, x: number, y: number, z: number, w: number) => void;
	uniform4fv: (location: WebGLUniformLocation, values: TFloatArray) => void;
	uniform4i: (location: WebGLUniformLocation, x: number, y: number, z: number, w: number) => void;
	uniform4iv: (location: WebGLUniformLocation, values: TIntArray) => void;
	uniform4ui: (location: WebGLUniformLocation, x: number, y: number, z: number, w: number) => void;
	uniform4uiv: (location: WebGLUniformLocation, values: TUintArray) => void;
	uniformBlockBinding: (program: WebGLProgram, uniformBlockIndex: number, uniformBlockBinding: number) => void;
	uniformMatrix2fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix2x3fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix2x4fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix3fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix3x2fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix3x4fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix4fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix4x2fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	uniformMatrix4x3fv: (location: WebGLUniformLocation, transpose: boolean, values: TFloatArray) => void;
	vertexAttrib1fv: (index: number, values: TFloatArray) => void;
	vertexAttrib2fv: (index: number, values: TFloatArray) => void;
	vertexAttrib3fv: (index: number, values: TFloatArray) => void;
	vertexAttrib4fv: (index: number, values: TFloatArray) => void;
	vertexAttribI4iv: (index: number, values: TIntArray) => void;
	vertexAttribI4uiv: (index: number, values: TUintArray) => void;
	useProgram: (program?: TOptional<WebGLProgram>) => void;
	validateProgram: (program?: TOptional<WebGLProgram>) => void;
	waitSync: (sync: WebGLSync, flags?: number, timeout?: number) => void;
};

export type TNativeTrimmed = Omit<TNative, keyof TWebGLOverrides>;

export type TNativeMutable = TMutable<TNativeTrimmed> & TWebGLOverrides & TWebGLConstructors & TMutable<TWebGLState> & {
	__isInited: boolean;
	_versionString: string;
	canvas?: { width: number, height: number };
};
