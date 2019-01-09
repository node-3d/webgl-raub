'use strict';

const webgl = require('webgl-raub');

const { Document } = require('glfw-raub');


Document.setWebgl(webgl);
new Document();

const extensions = webgl.getSupportedExtensions();
console.log(extensions.sort().join('\n'));
