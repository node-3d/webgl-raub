'use strict';

const platformPaths = {
	win32  : '../bin_windows/webgl',
	linux  : '../bin_linux/webgl'  ,
	darwin : '../bin_darwin/webgl' ,
};

const binPath = platformPaths[process.platform];

const gl = require(binPath);

var Image = module.exports = gl.Image;
var events = require('events');


Object.defineProperty(Image.prototype, 'onload', {
	set(callback) { 
		this.on('load', callback);
	},
});

// extend prototype
function inherits(target, source) {
	
	for (var k in source.prototype){
		target.prototype[k] = source.prototype[k];
	}
	
}

inherits(Image, events.EventEmitter);


