'use strict';

const webgl = require('..');
const Image = require('image-raub');

const { Document } = require('glfw-raub');

const { mat4, mat3, vec3 } = require('./libs/glMatrix-0.9.5.min');


Document.setWebgl(webgl);
const document = new Document();
webgl.canvas = document;

const canvas = document.createElement('canvas');
const frame = document.requestAnimationFrame;
let gl;

document.title = 'Lesson08';


const shaders = {
	'shader-fs': [
		'#ifdef GL_ES',
		'  precision mediump float;',
		'#endif',
		'varying vec2 vTextureCoord;',
		'varying vec3 vLightWeighting;',
		'uniform float uAlpha;',
		'uniform sampler2D uSampler;',
		'void main(void) {',
		'	vec4 textureColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));',
		'	gl_FragColor = vec4(textureColor.rgb * vLightWeighting, textureColor.a * uAlpha);',
		'}'
	].join('\n'),
	'shader-vs': [
		'attribute vec3 aVertexPosition;',
		'attribute vec3 aVertexNormal;',
		'attribute vec2 aTextureCoord;',
		'uniform mat4 uMVMatrix;',
		'uniform mat4 uPMatrix;',
		'uniform mat3 uNMatrix;',
		'uniform vec3 uAmbientColor;',
		'uniform vec3 uLightingDirection;',
		'uniform vec3 uDirectionalColor;',
		'uniform bool uUseLighting;',
		'varying vec2 vTextureCoord;',
		'varying vec3 vLightWeighting;',
		'void main(void) {',
		'	gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);',
		'	vTextureCoord = aTextureCoord;',
		'	if (!uUseLighting) {',
		'		vLightWeighting = vec3(1.0, 1.0, 1.0);',
		'	} else {',
		'		vec3 transformedNormal = uNMatrix * aVertexNormal;',
		'		float directionalLightWeighting = max(dot(transformedNormal, uLightingDirection), 0.0);',
		'		vLightWeighting = uAmbientColor + uDirectionalColor * directionalLightWeighting;',
		'	}',
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
	const str = shaders[id];
	
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
	const fragmentShader = getShader(gl, 'shader-fs');
	const vertexShader = getShader(gl, 'shader-vs');
	
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
	
	shaderProgram.vertexNormalAttribute = gl.getAttribLocation(shaderProgram, 'aVertexNormal');
	gl.enableVertexAttribArray(shaderProgram.vertexNormalAttribute);
	
	shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, 'aTextureCoord');
	gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
	
	shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
	shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
	shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');
	shaderProgram.nMatrixUniform = gl.getUniformLocation(shaderProgram, 'uNMatrix');
	shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, 'uSampler');
	shaderProgram.useLightingUniform = gl.getUniformLocation(shaderProgram, 'uUseLighting');
	shaderProgram.ambientColorUniform = gl.getUniformLocation(shaderProgram, 'uAmbientColor');
	shaderProgram.lightingDirectionUniform = gl.getUniformLocation(shaderProgram, 'uLightingDirection');
	shaderProgram.directionalColorUniform = gl.getUniformLocation(shaderProgram, 'uDirectionalColor');
	shaderProgram.alphaUniform = gl.getUniformLocation(shaderProgram, 'uAlpha');
};


const handleLoadedTexture = texture => {
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	
	gl.bindTexture(gl.TEXTURE_2D, texture);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
	gl.generateMipmap(gl.TEXTURE_2D);
	
	gl.bindTexture(gl.TEXTURE_2D, null);
};


let glassTexture;

const initTexture = () => {
	glassTexture = gl.createTexture();
	glassTexture.image = new Image();
	glassTexture.image.onload = () => {
		handleLoadedTexture(glassTexture);
	};
	glassTexture.image.src = __dirname + '/img/glass.gif';
};


let mvMatrix = mat4.create();
let pMatrix = mat4.create();


const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	const normalMatrix = mat3.create();
	mat4.toInverseMat3(mvMatrix, normalMatrix);
	mat3.transpose(normalMatrix);
	gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, normalMatrix);
};


const degToRad = degrees => degrees * Math.PI / 180;



let xRot = 0;
let xSpeed = 5;

let yRot = 0;
let ySpeed = -5;

let z = -5.0;


const currentlyPressedKeys = {};

document.on('keydown', evt => {
	// console.log("[KEYDOWN] keyCode: "+evt.keyCode+" which: "+evt.which);
	currentlyPressedKeys[evt.keyCode] = true;
	handleKeys();
});

document.on('keyup', evt => {
	// console.log("[KEYUP] keyCode: "+evt.keyCode);
	currentlyPressedKeys[evt.keyCode] = false;
});


