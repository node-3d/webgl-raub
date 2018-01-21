'use strict';

require('node-glfw-raub');

const webgl = require('./binary/webgl');


// Initialize GLEW
if ( ! webgl.init() ) {
	throw new Error('Failed to initialize WebGL');
}

module.exports = webgl;
