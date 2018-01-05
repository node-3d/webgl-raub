'use strict';

require('node-glfw-raub');


module.exports = {
	webgl    : require('./js/webgl'),
	Image    : require('./js/image'),
	document : require('./js/platform_glfw')
};
