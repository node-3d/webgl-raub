'use strict';

const webgl = require('..');
const Image = require('image-raub');

const { Document } = require('glfw-raub');

const { mat4 } = require('./libs/glMatrix-0.9.5.min');


Document.setWebgl(webgl);
const document = new Document();
webgl.canvas = document;

const canvas = document.createElement('canvas');
let gl;

document.title = 'Screen-aligned texture';
const requestAnimFrame = document.requestAnimationFrame;

let shaders = {
	'shader-fs' : [
		'#ifdef GL_ES',
		'  precision mediump float;',
		'#endif',
		'varying vec2 vTextureCoord;',
		'uniform sampler2D uSampler;',
		'void main(void) {',
		'    gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));',
		'}'
	].join('\n'),
	'shader-vs' : [
		'attribute vec3 aVertexPosition;',
		'attribute vec2 aTextureCoord;',
		'uniform mat4 uMVMatrix;',
		'uniform mat4 uPMatrix;',
		'varying vec2 vTextureCoord;',
		'void main(void) {',
		'    gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);',
		'    vTextureCoord = aTextureCoord;',
		'}'
	].join('\n')
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
	let shader;
	
	if (!shaders[id]) {
		return null;
	}
	let str = shaders[id];
	
	if (id.match(/-fs/)) {
		shader = gl.createShader(gl.FRAGMENT_SHADER);
	} else if (id.match(/-vs/)) {
		shader = gl.createShader(gl.VERTEX_SHADER);
	} else {
		return null;
	}
	
	gl.shaderSource(shader, str);
	gl.compileShader(shader);
	
	if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
		console.log(gl.getShaderInfoLog(shader));
		return null;
	}
	
	return shader;
};


let shaderProgram;

const initShaders = () => {
	let fragmentShader = getShader(gl, 'shader-fs');
	let vertexShader = getShader(gl, 'shader-vs');
	
	shaderProgram = gl.createProgram();
	gl.attachShader(shaderProgram, vertexShader);
	gl.attachShader(shaderProgram, fragmentShader);
	gl.linkProgram(shaderProgram);
	
	if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
		console.log('Could not initialise shaders');
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
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
	gl.bindTexture(gl.TEXTURE_2D, null);
};


let lena;

const initTexture = () => {
	lena = gl.createTexture();
	lena.image = new Image();
	lena.image.onload = () => {
		console.log(`Loaded image: ${lena.image.src}`);
		console.log(`size: ${lena.image.width}x${lena.image.height}`);
		handleLoadedTexture(lena);
	};
	lena.image.src = __dirname + '/img/glass.gif';
};


let mvMatrix = mat4.create();
let pMatrix = mat4.create();


const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
};

let cubeVertexPositionBuffer;
let cubeVertexTextureCoordBuffer;
let cubeVertexIndexBuffer;

const initBuffers = () => {
	cubeVertexPositionBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	const vertices = [
		// Front face
		-1.0, -1.0, 0.5,
		1.0, -1.0, 0.5,
		1.0, 1.0, 0.5,
		-1.0, 1.0, 0.5,
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	cubeVertexPositionBuffer.itemSize = 3;
	cubeVertexPositionBuffer.numItems = 4;
	
	cubeVertexTextureCoordBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	let textureCoords = [
		// Front face
		0.0, 0.0,
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoords), gl.STATIC_DRAW);
	cubeVertexTextureCoordBuffer.itemSize = 2;
	cubeVertexTextureCoordBuffer.numItems = 4;
	
	cubeVertexIndexBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	let cubeVertexIndices = [
		0, 1, 2, 0, 2, 3, // Front face
	];
	gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
	cubeVertexIndexBuffer.itemSize = 1;
	cubeVertexIndexBuffer.numItems = 6;
};


const drawScene = () => {
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	mat4.ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
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
	gl.bindTexture(gl.TEXTURE_2D, lena);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
};


const tick = () => {
	drawScene();
	requestAnimFrame(tick);
};


const start = () => {
	initContext(canvas);
	initShaders();
	initBuffers();
	initTexture();
	
	gl.clearColor(0.0, 0.0, 0.0, 1.0);
	gl.enable(gl.DEPTH_TEST);
	
	tick();
};

start();

