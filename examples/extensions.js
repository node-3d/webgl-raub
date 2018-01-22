'use strict';

const webgl = require('node-webgl-raub');

const { Document } = require('node-glfw-raub');


Document.setWebgl(webgl);
const document = new Document();

const extensions = webgl.getSupportedExtensions();
console.log(extensions.sort().join('\n'));
