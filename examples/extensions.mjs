import glfw from 'glfw-raub';
const { Document } = glfw;

import gl from '../index.js';


Document.setWebgl(gl);
const _doc = new Document();

const extensions = gl.getSupportedExtensions();
console.log('----- WebGL -----');
console.log(extensions.sort().join('\n'));
console.log('----- NATIVE -----');
console.log(gl._realExtensions.sort().join('\n'));
