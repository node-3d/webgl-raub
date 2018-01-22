'use strict';

const webgl    = require('node-webgl-raub');
const Document = require('node-glfw-raub');

const glMatrix = require('./libs/glMatrix-0.9.5.min');


Document.setWebgl(webgl);
const document = new Document();
const frame    = document.requestAnimationFrame;

let xRot   = 0;
let xSpeed = 5;
let yRot   = 0;
let ySpeed = -5;
let z      = -5;

document.on('resize', evt => {
	gl.viewportWidth  = evt.width;
	gl.viewportHeight = evt.height;
});


const shaders = {
	
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec4 aVertexColor;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		varying vec4 vColor;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vColor = aVertexColor;
		}
	`,
	
	fs : `
		#ifdef GL_ES
			precision mediump float;
		#endif
		varying vec4 vColor;
		void main(void) {
			gl_FragColor = vColor;
		}
	`,
	
};

let gl;

function initGL(canvas) {
	
	try {
		
		gl = canvas.getContext('webgl');
		
		gl.viewportWidth  = canvas.width;
		gl.viewportHeight = canvas.height;
		
	} catch (e) {
		
		console.error("Could not initialise WebGL, sorry :-(");
		console.error(e);
		process.exit(-1);
		
	}
	
}


function getShader(gl, id) {
	
	const shader = gl.createShader(id === 'vs' ? gl.VERTEX_SHADER : gl.FRAGMENT_SHADER);
	
	gl.shaderSource(shader, shaders[id]);
	gl.compileShader(shader);
	
	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		console.error(gl.getShaderInfoLog(shader));
		return null;
	}
	
	return shader;
	
}


let shaderProgram;

function initShaders() {
	
	const fragmentShader = getShader(gl, 'fs');
	const vertexShader   = getShader(gl, 'vs');
	
	shaderProgram = gl.createProgram();
	gl.attachShader(shaderProgram, vertexShader);
	gl.attachShader(shaderProgram, fragmentShader);
	gl.linkProgram(shaderProgram);
	
	if ( ! gl.getProgramParameter(shaderProgram, gl.LINK_STATUS) ) {
		console.error(
			`Could not initialise shaders. Error: ${
				gl.getProgramInfoLog(shaderProgram)
			}`
		);
	}
	
	gl.useProgram(shaderProgram);
	
	shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	
	shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
	shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
	shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');
	
}


let mvMatrix = glMatrix.mat4.create();
let pMatrix  = glMatrix.mat4.create();

const mvMatrixStack = [];


function mvPushMatrix() {
	const copy = glMatrix.mat4.create();
	glMatrix.mat4.set(mvMatrix, copy);
	mvMatrixStack.push(copy);
}


function mvPopMatrix() {
	if (mvMatrixStack.length == 0) {
		throw "Invalid popMatrix!";
	}
	mvMatrix = mvMatrixStack.pop();
}


function setMatrixUniforms() {
	
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	
	const error = gl.getError();
	if (error) {
		console.error("setMatrixUniforms():", gl.viewportWidth, gl.viewportHeight, error);
	}
	
}


function degToRad(degrees) {
	return degrees * Math.PI / 180;
}


const currentlyPressedKeys = {};

document.on('keydown', evt => {
	// console.log('[KEYDOWN]:', evt);
	currentlyPressedKeys[evt.keyCode] = true;
	handleKeys();
});

document.on('keyup', evt => {
	currentlyPressedKeys[evt.keyCode] = false;
});


function handleKeys() {
	
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
	//console.log("speed: "+xSpeed+" "+ySpeed+" "+z);
	
}


let cubeVertexPositionBuffer;
let cubeVertexNormalBuffer;
let cubeVerticesColorBuffer;
let cubeVertexIndexBuffer;

function initBuffers() {
	
	const vertices = [
		// Front face
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		
		// Back face
		-1.0, -1.0, -1.0,
		-1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0, -1.0, -1.0,
		
		// Top face
		-1.0,  1.0, -1.0,
		-1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0, -1.0,
		
		// Bottom face
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0,
		
		// Right face
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0,  1.0,
		1.0, -1.0,  1.0,
		
		// Left face
		-1.0, -1.0, -1.0,
		-1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0
	];
	
	cubeVertexPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	cubeVertexPositionBuffer.itemSize = 3;
	cubeVertexPositionBuffer.numItems = 24;
	
	const vertexNormals = [
		// Front face
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		0.0,  0.0,  1.0,
		
		// Back face
		0.0,  0.0, -1.0,
		0.0,  0.0, -1.0,
		0.0,  0.0, -1.0,
		0.0,  0.0, -1.0,
		
		// Top face
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		0.0,  1.0,  0.0,
		
		// Bottom face
		0.0, -1.0,  0.0,
		0.0, -1.0,  0.0,
		0.0, -1.0,  0.0,
		0.0, -1.0,  0.0,
		
		// Right face
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		1.0,  0.0,  0.0,
		
		// Left face
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0,
		-1.0,  0.0,  0.0
	];
	
	cubeVertexNormalBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexNormals), gl.STATIC_DRAW);
	cubeVertexNormalBuffer.itemSize = 3;
	cubeVertexNormalBuffer.numItems = 24;
	
	const colors = [
		[ 1.0, 1.0, 1.0, 0.5 ], // Front face: white
		[ 1.0, 0.0, 0.0, 0.5 ], // Back face: red
		[ 0.0, 1.0, 0.0, 0.5 ], // Top face: green
		[ 0.0, 0.0, 1.0, 0.5 ], // Bottom face: blue
		[ 1.0, 1.0, 0.0, 0.5 ], // Right face: yellow
		[ 1.0, 0.0, 1.0, 0.5 ] // Left face: purple
	];
	
	let generatedColors = [];
	
	for (let j = 0; j < 6; j++) {
		const c = colors[j];
		
		for (let i = 0; i < 4; i++) {
			generatedColors = generatedColors.concat(c);
		}
	}
	
	cubeVerticesColorBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
	gl.bufferData(
		gl.ARRAY_BUFFER,
		new Float32Array(generatedColors),
		gl.STATIC_DRAW
	);
	
	const cubeVertexIndices = [
		0, 1, 2,      0, 2, 3,    // Front face
		4, 5, 6,      4, 6, 7,    // Back face
		8, 9, 10,     8, 10, 11,  // Top face
		12, 13, 14,   12, 14, 15, // Bottom face
		16, 17, 18,   16, 18, 19, // Right face
		20, 21, 22,   20, 22, 23  // Left face
	];
	
	cubeVertexIndexBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
	cubeVertexIndexBuffer.itemSize = 1;
	cubeVertexIndexBuffer.numItems = 36;
	
	const error = gl.getError();
	if (error) {
		console.error("initBuffers():", error);
	}
	
}


function initBuffers2() {
	
	const n = [
		[-1.0, 0.0, 0.0],
		[0.0, 1.0, 0.0],
		[1.0, 0.0, 0.0],
		[0.0, -1.0, 0.0],
		[0.0, 0.0, 1.0],
		[0.0, 0.0, -1.0]
	];
	
	const faces = [
		[0, 1, 2, 3],
		[3, 2, 6, 7],
		[7, 6, 5, 4],
		[4, 5, 1, 0],
		[5, 6, 2, 1],
		[7, 4, 0, 3]
	];
	
	const v=new Array(8);
	for(let i = 0; i < 8; i++) {
		v[i] = new Array(4);
	}
	
	const size = 2;
	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
	
	const normals  = new Array();
	const vertices = new Array();
	for (let i = 5; i >= 0; i--) {
		normals.push(n[i][0],n[i][1],n[i][2]);
		vertices.push(v[faces[i][0]][0],v[faces[i][0]][1],v[faces[i][0]][2]);
		vertices.push(v[faces[i][0]][1],v[faces[i][1]][1],v[faces[i][1]][2]);
		vertices.push(v[faces[i][0]][2],v[faces[i][2]][1],v[faces[i][2]][2]);
		vertices.push(v[faces[i][0]][3],v[faces[i][3]][1],v[faces[i][3]][2]);
	}

}


function drawScene() {
	
	gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	glMatrix.mat4.perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0, pMatrix);
	glMatrix.mat4.identity(mvMatrix);
	glMatrix.mat4.translate(mvMatrix, [0.0, 0.0, z]);
	glMatrix.mat4.rotate(mvMatrix, degToRad(xRot), [1, 0, 0]);
	glMatrix.mat4.rotate(mvMatrix, degToRad(yRot), [0, 1, 0]);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);
	
	gl.blendFunc(gl.SRC_ALPHA, gl.ONE_MINUS_SRC_ALPHA);
	gl.enable(gl.BLEND);
	gl.disable(gl.DEPTH_TEST);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVerticesColorBuffer);
	gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, 4, gl.FLOAT, false, 0, 0);
	
	gl.enable(gl.CULL_FACE);
	
	gl.cullFace(gl.FRONT);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	
	setMatrixUniforms();
	
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	
	gl.cullFace(gl.BACK);
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	
	// cleanup GL state
	gl.bindBuffer(gl.ARRAY_BUFFER, null);
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
	
}


let lastTime = 0;
let fps=0;

function animate(timeNow) {
	
	if (lastTime) {
		
		const elapsed = timeNow - lastTime;
		fps = Math.round(1000/elapsed);
		
		xRot += (xSpeed * elapsed) / 1000.0;
		yRot += (ySpeed * elapsed) / 1000.0;
		
	}
	
	lastTime = timeNow;
	
}


/* Before calling AntTweakBar or any other library that could use programs,
 * one must make sure to disable the VertexAttribArray used by the current
 * program otherwise this may have some unpredictable consequences aka
 * wrong vertex attrib arrays being used by another program!
 */
function enableProgram() {
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
}


function disableProgram() {
	gl.disableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.disableVertexAttribArray(shaderProgram.vertexColorAttribute);
	gl.useProgram(null);
}


function tick(timeNow) {
	
	drawScene(timeNow);
	animate(timeNow);
	
	gl.finish(); // for timing
	frame(tick, 0);
	
}


function start() {
	
	const canvas = document.createElement('canvas');
	
	initGL(canvas);
	initShaders();
	initBuffers();
	
	gl.clearColor(255, 0, 0, 1);
	gl.enable(gl.DEPTH_TEST);
	
	tick(Date.now());
	
}

start();

