'use strict';

const WebGL = require('../index');


const document = WebGL.document();
const canvas = document.createElement('canvas');
const gl = canvas.getContext('webgl');

const extensions = gl.getSupportedExtensions();
console.log(extensions.sort().join('\n'));
