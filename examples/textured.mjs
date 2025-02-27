import Image from 'image-raub';
import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';
import { mat4 } from './utils/glMatrix-0.9.5.min.js';
import { cubeTexCoords, cubeVertexIndices, cubeVertices, texturedShaders } from './utils/presets.mjs';
import { buildShader } from './utils/build-shader.mjs';
import { deg2rad } from './utils/deg2rad.mjs';


Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'Textured',
});

const shaderProgram = buildShader(texturedShaders);
gl.useProgram(shaderProgram);

shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, 'aTextureCoord');
gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);

shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');
shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, 'uSampler');


const neheTexture = gl.createTexture();
neheTexture.image = new Image();
neheTexture.image.onload = () => {
	console.log(
		`Loaded image: ${neheTexture.image.src}`,
		`${neheTexture.image.width}x${neheTexture.image.height}`,
	);
	gl.bindTexture(gl.TEXTURE_2D, neheTexture);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, neheTexture.image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);
};
neheTexture.image.src = 'img/glass.gif';


const mvMatrix = mat4.create();
const pMatrix  = mat4.create();

const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	
	const error = gl.getError();
	if (error) {
		console.error('setMatrixUniforms():', gl.drawingBufferWidth, gl.drawingBufferHeight, error);
	}
};

const cubeVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeVertices), gl.STATIC_DRAW);
cubeVertexPositionBuffer.itemSize = 3;

const cubeVertexTextureCoordBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeTexCoords), gl.STATIC_DRAW);
cubeVertexTextureCoordBuffer.itemSize = 2;

const cubeVertexIndexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);

gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
cubeVertexIndexBuffer.numItems = 36;


let xRot = 0;
let yRot = 0;
let zRot = 0;

const drawScene = () => {
	gl.clearColor(0.05, 0.05, 0.1, 1);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
	
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [0.0, 0.0, -5.0]);
	
	mat4.rotate(mvMatrix, deg2rad(xRot), [1, 0, 0]);
	mat4.rotate(mvMatrix, deg2rad(yRot), [0, 1, 0]);
	mat4.rotate(mvMatrix, deg2rad(zRot), [0, 0, 1]);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	gl.vertexAttribPointer(
		shaderProgram.textureCoordAttribute, cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, neheTexture);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	
	// Cleanup GL state
	gl.bindTexture(gl.TEXTURE_2D, null);
	gl.bindBuffer(gl.ARRAY_BUFFER, null);
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
	gl.useProgram(null);
};


const tick = (now) => {
	xRot = (5 * now) * 0.001;
	yRot = (3 * now) * 0.001;
	zRot = (4 * now) * 0.001;
	
	drawScene();
};

document.loop(tick);
