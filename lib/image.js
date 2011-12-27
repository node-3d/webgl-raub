// javascript shim that lets our object inherit from EventEmitter
var Image = require(__dirname + '/../build/Release/webgl.node').Image;
var events = require('events');

inherits(Image, events.EventEmitter);
exports.Image = Image;

Image.prototype.onload = function(callback) {
  this.on('load',callback);
}

// extend prototype
function inherits(target, source) {
  for (var k in source.prototype)
    target.prototype[k] = source.prototype[k];
}
