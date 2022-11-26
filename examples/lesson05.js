'use strict';

const webgl = require('..');
const Image = require('image-raub');

const { Document } = require('glfw-raub');

const { mat4 } = require('./libs/glMatrix-0.9.5.min');


Document.setWebgl(webgl);
const document = new Document();
webgl.canvas = document;

const canvas = document.createElement('canvas');
const frame = document.requestAnimationFrame;

let gl;

document.title = 'Lesson05';

const shaders = {
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec2 aTextureCoord;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		varying vec2 vTextureCoord;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vTextureCoord = aTextureCoord;
		}
	`,
	fs : `
		#ifdef GL_ES
			precision mediump float;
		#endif
		varying vec2 vTextureCoord;
		uniform sampler2D uSampler;
		void main(void) {
			gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
		}
	`,
};


const initContext = canvas => {
	try {
		gl = canvas.getContext('webgl');
	} catch (e) {
		console.error('Could not initialise WebGL, sorry :-(');
		process.exit(-1);
	}
};


const getShader = (gl, id) => {
	const shader = gl.createShader(id === 'vs' ? gl.VERTEX_SHADER : gl.FRAGMENT_SHADER);
	
	gl.shaderSource(shader, shaders[id]);
	gl.compileShader(shader);
	
	if ( ! gl.getShaderParameter(shader, gl.COMPILE_STATUS) ) {
		console.error(gl.getShaderInfoLog(shader));
		return null;
	}
	
	return shader;
};


let shaderProgram;

const initShaders = () => {
	const fragmentShader = getShader(gl, 'fs');
	const vertexShader = getShader(gl, 'vs');
	
	shaderProgram = gl.createProgram();
	gl.attachShader(shaderProgram, vertexShader);
	gl.attachShader(shaderProgram, fragmentShader);
	gl.linkProgram(shaderProgram);
	
	if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
		console.error(
			`Could not initialise shaders. Error: ${
				gl.getProgramInfoLog(shaderProgram)
			}`
		);
	}
	
	gl.useProgram(shaderProgram);
	
	shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	
	shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, 'aTextureCoord');
	gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
	
	shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
	shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');
	shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, 'uSampler');
};


const handleLoadedTexture = texture => {
	gl.bindTexture(gl.TEXTURE_2D, texture);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);
};


let neheTexture;

const initTexture = () => {
	neheTexture = gl.createTexture();
	neheTexture.image = new Image();
	neheTexture.image.onload = () => {
		console.log(`Loaded image: ${neheTexture.image.src}`);
		console.log(`size: ${neheTexture.image.width}x${neheTexture.image.height}`);
		handleLoadedTexture(neheTexture);
	};
	
	neheTexture.image.src = 'img/glass.gif';
};



let mvMatrix = mat4.create();
let pMatrix  = mat4.create();

const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	
	const error = gl.getError();
	if (error) {
		console.error('setMatrixUniforms():', gl.drawingBufferWidth, gl.drawingBufferHeight, error);
	}
};


const degToRad = degrees => degrees * Math.PI / 180;


let cubeVertexPositionBuffer;
let cubeVertexTextureCoordBuffer;
let cubeVertexIndexBuffer;

const initBuffers = () => {
	cubeVertexPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	const vertices = [
		// Front face
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		
		// Back face
		-1.0, -1.0, -1.0,
		-1.0, 1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, -1.0, -1.0,
		
		// Top face
		-1.0, 1.0, -1.0,
		-1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, -1.0,
		
		// Bottom face
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, 1.0,
		-1.0, -1.0, 1.0,
		
		// Right face
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		1.0, 1.0, 1.0,
		1.0, -1.0, 1.0,
		
		// Left face
		-1.0, -1.0, -1.0,
		-1.0, -1.0, 1.0,
		-1.0, 1.0, 1.0,
		-1.0, 1.0, -1.0,
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	cubeVertexPositionBuffer.itemSize = 3;
	cubeVertexPositionBuffer.numItems = 24;
	
	cubeVertexTextureCoordBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	
	const textureCoords = [
		// Front face
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		
		// Back face
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		
		// Top face
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		
		// Bottom face
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		1.0, 0.0,
		
		// Right face
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
		0.0, 0.0,
		
		// Left face
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
	cubeVertexTextureCoordBuffer.itemSize = 2;
	cubeVertexTextureCoordBuffer.numItems = 24;
	
	cubeVertexIndexBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	
	const cubeVertexIndices = [
		0, 1, 2, 0, 2, 3, // Front face
		4, 5, 6, 4, 6, 7, // Back face
		8, 9, 10, 8, 10, 11, // Top face
		12, 13, 14, 12, 14, 15, // Bottom face
		16, 17, 18, 16, 18, 19, // Right face
		20, 21, 22, 20, 22, 23 // Left face
	];
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
	cubeVertexIndexBuffer.itemSize = 1;
	cubeVertexIndexBuffer.numItems = 36;
};


let xRot = 0;
let yRot = 0;
let zRot = 0;

const drawScene = () => {
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [0.0, 0.0, -5.0]);
	
	mat4.rotate(mvMatrix, degToRad(xRot), [1, 0, 0]);
	mat4.rotate(mvMatrix, degToRad(yRot), [0, 1, 0]);
	mat4.rotate(mvMatrix, degToRad(zRot), [0, 0, 1]);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute,
		cubeVertexPositionBuffer.itemSize,
		gl.FLOAT,
		false,
		0,
		0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	gl.vertexAttribPointer(
		shaderProgram.textureCoordAttribute,
		cubeVertexTextureCoordBuffer.itemSize,
		gl.FLOAT,
		false,
		0,
		0
	);
	
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, neheTexture);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
};


let lastTime = 0;

const animate = () => {
	const timeNow = Date.now();
	
	if (lastTime != 0) {
		const elapsed = timeNow - lastTime;
		
		xRot += (90 * elapsed) / 1000.0;
		yRot += (90 * elapsed) / 1000.0;
		zRot += (90 * elapsed) / 1000.0;
	}
	
	lastTime = timeNow;
};


const tick = () => {
	drawScene();
	animate();
	frame(tick);
};


const start = () => {
	initContext(canvas);
	initShaders();
	initBuffers();
	initTexture();
	
	gl.clearColor(0, 0, 0, 1);
	gl.enable(gl.DEPTH_TEST);
	
	tick();
};

start();
