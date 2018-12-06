'use strict';

const webgl = require('webgl-raub');

const { Document } = require('glfw-raub');


Document.setWebgl(webgl);
const document = new Document();
console.log('extensions.js', 'DOC');
const extensions = webgl.getSupportedExtensions();
console.log(extensions.sort().join('\n'));