const handleKeys = () => {
	if (currentlyPressedKeys[221]) {
		// ]
		z -= 0.5;
	}
	if (currentlyPressedKeys[220]) {
		// \
		z += 0.5;
	}
	if (currentlyPressedKeys[37]) {
		// Left cursor key
		ySpeed -= 1;
	}
	if (currentlyPressedKeys[39]) {
		// Right cursor key
		ySpeed += 1;
	}
	if (currentlyPressedKeys[38]) {
		// Up cursor key
		xSpeed -= 1;
	}
	if (currentlyPressedKeys[40]) {
		// Down cursor key
		xSpeed += 1;
	}
	//console.log("speed: "+xSpeed+" "+ySpeed+" "+z);
};


let cubeVertexPositionBuffer;
let cubeVertexNormalBuffer;
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
		-1.0, 1.0, -1.0
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
	cubeVertexPositionBuffer.itemSize = 3;
	cubeVertexPositionBuffer.numItems = 24;
	
	cubeVertexNormalBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
	let vertexNormals = [
		// Front face
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		0.0, 0.0, 1.0,
		
		// Back face
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		0.0, 0.0, -1.0,
		
		// Top face
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 1.0, 0.0,
		
		// Bottom face
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		0.0, -1.0, 0.0,
		
		// Right face
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		1.0, 0.0, 0.0,
		
		// Left face
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0,
		-1.0, 0.0, 0.0
	];
	gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertexNormals), gl.STATIC_DRAW);
	cubeVertexNormalBuffer.itemSize = 3;
	cubeVertexNormalBuffer.numItems = 24;
	
	cubeVertexTextureCoordBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	let textureCoords = [
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
	let cubeVertexIndices = [
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


const drawScene = () => {
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [0.0, 0.0, z]);
	
	mat4.rotate(mvMatrix, degToRad(xRot), [1, 0, 0]);
	mat4.rotate(mvMatrix, degToRad(yRot), [0, 1, 0]);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute,
		cubeVertexPositionBuffer.itemSize,
		gl.FLOAT,
		false,
		0,
		0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexNormalAttribute,
		cubeVertexNormalBuffer.itemSize,
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
	gl.bindTexture(gl.TEXTURE_2D, glassTexture);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	
	const blending = 0.5; //document.getElementById("blending").checked;
	if (blending > 0) {
		gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
		gl.enable(gl.BLEND);
		gl.disable(gl.DEPTH_TEST);
		gl.uniform1f(
			shaderProgram.alphaUniform,
			parseFloat(blending /*document.getElementById("alpha").value*/)
		);
	} else {
		gl.disable(gl.BLEND);
		gl.enable(gl.DEPTH_TEST);
	}
	
	const lighting = false; //document.getElementById("lighting").checked;
	const ambientR = 0.2;
	const ambientG = 0.2;
	const ambientB = 0.2;
	
	const lightDirectionX = -0.25;
	const lightDirectionY = -0.25;
	const lightDirectionZ = -1;
	
	const directionalR = 0.8;
	const directionalG = 0.8;
	const directionalB = 0.8;
	
	gl.uniform1i(shaderProgram.useLightingUniform, lighting);
	if (lighting) {
		gl.uniform3f(
			shaderProgram.ambientColorUniform,
			parseFloat(ambientR /*document.getElementById("ambientR").value*/),
			parseFloat(ambientG /*document.getElementById("ambientG").value*/),
			parseFloat(ambientB /*document.getElementById("ambientB").value*/)
		);
		
		const lightingDirection = [
			parseFloat(lightDirectionX /*document.getElementById("lightDirectionX").value*/),
			parseFloat(lightDirectionY /*document.getElementById("lightDirectionY").value*/),
			parseFloat(lightDirectionZ /*document.getElementById("lightDirectionZ").value*/)
		];
		const adjustedLD = vec3.create();
		vec3.normalize(lightingDirection, adjustedLD);
		vec3.scale(adjustedLD, -1);
		gl.uniform3fv(shaderProgram.lightingDirectionUniform, adjustedLD);
		
		gl.uniform3f(
			shaderProgram.directionalColorUniform,
			parseFloat(directionalR /*document.getElementById("directionalR").value*/),
			parseFloat(directionalG /*document.getElementById("directionalG").value*/),
			parseFloat(directionalB /*document.getElementById("directionalB").value*/)
		);
	}
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
};


let lastTime = 0;


const animate = () => {
	let timeNow = new Date().getTime();
	if (lastTime != 0) {
		let elapsed = timeNow - lastTime;
		xRot += (xSpeed * elapsed) / 1000.0;
		yRot += (ySpeed * elapsed) / 1000.0;
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
	gl.clearColor(0.0, 0.0, 0.0, 1.0);
	gl.enable(gl.DEPTH_TEST);
	tick();
};

start();
