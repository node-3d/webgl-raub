import { Document } from '@node-3d/glfw';

import { webgl as gl } from '@node-3d/webgl';
import { mat4 } from './utils/matrix.ts';
import { colorsTri, shapeShaders, vertsQuad, vertsTri } from './utils/presets.ts';
import { buildShader } from './utils/build-shader.ts';


Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'Shapes',
});

const shaderProgram = buildShader(shapeShaders);
gl.useProgram(shaderProgram);

type TShaderVars = {
	vertexPositionAttribute: number;
	vertexColorAttribute: number;
	pMatrixUniform: WebGLUniformLocation;
	mvMatrixUniform: WebGLUniformLocation;
};
const shaderVars: TShaderVars = {
	vertexPositionAttribute: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
	vertexColorAttribute: gl.getAttribLocation(shaderProgram, 'aVertexColor'),
	pMatrixUniform: gl.getUniformLocation(shaderProgram, 'uPMatrix'),
	mvMatrixUniform: gl.getUniformLocation(shaderProgram, 'uMVMatrix'),
};

gl.enableVertexAttribArray(shaderVars.vertexPositionAttribute);
gl.enableVertexAttribArray(shaderVars.vertexColorAttribute);

const mvMatrix = mat4.create();
const pMatrix = mat4.create();

const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderVars.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderVars.mvMatrixUniform, false, mvMatrix);
	
	const error = gl.getError();
	if (error) {
		console.error('setMatrixUniforms():', gl.drawingBufferWidth, gl.drawingBufferHeight, error);
	}
};

const triangleVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertsTri), gl.STATIC_DRAW);
const triangleVertexPositionBufferItemSize = 3;
const triangleVertexPositionBufferNumItems = 3;

const triangleVertexColorBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colorsTri), gl.STATIC_DRAW);
const triangleVertexColorBufferItemSize = 4;


const squareVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertsQuad), gl.STATIC_DRAW);
const squareVertexPositionBufferItemSize = 3;
const squareVertexPositionBufferNumItems = 4;

const squareVertexColorBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);

const colors2 = [];
for (let i = 0; i < 4; i++) {
	colors2.push(0.5, 0.5, 1.0, 1.0);
}

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors2), gl.STATIC_DRAW);
const squareVertexColorBufferItemSize = 4;


const drawScene = () => {
	gl.clearColor(0.1, 0.1, 0.05, 1);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderVars.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderVars.vertexColorAttribute);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [-1.5, 0.0, -7.0]);
	gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderVars.vertexPositionAttribute, triangleVertexPositionBufferItemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
	gl.vertexAttribPointer(
		shaderVars.vertexColorAttribute, triangleVertexColorBufferItemSize, gl.FLOAT, false, 0, 0
	);
	
	setMatrixUniforms();
	gl.drawArrays(gl.TRIANGLES, 0, triangleVertexPositionBufferNumItems);
	
	mat4.translate(mvMatrix, [3.0, 0.0, 0.0]);
	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderVars.vertexPositionAttribute, squareVertexPositionBufferItemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
	gl.vertexAttribPointer(
		shaderVars.vertexColorAttribute, squareVertexColorBufferItemSize, gl.FLOAT, false, 0, 0
	);
	
	setMatrixUniforms();
	gl.drawArrays(gl.TRIANGLE_STRIP, 0, squareVertexPositionBufferNumItems);
};


document.loop(drawScene);




