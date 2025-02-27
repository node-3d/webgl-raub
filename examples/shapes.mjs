import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';
import { mat4 } from './utils/glMatrix-0.9.5.min.js';
import { colorsTri, shapeShaders, vertsQuad, vertsTri } from './utils/presets.mjs';
import { buildShader } from './utils/build-shader.mjs';


Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'Shapes',
});

const shaderProgram = buildShader(shapeShaders);
gl.useProgram(shaderProgram);

shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');
gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);

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

const triangleVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertsTri), gl.STATIC_DRAW);
triangleVertexPositionBuffer.itemSize = 3;
triangleVertexPositionBuffer.numItems = 3;

const triangleVertexColorBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colorsTri), gl.STATIC_DRAW);
triangleVertexColorBuffer.itemSize = 4;


const squareVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertsQuad), gl.STATIC_DRAW);
squareVertexPositionBuffer.itemSize = 3;
squareVertexPositionBuffer.numItems = 4;

const squareVertexColorBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);

let colors2 = [];
for (let i = 0; i < 4; i++) {
	colors2 = colors2.concat([0.5, 0.5, 1.0, 1.0]);
}

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors2), gl.STATIC_DRAW);
squareVertexColorBuffer.itemSize = 4;


const drawScene = () => {
	gl.clearColor(0.1, 0.1, 0.05, 1);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [-1.5, 0.0, -7.0]);
	gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute, triangleVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexColorAttribute, triangleVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	setMatrixUniforms();
	gl.drawArrays(gl.TRIANGLES, 0, triangleVertexPositionBuffer.numItems);
	
	mat4.translate(mvMatrix, [3.0, 0.0, 0.0]);
	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute, squareVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexColorAttribute, squareVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	setMatrixUniforms();
	gl.drawArrays(gl.TRIANGLE_STRIP, 0, squareVertexPositionBuffer.numItems);
};


document.loop(drawScene);
