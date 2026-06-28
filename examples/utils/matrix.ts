export type TVec3Input = readonly [number, number, number] | readonly number[] | Float32Array;
export type TVec3 = Float32Array;
export type TMat3 = Float32Array;
export type TMat4 = Float32Array;

const MAT3_SIZE = 9;
const MAT4_SIZE = 16;
const HALF_CIRCLE_DEGREES = 180;

const copyArrayLike = (input: ArrayLike<number>, out: Float32Array, maxLength: number): void => {
	const length = Math.min(input.length, maxLength);

	for (let i = 0; i < length; i++) {
		out[i] = input[i];
	}
};

const createVec3 = (): TVec3 => new Float32Array(3);

const normalizeVec3 = (input: TVec3Input, out: TVec3 = createVec3()): TVec3 => {
	const x = input[0] ?? 0;
	const y = input[1] ?? 0;
	const z = input[2] ?? 0;
	const length = Math.hypot(x, y, z);

	if (length === 0) {
		out[0] = 0;
		out[1] = 0;
		out[2] = 0;
		return out;
	}

	const scale = 1 / length;
	out[0] = x * scale;
	out[1] = y * scale;
	out[2] = z * scale;
	return out;
};

const scaleVec3 = (input: TVec3, value: number, out: TVec3 = input): TVec3 => {
	out[0] = input[0] * value;
	out[1] = input[1] * value;
	out[2] = input[2] * value;
	return out;
};

const createMat3 = (input?: ArrayLike<number>): TMat3 => {
	const out = new Float32Array(MAT3_SIZE);

	if (input) {
		copyArrayLike(input, out, MAT3_SIZE);
	}

	return out;
};

const transposeMat3 = (input: TMat3, out: TMat3 = input): TMat3 => {
	if (out === input) {
		const a01 = input[1];
		const a02 = input[2];
		const a12 = input[5];

		input[1] = input[3];
		input[2] = input[6];
		input[3] = a01;
		input[5] = input[7];
		input[6] = a02;
		input[7] = a12;
		return input;
	}

	out[0] = input[0];
	out[1] = input[3];
	out[2] = input[6];
	out[3] = input[1];
	out[4] = input[4];
	out[5] = input[7];
	out[6] = input[2];
	out[7] = input[5];
	out[8] = input[8];
	return out;
};

const createMat4 = (input?: ArrayLike<number>): TMat4 => {
	const out = new Float32Array(MAT4_SIZE);

	if (input) {
		copyArrayLike(input, out, MAT4_SIZE);
	}

	return out;
};

const identityMat4 = (out: TMat4): TMat4 => {
	out.fill(0);
	out[0] = 1;
	out[5] = 1;
	out[10] = 1;
	out[15] = 1;
	return out;
};

const frustumMat4 = (values: readonly [
	left: number,
	right: number,
	bottom: number,
	top: number,
	near: number,
	far: number,
	out: TMat4,
]): TMat4 => {
	const [left, right, bottom, top, near, far, out] = values;
	const width = right - left;
	const height = top - bottom;
	const depth = far - near;

	out[0] = (near * 2) / width;
	out[1] = 0;
	out[2] = 0;
	out[3] = 0;
	out[4] = 0;
	out[5] = (near * 2) / height;
	out[6] = 0;
	out[7] = 0;
	out[8] = (right + left) / width;
	out[9] = (top + bottom) / height;
	out[10] = -(far + near) / depth;
	out[11] = -1;
	out[12] = 0;
	out[13] = 0;
	out[14] = -(far * near * 2) / depth;
	out[15] = 0;
	return out;
};

const perspectiveMat4 = (
	fovyDegrees: number,
	aspect: number,
	near: number,
	far: number,
	out: TMat4,
): TMat4 => {
	const top = near * Math.tan((fovyDegrees * Math.PI) / (HALF_CIRCLE_DEGREES * 2));
	const right = top * aspect;

	return frustumMat4([-right, right, -top, top, near, far, out]);
};

const orthoMat4 = (...args: [
	left: number,
	right: number,
	bottom: number,
	top: number,
	near: number,
	far: number,
	out: TMat4,
]): TMat4 => {
	const [left, right, bottom, top, near, far, out] = args;
	const width = right - left;
	const height = top - bottom;
	const depth = far - near;

	out[0] = 2 / width;
	out[1] = 0;
	out[2] = 0;
	out[3] = 0;
	out[4] = 0;
	out[5] = 2 / height;
	out[6] = 0;
	out[7] = 0;
	out[8] = 0;
	out[9] = 0;
	out[10] = -2 / depth;
	out[11] = 0;
	out[12] = -(left + right) / width;
	out[13] = -(top + bottom) / height;
	out[14] = -(far + near) / depth;
	out[15] = 1;
	return out;
};

