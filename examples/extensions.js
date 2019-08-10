'use strict';

const webgl = require('..');

const { Document } = require('glfw-raub');


Document.setWebgl(webgl);
new Document();

const extensions = webgl.getSupportedExtensions();
console.log('----- WebGL -----');
console.log(extensions.sort().join('\n'));
console.log('----- NATIVE -----');
console.log(webgl._realExtensions.sort().join('\n'));
