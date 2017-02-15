'use strict';

require('node-glfw-raub');

module.exports = {
	webgl   : require('./lib/webgl'),
	Image   : require('./lib/image'),
	document: require('./lib/platform_glfw')
};
