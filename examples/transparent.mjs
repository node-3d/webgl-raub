'use strict';

import Image from 'image-raub';
import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';
import {
	cubeTexCoords, cubeVertexIndices, cubeVertexNormals, cubeVertices, transparentShaders,
} from './utils/presets.mjs';
import { buildShader } from './utils/build-shader.mjs';
import { mat4, mat3, vec3 } from './utils/glMatrix-0.9.5.min.js';
import { deg2rad } from './utils/deg2rad.mjs';


Document.setWebgl(gl);
const document = new Document({
	vsync: true, autoEsc: true, autoFullscreen: true, title: 'Transparent',
});

const shaderProgram = buildShader(transparentShaders);
gl.useProgram(shaderProgram);

shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, 'aVertexPosition');
shaderProgram.vertexNormalAttribute = gl.getAttribLocation(shaderProgram, 'aVertexNormal');
shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, 'aTextureCoord');
shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, 'aVertexColor');
shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, 'uPMatrix');
shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, 'uMVMatrix');
shaderProgram.nMatrixUniform = gl.getUniformLocation(shaderProgram, 'uNMatrix');
shaderProgram.samplerUniform = gl.getUniformLocation(shaderProgram, 'uSampler');
shaderProgram.useLightingUniform = gl.getUniformLocation(shaderProgram, 'uUseLighting');
shaderProgram.ambientColorUniform = gl.getUniformLocation(shaderProgram, 'uAmbientColor');
shaderProgram.lightingDirectionUniform = gl.getUniformLocation(shaderProgram, 'uLightingDirection');
shaderProgram.directionalColorUniform = gl.getUniformLocation(shaderProgram, 'uDirectionalColor');
shaderProgram.alphaUniform = gl.getUniformLocation(shaderProgram, 'uAlpha');


const glassTexture = gl.createTexture();
glassTexture.image = new Image();
glassTexture.image.onload = () => {
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	
	gl.bindTexture(gl.TEXTURE_2D, glassTexture);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, glassTexture.image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
	gl.generateMipmap(gl.TEXTURE_2D);
	
	gl.bindTexture(gl.TEXTURE_2D, null);
};
glassTexture.image.src = 'img/glass.gif';


const mvMatrix = mat4.create();
const pMatrix = mat4.create();


const setMatrixUniforms = () => {
	gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, pMatrix);
	gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, mvMatrix);
	const normalMatrix = mat3.create();
	mat4.toInverseMat3(mvMatrix, normalMatrix);
	mat3.transpose(normalMatrix);
	gl.uniformMatrix3fv(shaderProgram.nMatrixUniform, false, normalMatrix);
};

let xRot = 0;
let xSpeed = 5;

let yRot = 0;
let ySpeed = -5;

let z = -5.0;


const currentlyPressedKeys = {};

document.on('keydown', (evt) => {
	// console.log("[KEYDOWN] keyCode: "+evt.keyCode+" which: "+evt.which);
	currentlyPressedKeys[evt.keyCode] = true;
	handleKeys();
});

document.on('keyup', (evt) => {
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


const cubeVertexPositionBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeVertices), gl.STATIC_DRAW);
cubeVertexPositionBuffer.itemSize = 3;

const cubeVertexNormalBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeVertexNormals), gl.STATIC_DRAW);
cubeVertexNormalBuffer.itemSize = 3;

const cubeVertexTextureCoordBuffer = gl.createBuffer();
gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);

gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(cubeTexCoords), gl.STATIC_DRAW);
cubeVertexTextureCoordBuffer.itemSize = 2;

const cubeVertexIndexBuffer = gl.createBuffer();
gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeVertexIndices), gl.STATIC_DRAW);
cubeVertexIndexBuffer.itemSize = 1;
cubeVertexIndexBuffer.numItems = 36;


const drawScene = () => {
	gl.clearColor(0.0, 0.0, 0.0, 1.0);
	gl.enable(gl.DEPTH_TEST);
	
	gl.viewport(0, 0, gl.drawingBufferWidth, gl.drawingBufferHeight);
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
	
	gl.useProgram(shaderProgram);
	gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);
	gl.enableVertexAttribArray(shaderProgram.vertexNormalAttribute);
	gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);
	gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);
	
	mat4.perspective(45, gl.drawingBufferWidth / gl.drawingBufferHeight, 0.1, 100.0, pMatrix);
	
	mat4.identity(mvMatrix);
	
	mat4.translate(mvMatrix, [0.0, 0.0, z]);
	
	mat4.rotate(mvMatrix, deg2rad(xRot), [1, 0, 0]);
	mat4.rotate(mvMatrix, deg2rad(yRot), [0, 1, 0]);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexNormalBuffer);
	gl.vertexAttribPointer(
		shaderProgram.vertexNormalAttribute, cubeVertexNormalBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
	gl.vertexAttribPointer(
		shaderProgram.textureCoordAttribute, cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0
	);
	
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D, glassTexture);
	gl.uniform1i(shaderProgram.samplerUniform, 0);
	
	const blending = 0.5;
	if (blending > 0) {
		gl.blendFunc(gl.SRC_ALPHA, gl.ONE);
		gl.enable(gl.BLEND);
		gl.disable(gl.DEPTH_TEST);
		gl.uniform1f(
			shaderProgram.alphaUniform,
			parseFloat(blending),
		);
	} else {
		gl.disable(gl.BLEND);
		gl.enable(gl.DEPTH_TEST);
	}
	
	const lighting = false;
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
			parseFloat(ambientR),
			parseFloat(ambientG),
			parseFloat(ambientB),
		);
		
		const lightingDirection = [
			parseFloat(lightDirectionX),
			parseFloat(lightDirectionY),
			parseFloat(lightDirectionZ),
		];
		const adjustedLD = vec3.create();
		vec3.normalize(lightingDirection, adjustedLD);
		vec3.scale(adjustedLD, -1);
		gl.uniform3fv(shaderProgram.lightingDirectionUniform, adjustedLD);
		
		gl.uniform3f(
			shaderProgram.directionalColorUniform,
			parseFloat(directionalR),
			parseFloat(directionalG),
			parseFloat(directionalB),
		);
	}
	
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
	setMatrixUniforms();
	gl.drawElements(gl.TRIANGLES, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);
	
	// Cleanup GL state
	gl.bindTexture(gl.TEXTURE_2D, null);
	gl.bindBuffer(gl.ARRAY_BUFFER, null);
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, null);
	gl.useProgram(null);
};

const tick = () => {
	xRot = (xSpeed * Date.now()) * 0.001;
	yRot = (ySpeed * Date.now()) * 0.001;
	
	drawScene();
	
	document.requestAnimationFrame(tick);
};

document.requestAnimationFrame(tick);
