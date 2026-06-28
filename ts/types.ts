import type { TExtensions } from "./extensions";

export type TContextAttributes = Readonly<{
	alpha: boolean,
	antialias: boolean,
	depth: boolean,
	desynchronized: boolean,
	failIfMajorPerformanceCaveat: boolean,
	powerPreference: 'default' | 'low-power' | 'high-performance',
	premultipliedAlpha: boolean,
	preserveDrawingBuffer: boolean,
	stencil: boolean,
}>;

export type TSize = Readonly<{ width: number; height: number }>;

export type TImage = TSize & Readonly<{
	data: Buffer | null;
	noflip?: boolean;
}>;

export type TNativeArrayData = ArrayBuffer | ArrayBufferView | Buffer;
export type TNativeImage = Readonly<{
	data: TNativeArrayData | null;
	height?: number;
	noflip?: boolean;
	width?: number;
}>;

export type TProgramBinary = Readonly<{ binary: string; binaryFormat: number }>;
export type TShaderPrecisionFormat = Readonly<{ precision: number; rangeMax: number; rangeMin: number }>;

export type TNativeImageData = TNativeArrayData | TNativeImage;

type NumberTypedArray =
  | Int8Array
  | Uint8Array
  | Uint8ClampedArray
  | Int16Array
  | Uint16Array
  | Int32Array
  | Uint32Array
  | Float32Array
  | Float64Array;

export type TFloatArray = number[] | Float32Array;
export type TIntArray = number[] | Int32Array;
export type TUintArray = number[] | Uint32Array;
export type TArrayValue = number[] | NumberTypedArray;

export type TWebGLState = Readonly<{
	contextAttributes: TContextAttributes;
	drawingBufferHeight: number;
	drawingBufferWidth: number;
	getContextAttributes: () => TContextAttributes;
	getExtension: <T extends keyof TExtensions>(name: T) => TExtensions[T];
	isContextLost: () => boolean;
	useWebGL2: () => void;
	extractId: (x: { _?: number }) => number;
	getGLExtensions: () => string[];
}>;
