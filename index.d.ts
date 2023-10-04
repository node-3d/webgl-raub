declare module "webgl-raub" {
	
	export type TActiveInfo = Readonly<{
		size: number;
		type: number;
		name: string;
	}>;
	
	export type TContextAttributes = Readonly<{
		alpha: boolean,
		antialias: boolean,
		depth: boolean,
		failIfMajorPerformanceCaveat: boolean,
		powerPreference: string,
		premultipliedAlpha: boolean,
		preserveDrawingBuffer: boolean,
		stencil: boolean,
		desynchronized: boolean,
	}>;
	
	export type TResourceId = number;
	
	export type TSize = Readonly<{ width: number; height: number }>;
	
	export type TImage = TSize & Readonly<{
		data: Buffer;
		noflip?: boolean;
	}>;
	
	export type TShaderArray = number[] | Float32Array;
	
	export class TGLObject {
		constructor(_: TResourceId);
		_: TResourceId;
	}
	
	export class TGLActiveInfo {
		constructor(_: TActiveInfo);
		_: TActiveInfo;
		size: number;
		type: number;
		name: string;
	}
	
	export class WebGLRenderingContext extends TGLObject {}
	export class WebGLProgram extends TGLObject {}
	export class WebGLQuery extends TGLObject {}
	export class WebGLShader extends TGLObject {}
	export class WebGLVertexArrayObject extends TGLObject {}
	export class WebGLBuffer extends TGLObject {}
	export class WebGLVertexArray extends TGLObject {}
	export class WebGLFramebuffer extends TGLObject {}
	export class WebGLRenderbuffer extends TGLObject {}
	export class WebGLTexture extends TGLObject {}
	export class WebGLUniformLocation extends TGLObject {}
	export class WebGLActiveInfo extends TGLActiveInfo {}
	export class WebGLTransformFeedback extends TGLObject {}
	
	const webgl: WebGL;
	export default webgl;
	
	export interface WebGL {
		contextAttributes: TContextAttributes;
		getContextAttributes: () => TContextAttributes;
		
		createQuery: ()=> WebGLQuery;
		deleteQuery: (query: WebGLQuery)=> void;
		
		bindAttribLocation: (program: WebGLProgram, index: number, name: string) => void;
		disableVertexAttribArray: (index: number) => void;
		enableVertexAttribArray: (id: number) => void;
		getActiveAttrib: (program: WebGLProgram, index: number) => TActiveInfo;
		getAttribLocation: (program: WebGLProgram, name: string) => number;
		getVertexAttrib: (index: number, name: number) => (boolean | number | number[]);
		getVertexAttribOffset: (index: number, name: number) => number;
		vertexAttrib1f: (location: number, x: number) => void;
		vertexAttrib1fv: (location: number, v: TShaderArray) => void;
		vertexAttrib2f: (location: number, x: number, y: number) => void;
		vertexAttrib2fv: (location: number, v: TShaderArray) => void;
		vertexAttrib3f: (location: number, x: number, y: number, z: number) => void;
		vertexAttrib3fv: (location: number, v: TShaderArray) => void;
		vertexAttrib4f: (location: number, x: number, y: number, z: number, w: number) => void;
		vertexAttrib4fv: (location: number, v: TShaderArray) => void;
		vertexAttribPointer: (index: number, size: number, type: number, isNormalized: boolean, stride: number, offset: number) => number;
		vertexAttribIPointer: (
			indx: number,
			size: number,
			type: number,
			stride: number,
			offset: number,
		) => void;
		blendColor: (
			red: number,
			green: number,
			blue: number,
			alpha: number,
		) => void;
		blendEquation: (mode: number) => void;
		blendEquationSeparate: (modeRGB: number, modeAlpha: number) => void;
		blendFunc: (sfactor: number, dfactor: number) => void;
		blendFuncSeparate: (
			srcRGB: number,
			dstRGB: number,
			srcAlpha: number,
			dstAlpha: number,
		) => void;
		createBuffer: () => WebGLBuffer;
		deleteBuffer: (buffer: WebGLBuffer) => void;
		isBuffer: (buffer: WebGLBuffer) => boolean;
		bindBuffer: (target: number, buffer: WebGLBuffer) => void;
		bindBufferBase: (
			target: number,
			index: number,
			buffer: WebGLBuffer,
		) => void;
		bindBufferRange: (
			target: number,
			index: number,
			buffer: WebGLBuffer,
			offset: number,
			size: number,
		) => void;
		bufferSubData: (
			target: number,
			offset: number,
			v: number[] | Float32Array,
		) => void;
		bufferData: (
			target: number,
			value: number | number[] | Float32Array | Uint16Array,
			usage: number,
			srcOffset?: number,
			length?: number,
		) => void;
		bufferSubData: (
			target: number,
			offset: number,
			arr: Float32Array,
		) => void;
		copyBufferSubData: (
			readTarget: number,
			writeTarget: number,
			readOffset: number,
			writeOffset: number,
			size: number,
		) => void;
		getBufferSubData: (
			readTarget: number,
			sourceByteOffset: number,
			dest: Float32Array,
			destByteOffset?: number,
			length?: number,
		) => void;
		getBufferParameter: (target: number, name: number) => number;
		createFramebuffer: () => WebGLFramebuffer;
		deleteFramebuffer: (frameBuffer: WebGLFramebuffer) => void;
		invalidateFramebuffer: (target: number, attachments: number[]) => void;
		isFramebuffer: (frameBuffer: WebGLFramebuffer) => boolean;
		bindFramebuffer: (target: number, buffer?: WebGLFramebuffer) => void;
		blitFramebuffer: (
			srcX0: number,
			srcY0: number,
			srcX1: number,
			srcY1: number,
			dstX0: number,
			dstY0: number,
			dstX1: number,
			dstY1: number,
			mask: number,
			filter: number,
		) => void;
		checkFramebufferStatus: (target: number) => number;
		framebufferRenderbuffer: (
			target: number,
			attachment: number,
			renderbuffertarget: number,
			renderbuffer: WebGLRenderbuffer,
		) => void;
		framebufferTexture2D: (
			target: number,
			attachment: number,
			textarget: number,
			texture: WebGLTexture,
			level: number,
		) => void;
		framebufferTextureLayer: (
			target: number,
			attachment: number,
			texture: WebGLTexture,
			level: number,
			layer: number,
		) => void;
		getFramebufferAttachmentParameter: (
			target: number,
			attachment: number,
			name: number,
		) => number;
		createProgram: () => WebGLProgram;
		deleteProgram: (program: WebGLProgram) => void;
		isProgram: (program: WebGLProgram) => boolean;
		getProgramInfoLog: (program: WebGLProgram) => string;
		getProgramParameter: (program: WebGLProgram, name: number) => (boolean | number);
		linkProgram: (program: WebGLProgram) => void;
		useProgram: (program: WebGLProgram) => void;
		validateProgram: (program: WebGLProgram) => void;
		createRenderbuffer: () => WebGLRenderbuffer;
		deleteRenderbuffer: (renderBuffer: WebGLRenderbuffer) => void;
		isRenderbuffer: (renderBuffer: WebGLRenderbuffer) => boolean;
		bindRenderbuffer: (target: number, renderBuffer?: WebGLRenderbuffer) => void;
		getRenderbufferParameter: (target: number, name: number) => number;
		renderbufferStorage: (
			target: number,
			internalformat: number,
			width: number,
			height: number,
		) => void;
		renderbufferStorageMultisample: (
			target: number,
			samples: number,
			internalformat: number,
			width: number,
			height: number,
		) => void;
		createShader: (type: number) => WebGLShader;
		deleteShader: (shader: WebGLShader) => void;
		isShader: (shader: WebGLShader) => boolean;
		attachShader: (program: WebGLProgram, shader: WebGLShader) => void;
		compileShader: (shader: WebGLShader) => void;
		detachShader: (program: WebGLProgram, shader: WebGLShader) => void;
		getAttachedShaders: (program: WebGLProgram) => (number[]);
		getShaderInfoLog: (shader: WebGLShader) => string;
		getShaderParameter: (shader: WebGLShader, pname: number) => (number | boolean);
		getShaderSource: (shader: WebGLShader) => string;
		getShaderPrecisionFormat: (shaderType: number, precisionType: number) => string;
		shaderSource: (shader: WebGLShader, code: string) => void;
		clearStencil: (index: number) => void;
		stencilFunc: (
			func: number,
			ref: number,
			mask: number,
		) => void;
		stencilFuncSeparate: (
			face: number,
			func: number,
			ref: number,
			mask: number,
		) => void;
		stencilMask: (mask: number) => void;
		stencilMaskSeparate: (face: number, mask: number) => void;
		stencilOp: (
			fail: number,
			zfail: number,
			zpass: number,
		) => void;
		stencilOpSeparate: (
			face: number,
			fail: number,
			zfail: number,
			zpass: number,
		) => void;
		createTexture: () => WebGLTexture;
		deleteTexture: (texture: WebGLTexture) => void;
		isTexture: (texture: WebGLTexture) => boolean;
		bindTexture: (target: number, texture?: WebGLTexture) => void;
		activeTexture: (textureUnit: number) => void;
		copyTexImage2D: (
			target: number,
			level: number,
			internalformat: number,
			x: number,
			y: number,
			width: number,
			height: number,
			border: number,
		) => void;
		copyTexSubImage2D: (
			target: number,
			level: number,
			xoffset: number,
			yoffset: number,
			x: number,
			y: number,
			width: number,
			height: number,
		) => void;
		generateMipmap: (target: number) => void;
		getTexParameter: (target: number, name: number) => number;
		texImage2D: (
			target: number,
			level: number,
			internalformat: number,
			width: number,
			height: number,
			border: number,
			format: number,
			type: number,
			ptr?: TImage | number,
		) => void;
		texImage3D: (
			target: number,
			level: number,
			internalformat: number,
			width: number,
			height: number,
			depth: number,
			border: number,
			format: number,
			type: number,
			ptr?: TImage,
		) => void;
		texParameterf: (
			target: number,
			name: number,
			param: number,
		) => void;
		texParameteri: (
			target: number,
			name: number,
			param: number,
		) => void;
		texSubImage2D: (
			target: number,
			level: number,
			xoffset: number,
			yoffset: number,
			width: number,
			height: number,
			format: number,
			type: number,
			image?: TImage,
		) => void;
		compressedTexSubImage2D: (
			target: number,
			level: number,
			xoffset: number,
			yoffset: number,
			width: number,
			height: number,
			format: number,
			image?: TImage,
		) => void;
		texStorage2D: (
			target: number,
			levels: number,
			internalformat: number,
			width: number,
			height: number,
		) => void;
		getActiveUniform: (program: WebGLProgram, index: number) => TActiveInfo;
		getUniform: (program: WebGLProgram, location: WebGLUniformLocation) => (undefined | number[]);
		getUniformLocation: (program: WebGLProgram, name: string) => WebGLUniformLocation;
		uniform1f: (location: WebGLUniformLocation, x: number) => void;
		uniform1fv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform1i: (location: WebGLUniformLocation, x: number) => void;
		uniform1iv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform2f: (location: WebGLUniformLocation, x: number, y: number) => void;
		uniform2fv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform2i: (location: WebGLUniformLocation, x: number, y: number) => void;
		uniform2iv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform3f: (location: WebGLUniformLocation, x: number, y: number, z: number) => void;
		uniform3fv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform3i: (location: WebGLUniformLocation, x: number, y: number, z: number) => void;
		uniform3iv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform4f: (location: WebGLUniformLocation, x: number, y: number, z: number, w: number) => void;
		uniform4fv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniform4i: (location: WebGLUniformLocation, x: number, y: number, z: number, w: number) => void;
		uniform4iv: (location: WebGLUniformLocation, values: TShaderArray) => void;
		uniformMatrix2fv: (location: WebGLUniformLocation, transpose: boolean, values: TShaderArray) => void;
		uniformMatrix3fv: (location: WebGLUniformLocation, transpose: boolean, values: TShaderArray) => void;
		uniformMatrix4fv: (location: WebGLUniformLocation, transpose: boolean, values: TShaderArray) => void;
		createVertexArray: () => WebGLVertexArray;
		deleteVertexArray: (vertexArray: WebGLVertexArray) => void;
		isVertexArray: (vertexArray: WebGLVertexArray) => boolean;
		bindVertexArray: (vertexarray: WebGLVertexArray) => void;
		drawArraysInstanced: (
			mode: number,
			first: number,
			count: number,
			primcount: number,
		) => void;
		drawElementsInstanced: (
			mode: number,
			count: number,
			type: number,
			ptr: number,
			primcount: number,
		) => void;
		vertexAttribDivisor: (index: number, divisor: number) => void;
		createTransformFeedback: () => WebGLTransformFeedback;
		deleteTransformFeedback: (transformFeedback: WebGLTransformFeedback) => void;
		isTransformFeedback: (transformFeedback: WebGLTransformFeedback) => boolean;
		bindTransformFeedback: (target: number, transformFeedback: WebGLTransformFeedback) => void;
		beginTransformFeedback: (mode: number) => void;
		endTransformFeedback: () => void;
		pauseTransformFeedback: () => void;
		resumeTransformFeedback: () => void;
		transformFeedbackVaryings: (
			program: WebGLProgram,
			jsVaryings: string[],
			bufferMode: number,
		) => void;
		getTransformFeedbackVarying: (program: WebGLProgram, index: number) => TActiveInfo;
		clear: (target: number) => void;
		clearColor: (
			red: number,
			green: number,
			blue: number,
			alpha: number,
		) => void;
		clearDepth: (depth: number) => void;
		clearBufferfv: (buffer: number, drawBuffer: number, value: number[]) => void;
		clearBufferiv: (buffer: number, drawBuffer: number, value: number[]) => void;
		clearBufferuiv: (buffer: number, drawBuffer: number, value: number[]) => void;
		clearBufferfi: (buffer: number, drawBuffer: number, depth: number, stencil: number) => void;
		colorMask: (
			red: boolean,
			green: boolean,
			blue: boolean,
			alpha: boolean,
		) => void;
		cullFace: (mode: number) => void;
		depthFunc: (id: number) => void;
		depthMask: (flag: boolean) => void;
		depthRange: (zNear: number, zFar: number) => void;
		disable: (id: number) => void;
		drawArrays: (
			mode: number,
			first: number,
			count: number,
		) => void;
		drawElements: (
			mode: number,
			count: number,
			type: number,
			ptr: number,
		) => void;
		drawBuffers: (buffers: number[]) => void;
		enable: (id: number) => void;
		finish: () => void;
		flush: () => void;
		frontFace: (id: number) => void;
		getError: () => number;
		getParameter: (name: number) => (number | boolean | number[] | string | boolean[]);
		getInternalformatParameter: (
			target: number,
			internalformat: number,
			name: number,
		) => (Int32Array | null);
		getRenderTarget: (
			width: number,
			height: number,
			samples: number,
		) => (number[] | null);
		getSupportedExtensions: () => (string[]);
		getExtension: (name: string) => unknown;
		hint: (target: number, mode: number) => void;
		isEnabled: (capability: number) => boolean;
		lineWidth: (width: number) => void;
		pixelStorei: (name: number, param: number) => void;
		polygonOffset: (factor: number, units: number) => void;
		readPixels: (
			x: number,
			y: number,
			width: number,
			height: number,
			format: number,
			type: number,
			image: TImage,
		) => void;
		sampleCoverage: (value: number, invert: boolean) => void;
		scissor: (
			x: number,
			y: number,
			width: number,
			height: number,
		) => void;
		viewport: (
			x: number,
			y: number,
			w: number,
			h: number,
		) => void;
		
		drawingBufferWidth: number;
		drawingBufferHeight: number;
		
		DEPTH_BUFFER_BIT: number;
		STENCIL_BUFFER_BIT: number;
		COLOR_BUFFER_BIT: number;
		FALSE: number;
		TRUE: number;
		POINTS: number;
		LINES: number;
		LINE_LOOP: number;
		LINE_STRIP: number;
		TRIANGLES: number;
		TRIANGLE_STRIP: number;
		TRIANGLE_FAN: number;
		ZERO: number;
		ONE: number;
		SRC_COLOR: number;
		ONE_MINUS_SRC_COLOR: number;
		SRC_ALPHA: number;
		ONE_MINUS_SRC_ALPHA: number;
		DST_ALPHA: number;
		ONE_MINUS_DST_ALPHA: number;
		DST_COLOR: number;
		ONE_MINUS_DST_COLOR: number;
		SRC_ALPHA_SATURATE: number;
		FUNC_ADD: number;
		BLEND_EQUATION: number;
		BLEND_EQUATION_RGB: number;
		BLEND_EQUATION_ALPHA: number;
		FUNC_SUBTRACT: number;
		FUNC_REVERSE_SUBTRACT: number;
		BLEND_DST_RGB: number;
		BLEND_SRC_RGB: number;
		BLEND_DST_ALPHA: number;
		BLEND_SRC_ALPHA: number;
		CONSTANT_COLOR: number;
		ONE_MINUS_CONSTANT_COLOR: number;
		CONSTANT_ALPHA: number;
		ONE_MINUS_CONSTANT_ALPHA: number;
		BLEND_COLOR: number;
		ARRAY_BUFFER: number;
		ELEMENT_ARRAY_BUFFER: number;
		ARRAY_BUFFER_BINDING: number;
		ELEMENT_ARRAY_BUFFER_BINDING: number;
		STREAM_DRAW: number;
		STATIC_DRAW: number;
		DYNAMIC_DRAW: number;
		BUFFER_SIZE: number;
		BUFFER_USAGE: number;
		CURRENT_VERTEX_ATTRIB: number;
		FRONT: number;
		BACK: number;
		FRONT_AND_BACK: number;
		TEXTURE_2D: number;
		TEXTURE_2D_ARRAY: number;
		TEXTURE_3D: number;
		CULL_FACE: number;
		BLEND: number;
		DITHER: number;
		STENCIL_TEST: number;
		DEPTH_TEST: number;
		SCISSOR_TEST: number;
		POLYGON_OFFSET_FILL: number;
		SAMPLE_ALPHA_TO_COVERAGE: number;
		SAMPLE_COVERAGE: number;
		NO_ERROR: number;
		INVALID_ENUM: number;
		INVALID_VALUE: number;
		INVALID_OPERATION: number;
		OUT_OF_MEMORY: number;
		CW: number;
		CCW: number;
		LINE_WIDTH: number;
		ALIASED_POINT_SIZE_RANGE: number;
		ALIASED_LINE_WIDTH_RANGE: number;
		CULL_FACE_MODE: number;
		FRONT_FACE: number;
		DEPTH_RANGE: number;
		DEPTH_WRITEMASK: number;
		DEPTH_CLEAR_VALUE: number;
		DEPTH_FUNC: number;
		STENCIL_CLEAR_VALUE: number;
		STENCIL_FUNC: number;
		STENCIL_FAIL: number;
		STENCIL_PASS_DEPTH_FAIL: number;
		STENCIL_PASS_DEPTH_PASS: number;
		STENCIL_REF: number;
		STENCIL_VALUE_MASK: number;
		STENCIL_WRITEMASK: number;
		STENCIL_BACK_FUNC: number;
		STENCIL_BACK_FAIL: number;
		STENCIL_BACK_PASS_DEPTH_FAIL: number;
		STENCIL_BACK_PASS_DEPTH_PASS: number;
		STENCIL_BACK_REF: number;
		STENCIL_BACK_VALUE_MASK: number;
		STENCIL_BACK_WRITEMASK: number;
		VIEWPORT: number;
		SCISSOR_BOX: number;
		COLOR_CLEAR_VALUE: number;
		COLOR_WRITEMASK: number;
		UNPACK_ALIGNMENT: number;
		PACK_ALIGNMENT: number;
		MAX_TEXTURE_SIZE: number;
		MAX_VIEWPORT_DIMS: number;
		SUBPIXEL_BITS: number;
		RED_BITS: number;
		GREEN_BITS: number;
		BLUE_BITS: number;
		ALPHA_BITS: number;
		DEPTH_BITS: number;
		STENCIL_BITS: number;
		POLYGON_OFFSET_UNITS: number;
		POLYGON_OFFSET_FACTOR: number;
		TEXTURE_BINDING_2D: number;
		SAMPLE_BUFFERS: number;
		SAMPLES: number;
		SAMPLE_COVERAGE_VALUE: number;
		SAMPLE_COVERAGE_INVERT: number;
		NUM_COMPRESSED_TEXTURE_FORMATS: number;
		COMPRESSED_TEXTURE_FORMATS: number;
		DONT_CARE: number;
		FASTEST: number;
		NICEST: number;
		GENERATE_MIPMAP_HINT: number;
		BYTE: number;
		UNSIGNED_BYTE: number;
		SHORT: number;
		UNSIGNED_SHORT: number;
		INT: number;
		UNSIGNED_INT: number;
		UNSIGNED_INT_24_8: number;
		FLOAT: number;
		FIXED: number;
		DEPTH_COMPONENT: number;
		ALPHA: number;
		RGB: number;
		RGBA: number;
		LUMINANCE: number;
		LUMINANCE_ALPHA: number;
		RGBA4: number;
		RGB5_A1: number;
		R16F: number;
		R16I: number;
		R16UI: number;
		R32F: number;
		R32I: number;
		R32UI: number;
		R8: number;
		R8I: number;
		R8UI: number;
		RED: number;
		RED_INTEGER: number;
		RG: number;
		RG_INTEGER: number;
		RG16F: number;
		RG32F: number;
		RG8: number;
		RGBA_INTEGER: number;
		RGBA16F: number;
		RGBA32F: number;
		RGBA8: number;
		SRGB8_ALPHA8: number;
		UNSIGNED_SHORT_4_4_4_4: number;
		UNSIGNED_SHORT_5_5_5_1: number;
		UNSIGNED_SHORT_5_6_5: number;
		FRAGMENT_SHADER: number;
		VERTEX_SHADER: number;
		MAX_VERTEX_ATTRIBS: number;
		MAX_VERTEX_UNIFORM_VECTORS: number;
		MAX_VARYING_VECTORS: number;
		MAX_COMBINED_TEXTURE_IMAGE_UNITS: number;
		MAX_VERTEX_TEXTURE_IMAGE_UNITS: number;
		MAX_TEXTURE_IMAGE_UNITS: number;
		MAX_FRAGMENT_UNIFORM_VECTORS: number;
		SHADER_TYPE: number;
		DELETE_STATUS: number;
		LINK_STATUS: number;
		VALIDATE_STATUS: number;
		ATTACHED_SHADERS: number;
		ACTIVE_UNIFORMS: number;
		ACTIVE_UNIFORM_MAX_LENGTH: number;
		ACTIVE_ATTRIBUTES: number;
		ACTIVE_ATTRIBUTE_MAX_LENGTH: number;
		SHADING_LANGUAGE_VERSION: number;
		CURRENT_PROGRAM: number;
		UNIFORM_BUFFER: number;
		NEVER: number;
		LESS: number;
		EQUAL: number;
		LEQUAL: number;
		GREATER: number;
		NOTEQUAL: number;
		GEQUAL: number;
		ALWAYS: number;
		KEEP: number;
		REPLACE: number;
		INCR: number;
		DECR: number;
		INVERT: number;
		INCR_WRAP: number;
		DECR_WRAP: number;
		PROGRAM_POINT_SIZE: number;
		POINT_SPRITE: number;
		VENDOR: number;
		RENDERER: number;
		VERSION: number;
		EXTENSIONS: number;
		NEAREST: number;
		LINEAR: number;
		NEAREST_MIPMAP_NEAREST: number;
		LINEAR_MIPMAP_NEAREST: number;
		NEAREST_MIPMAP_LINEAR: number;
		LINEAR_MIPMAP_LINEAR: number;
		TEXTURE_MAG_FILTER: number;
		TEXTURE_MIN_FILTER: number;
		TEXTURE_WRAP_S: number;
		TEXTURE_WRAP_T: number;
		TEXTURE_WRAP_R: number;
		TEXTURE: number;
		TEXTURE_CUBE_MAP: number;
		TEXTURE_BINDING_CUBE_MAP: number;
		TEXTURE_CUBE_MAP_POSITIVE_X: number;
		TEXTURE_CUBE_MAP_NEGATIVE_X: number;
		TEXTURE_CUBE_MAP_POSITIVE_Y: number;
		TEXTURE_CUBE_MAP_NEGATIVE_Y: number;
		TEXTURE_CUBE_MAP_POSITIVE_Z: number;
		TEXTURE_CUBE_MAP_NEGATIVE_Z: number;
		MAX_CUBE_MAP_TEXTURE_SIZE: number;
		TEXTURE0: number;
		TEXTURE1: number;
		TEXTURE2: number;
		TEXTURE3: number;
		TEXTURE4: number;
		TEXTURE5: number;
		TEXTURE6: number;
		TEXTURE7: number;
		TEXTURE8: number;
		TEXTURE9: number;
		TEXTURE10: number;
		TEXTURE11: number;
		TEXTURE12: number;
		TEXTURE13: number;
		TEXTURE14: number;
		TEXTURE15: number;
		TEXTURE16: number;
		TEXTURE17: number;
		TEXTURE18: number;
		TEXTURE19: number;
		TEXTURE20: number;
		TEXTURE21: number;
		TEXTURE22: number;
		TEXTURE23: number;
		TEXTURE24: number;
		TEXTURE25: number;
		TEXTURE26: number;
		TEXTURE27: number;
		TEXTURE28: number;
		TEXTURE29: number;
		TEXTURE30: number;
		TEXTURE31: number;
		ACTIVE_TEXTURE: number;
		CLAMP: number;
		CLAMP_TO_BORDER: number;
		CLAMP_TO_EDGE: number;
		MIRRORED_REPEAT: number;
		REPEAT: number;
		FLOAT_VEC2: number;
		FLOAT_VEC3: number;
		FLOAT_VEC4: number;
		INT_VEC2: number;
		INT_VEC3: number;
		INT_VEC4: number;
		BOOL: number;
		BOOL_VEC2: number;
		BOOL_VEC3: number;
		BOOL_VEC4: number;
		FLOAT_MAT2: number;
		FLOAT_MAT3: number;
		FLOAT_MAT4: number;
		SAMPLER_2D: number;
		SAMPLER_CUBE: number;
		VERTEX_ATTRIB_ARRAY_ENABLED: number;
		VERTEX_ATTRIB_ARRAY_SIZE: number;
		VERTEX_ATTRIB_ARRAY_STRIDE: number;
		VERTEX_ATTRIB_ARRAY_TYPE: number;
		VERTEX_ATTRIB_ARRAY_NORMALIZED: number;
		VERTEX_ATTRIB_ARRAY_POINTER: number;
		VERTEX_ATTRIB_ARRAY_BUFFER_BINDING: number;
		IMPLEMENTATION_COLOR_READ_TYPE: number;
		IMPLEMENTATION_COLOR_READ_FORMAT: number;
		COMPILE_STATUS: number;
		INFO_LOG_LENGTH: number;
		SHADER_SOURCE_LENGTH: number;
		SHADER_COMPILER: number;
		SHADER_BINARY_FORMATS: number;
		NUM_SHADER_BINARY_FORMATS: number;
		LOW_FLOAT: number;
		MEDIUM_FLOAT: number;
		HALF_FLOAT: number;
		HIGH_FLOAT: number;
		LOW_INT: number;
		MEDIUM_INT: number;
		HIGH_INT: number;
		FRAMEBUFFER: number;
		RENDERBUFFER: number;
		RGB565: number;
		DEPTH_COMPONENT16: number;
		DEPTH_COMPONENT24: number;
		DEPTH_COMPONENT32F: number;
		STENCIL_INDEX: number;
		STENCIL_INDEX8: number;
		DEPTH_STENCIL: number;
		DEPTH24_STENCIL8: number;
		RENDERBUFFER_WIDTH: number;
		RENDERBUFFER_HEIGHT: number;
		RENDERBUFFER_INTERNAL_FORMAT: number;
		RENDERBUFFER_RED_SIZE: number;
		RENDERBUFFER_GREEN_SIZE: number;
		RENDERBUFFER_BLUE_SIZE: number;
		RENDERBUFFER_ALPHA_SIZE: number;
		RENDERBUFFER_DEPTH_SIZE: number;
		RENDERBUFFER_STENCIL_SIZE: number;
		FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE: number;
		FRAMEBUFFER_ATTACHMENT_OBJECT_NAME: number;
		FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL: number;
		FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE: number;
		COLOR: number;
		COLOR_ATTACHMENT0: number;
		DEPTH_ATTACHMENT: number;
		STENCIL_ATTACHMENT: number;
		DEPTH_STENCIL_ATTACHMENT: number;
		VERTEX_ARRAY_BINDING: number;
		NONE: number;
		FRAMEBUFFER_COMPLETE: number;
		FRAMEBUFFER_INCOMPLETE_ATTACHMENT: number;
		FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: number;
		FRAMEBUFFER_INCOMPLETE_DIMENSIONS: number;
		FRAMEBUFFER_UNSUPPORTED: number;
		FRAMEBUFFER_BINDING: number;
		DRAW_FRAMEBUFFER_BINDING: number;
		DRAW_FRAMEBUFFER: number;
		READ_FRAMEBUFFER: number;
		RENDERBUFFER_BINDING: number;
		MAX_RENDERBUFFER_SIZE: number;
		INVALID_FRAMEBUFFER_OPERATION: number;
		TRANSFORM_FEEDBACK_BUFFER_MODE: number;
		MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS: number;
		TRANSFORM_FEEDBACK_VARYINGS: number;
		TRANSFORM_FEEDBACK_BUFFER_START: number;
		TRANSFORM_FEEDBACK_BUFFER_SIZE: number;
		TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN: number;
		MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS: number;
		MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS: number;
		INTERLEAVED_ATTRIBS: number;
		SEPARATE_ATTRIBS: number;
		TRANSFORM_FEEDBACK_BUFFER: number;
		TRANSFORM_FEEDBACK_BUFFER_BINDING: number;
		TRANSFORM_FEEDBACK: number;
		TRANSFORM_FEEDBACK_PAUSED: number;
		TRANSFORM_FEEDBACK_ACTIVE: number;
		TRANSFORM_FEEDBACK_BINDING: number;
		UNPACK_IMAGE_HEIGHT: number;
		UNPACK_SKIP_IMAGES: number;
		UNPACK_SKIP_PIXELS: number;
		UNPACK_SKIP_ROWS: number;
		TEXTURE_COMPARE_FUNC: number;
		TEXTURE_COMPARE_MODE: number;
		COMPARE_REF_TO_TEXTURE: number;
		UNPACK_FLIP_Y_WEBGL: number;
		UNPACK_PREMULTIPLY_ALPHA_WEBGL: number;
		CONTEXT_LOST_WEBGL: number;
		UNPACK_COLORSPACE_CONVERSION_WEBGL: number;
		BROWSER_DEFAULT_WEBGL: number;
		MAX: number;
		MIN: number;
		UNPACK_ROW_LENGTH: number;
		PIXEL_PACK_BUFFER: number;
		PIXEL_UNPACK_BUFFER: number;
		PIXEL_PACK_BUFFER_BINDING: number;
		PIXEL_UNPACK_BUFFER_BINDING: number;
	}
}