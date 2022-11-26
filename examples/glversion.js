'use strict';

const gl = require('..');

const { Document } = require('glfw-raub');


Document.setWebgl(gl);
new Document();

console.log(`
OpenGL
	vendor    : ${gl.getParameter(gl.VENDOR)}
	version   : ${gl.getParameter(gl.VERSION)}
	glsl      : ${gl.getParameter(gl.SHADING_LANGUAGE_VERSION)}
	renderer  : ${gl.getParameter(gl.RENDERER)}
	extensions: ${gl.getSupportedExtensions().length}
`);
