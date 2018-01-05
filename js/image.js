'use strict';

const gl     = require('../binary/webgl');
const Image  = gl.Image;
const events = require('events');


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

inherit(Image, events.EventEmitter);


module.exports = Image;
