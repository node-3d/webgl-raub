import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';
import { mat4 } from './utils/glMatrix-0.9.5.min.js';
import { cubeColors, cubeVertexIndices, cubeVertices, shapeShaders } from './utils/presets.mjs';
import { buildShader } from './utils/build-shader.mjs';
import { deg2rad } from './utils/deg2rad.mjs';


Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'VAO',
});

let xRot = 0;
let xSpeed = 5;
let yRot = 0;
let ySpeed = -5;
let z = -5;

const shaderProgram = buildShader(shapeShaders);
gl.useProgram(shaderProgram);

shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');

shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');


const mvMatrix = mat4.create();
const pMatrix = mat4.create();


const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	
	const error = gl.getError();
	if (error) {
		console.error('setMatrixUniforms():', gl.drawingBufferWidth, gl.drawingBufferHeight, error);
	}
};

const currentlyPressedKeys = {};

document.on('keydown', (evt) => {
	// console.log('[KEYDOWN]:', evt);
	currentlyPressedKeys[evt.keyCode] = true;
	handleKeys();
});

document.on('keyup', (evt) => {
	currentlyPressedKeys[evt.keyCode] = false;
});


const handleKeys = () => {
	if (currentlyPressedKeys[219]) { // ]
		z -= 0.05;
	}
	if (currentlyPressedKeys[221]) { // \
		z += 0.05;
	}
	if (currentlyPressedKeys[37]) { // Left cursor key
		ySpeed -= 1;
	}
	if (currentlyPressedKeys[39]) { // Right cursor key
		ySpeed += 1;
	}
	if (currentlyPressedKeys[38]) { // Up cursor key
		xSpeed -= 1;
	}
	if (currentlyPressedKeys[40]) { // Down cursor key
		xSpeed += 1;
	}
};


const cubeVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeVertices), gl.STATIC_DRAW);
cubeVertexPositionBuffer.itemSize = 3;

const cubeVerticesColorBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
gl.bufferData(
	gl.ARRAY_BUFFER,
	new Float32Array(cubeColors),
	gl.STATIC_DRAW
);
cubeVerticesColorBuffer.itemSize = 4;

const cubeVertexIndexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
cubeVertexIndexBuffer.numItems = 36;

gl.bindVertexArray(null);
gl.bindBuffer(gl.ARRAY_BUFFER, null);
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);


const reinitVao = () => {
	const vao = gl.createVertexArray();
	gl.bindVertexArray(vao);
	
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexColorAttribute, cubeVerticesColorBuffer.itemSize, gl.FLOAT, false, 0, 0,
	);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	gl.bindVertexArray(null);
	gl.bindBuffer(gl.ARRAY_BUFFER, null);
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
	
	return vao;
};

let vao = reinitVao();
document.on('mode', () => {
	vao = reinitVao();
});


const error = gl.getError();
if (error) {
	console.error('Init Error:', error);
}


const drawScene = () => {
	gl.clearColor(0.05, 0.1, 0.1, 1);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	mat4.identity(mvMatrix);
	mat4.translate(mvMatrix, [0.0, 0.0, z]);
	mat4.rotate(mvMatrix, deg2rad(xRot), [1, 0, 0]);
	mat4.rotate(mvMatrix, deg2rad(yRot), [0, 1, 0]);
	setMatrixUniforms();
	
	gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
	gl.enable(gl.BLEND);
	gl.disable(gl.DEPTH_TEST);
	gl.enable(gl.CULL_FACE);
	gl.cullFace(gl.FRONT);
	
	gl.bindVertexArray(vao);
	
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	gl.cullFace(gl.BACK);
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	
	// cleanup GL state
	gl.bindVertexArray(null);
	gl.useProgram(null);
};


const tick = (now) => {
	xRot = (xSpeed * now) * 0.001;
	yRot = (ySpeed * now) * 0.001;
	
	drawScene();
};

document.loop(tick);