const translateMat4 = (input: TMat4, vector: TVec3Input, out: TMat4 = input): TMat4 => {
	const x = vector[0] ?? 0;
	const y = vector[1] ?? 0;
	const z = vector[2] ?? 0;

	if (out !== input) {
		out.set(input);
	}

	out[12] = input[0] * x + input[4] * y + input[8] * z + input[12];
	out[13] = input[1] * x + input[5] * y + input[9] * z + input[13];
	out[14] = input[2] * x + input[6] * y + input[10] * z + input[14];
	out[15] = input[3] * x + input[7] * y + input[11] * z + input[15];
	return out;
};

const rotateMat4 = (input: TMat4, angle: number, axis: TVec3Input, out: TMat4 = input): TMat4 | null => {
	const normalized = normalizeVec3(axis);
	const x = normalized[0];
	const y = normalized[1];
	const z = normalized[2];

	if (x === 0 && y === 0 && z === 0) {
		return null;
	}

	const sin = Math.sin(angle);
	const cos = Math.cos(angle);
	const t = 1 - cos;
	const a00 = input[0];
	const a01 = input[1];
	const a02 = input[2];
	const a03 = input[3];
	const a10 = input[4];
	const a11 = input[5];
	const a12 = input[6];
	const a13 = input[7];
	const a20 = input[8];
	const a21 = input[9];
	const a22 = input[10];
	const a23 = input[11];
	const b00 = x * x * t + cos;
	const b01 = y * x * t + z * sin;
	const b02 = z * x * t - y * sin;
	const b10 = x * y * t - z * sin;
	const b11 = y * y * t + cos;
	const b12 = z * y * t + x * sin;
	const b20 = x * z * t + y * sin;
	const b21 = y * z * t - x * sin;
	const b22 = z * z * t + cos;

	if (out !== input) {
		out[12] = input[12];
		out[13] = input[13];
		out[14] = input[14];
		out[15] = input[15];
	}

	out[0] = a00 * b00 + a10 * b01 + a20 * b02;
	out[1] = a01 * b00 + a11 * b01 + a21 * b02;
	out[2] = a02 * b00 + a12 * b01 + a22 * b02;
	out[3] = a03 * b00 + a13 * b01 + a23 * b02;
	out[4] = a00 * b10 + a10 * b11 + a20 * b12;
	out[5] = a01 * b10 + a11 * b11 + a21 * b12;
	out[6] = a02 * b10 + a12 * b11 + a22 * b12;
	out[7] = a03 * b10 + a13 * b11 + a23 * b12;
	out[8] = a00 * b20 + a10 * b21 + a20 * b22;
	out[9] = a01 * b20 + a11 * b21 + a21 * b22;
	out[10] = a02 * b20 + a12 * b21 + a22 * b22;
	out[11] = a03 * b20 + a13 * b21 + a23 * b22;
	return out;
};

const toInverseMat3 = (input: TMat4, out: TMat3 = createMat3()): TMat3 | null => {
	const a00 = input[0];
	const a01 = input[1];
	const a02 = input[2];
	const a10 = input[4];
	const a11 = input[5];
	const a12 = input[6];
	const a20 = input[8];
	const a21 = input[9];
	const a22 = input[10];
	const b01 = a22 * a11 - a12 * a21;
	const b11 = -a22 * a10 + a12 * a20;
	const b21 = a21 * a10 - a11 * a20;
	const determinant = a00 * b01 + a01 * b11 + a02 * b21;

	if (determinant === 0) {
		return null;
	}

	const scale = 1 / determinant;
	out[0] = b01 * scale;
	out[1] = (-a22 * a01 + a02 * a21) * scale;
	out[2] = (a12 * a01 - a02 * a11) * scale;
	out[3] = b11 * scale;
	out[4] = (a22 * a00 - a02 * a20) * scale;
	out[5] = (-a12 * a00 + a02 * a10) * scale;
	out[6] = b21 * scale;
	out[7] = (-a21 * a00 + a01 * a20) * scale;
	out[8] = (a11 * a00 - a01 * a10) * scale;
	return out;
};

export const vec3 = {
	create: createVec3,
	normalize: normalizeVec3,
	scale: scaleVec3,
};

export const mat3 = {
	create: createMat3,
	transpose: transposeMat3,
};

export const mat4 = {
	create: createMat4,
	identity: identityMat4,
	ortho: orthoMat4,
	perspective: perspectiveMat4,
	rotate: rotateMat4,
	toInverseMat3,
	translate: translateMat4,
};
