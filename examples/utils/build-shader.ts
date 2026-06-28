import { webgl as gl } from '@node-3d/webgl';

type TShaderCodes = Readonly<Record<'fs' | 'vs', string>>;

const getShader = (shaderCodes: TShaderCodes, id: keyof TShaderCodes): WebGLShader => {
	const shader = gl.createShader(id === 'vs' ? gl.VERTEX_SHADER : gl.FRAGMENT_SHADER);
	
	gl.shaderSource(shader, shaderCodes[id]);
	gl.compileShader(shader);
	
	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		console.error(gl.getShaderInfoLog(shader));
		throw new Error(`Failed to compile ${id} shader.`);
	}
	
	return shader;
};


export const buildShader = (shaderCodes: TShaderCodes): WebGLProgram => {
	const fragmentShader = getShader(shaderCodes, 'fs');
	const vertexShader = getShader(shaderCodes, 'vs');
	
	const shaderProgram = gl.createProgram();
	gl.attachShader(shaderProgram, vertexShader);
	gl.attachShader(shaderProgram, fragmentShader);
	gl.linkProgram(shaderProgram);
	
	if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
		console.error(
			`Failed to build shaders. Error: ${
				gl.getProgramInfoLog(shaderProgram)
			}`
		);
	}
	
	return shaderProgram;
};


