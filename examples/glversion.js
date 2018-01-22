'use strict';

const gl = require('node-webgl-raub');

const { Document } = require('node-glfw-raub');


Document.setWebgl(gl);
const document = new Document();

console.log(`
OpenGL
	vendor                   : ${ gl.getParameter(gl.VENDOR) }
	version                  : ${ gl.getParameter(gl.VERSION) }
	shading language version : ${ gl.getParameter(gl.SHADING_LANGUAGE_VERSION) }
	renderer                 : ${ gl.getParameter(gl.RENDERER) }
	extensions               : ${ gl.getSupportedExtensions().length }
`);
