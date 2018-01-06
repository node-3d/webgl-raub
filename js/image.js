'use strict';

const EventEmitter = require('events');

const gl = require('../binary/webgl');

const { Image } = gl;


Object.defineProperty(Image.prototype, 'onload', {
	set(callback) { 
		this.on('load', callback);
	},
});

// extend prototype
function inherit(target, source) {
	
	for (let k in source.prototype){
		target.prototype[k] = source.prototype[k];
	}
	
}

inherit(Image, EventEmitter);


module.exports = Image;
