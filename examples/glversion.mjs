'use strict';

import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';


Document.setWebgl(gl);
const _doc = new Document();

console.log(`
OpenGL
	vendor    : ${gl.getParameter(gl.VENDOR)}
	version   : ${gl.getParameter(gl.VERSION)}
	glsl      : ${gl.getParameter(gl.SHADING_LANGUAGE_VERSION)}
	renderer  : ${gl.getParameter(gl.RENDERER)}
	extensions: ${gl.getSupportedExtensions().length}
`);
