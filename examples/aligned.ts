import { Image } from '@node-3d/image';
import { Document } from '@node-3d/glfw';

import { webgl as gl } from '@node-3d/webgl';
import { mat4 } from './utils/matrix.ts';
import { alignedShaders } from './utils/presets.ts';
import { buildShader } from './utils/build-shader.ts';


const vertices = [
	// Front face
	-1.0, -1.0, 0.5,
	1.0, -1.0, 0.5,
	1.0, 1.0, 0.5,
	-1.0, 1.0, 0.5,
];

const textureCoords = [
	// Front face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
];

const cubeVertexIndices = [
	0, 1, 2, 0, 2, 3, // Front face
];

Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'Aligned',
});

const shaderProgram = buildShader(alignedShaders);
gl.useProgram(shaderProgram);

type TAttributes = {
	vertexPositionAttribute: number;
	textureCoordAttribute: number;
	pMatrixUniform: WebGLUniformLocation;
	mvMatrixUniform: WebGLUniformLocation;
	samplerUniform: WebGLUniformLocation;
};
const shaderVars: TAttributes = {
	vertexPositionAttribute: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
	textureCoordAttribute: gl.getAttribLocation(shaderProgram, 'aTextureCoord'),
	pMatrixUniform: gl.getUniformLocation(shaderProgram, 'uPMatrix'),
	mvMatrixUniform: gl.getUniformLocation(shaderProgram, 'uMVMatrix'),
	samplerUniform: gl.getUniformLocation(shaderProgram, 'uSampler'),
};

gl.enableVertexAttribArray(shaderVars.vertexPositionAttribute);
gl.enableVertexAttribArray(shaderVars.textureCoordAttribute);

const texLena = gl.createTexture();
const texLenaImage = new Image();
texLenaImage.on('load', () => {
	console.log(
		`Loaded image: ${texLenaImage.src}`,
		`${texLenaImage.width}x${texLenaImage.height}`,
	);
	gl.bindTexture(gl.TEXTURE_2D, texLena);
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texLenaImage);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);
});
texLenaImage.src = 'img/glass.gif';


const mvMatrix = mat4.create();
const pMatrix = mat4.create();


const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderVars.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderVars.mvMatrixUniform, false, mvMatrix);
};

const cubeVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
const cubeVertexPositionBufferItemSize = 3;

const cubeVertexTextureCoordBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
const cubeVertexTextureCoordBufferItemSize = 2;

const cubeVertexIndexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
const cubeVertexIndexBufferNumItems = 6;


const drawScene = () => {
	gl.clearColor(0.05, 0.1, 0.05, 1.0);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderVars.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderVars.textureCoordAttribute);
	
	mat4.ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderVars.vertexPositionAttribute, cubeVertexPositionBufferItemSize, gl.FLOAT, false, 0, 0,
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	gl.vertexAttribPointer(
		shaderVars.textureCoordAttribute, cubeVertexTextureCoordBufferItemSize, gl.FLOAT, false, 0, 0,
	);
	
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, texLena);
	gl.uniform1i(shaderVars.samplerUniform, 0);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBufferNumItems, gl.UNSIGNED_SHORT, 0);
	
	// Cleanup GL state
	gl.bindTexture(gl.TEXTURE_2D, null);
	gl.bindBuffer(gl.ARRAY_BUFFER, null);
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
	gl.useProgram(null);
};


document.loop(drawScene);




