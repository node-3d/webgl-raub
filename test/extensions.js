'use strict';

const { Document } = require('..');


const document = new Document();
const canvas = document.createElement('canvas');
const gl = canvas.getContext('webgl');

const extensions = gl.getSupportedExtensions();
console.log(extensions.sort().join('\n'));
