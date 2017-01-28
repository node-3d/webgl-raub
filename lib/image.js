// javascript shim that lets our object inherit from EventEmitter

const os = require('os');

const addonPaths = {
	win32 : '../bin_win32/webgl' ,
	linux : '../bin_linux/webgl' ,
	darwin: '../bin_darwin/webgl',
};

const gl = require(addonPaths[os.platform()]);

var Image = module.exports = gl.Image;
var events = require('events');


Object.defineProperty(Image.prototype, 'onload', {
  set: function(callback) { 
    this.on('load', callback);
    },
});

inherits(Image, events.EventEmitter);

// extend prototype
function inherits(target, source) {
  for (var k in source.prototype)
    target.prototype[k] = source.prototype[k];
}
