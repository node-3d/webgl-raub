// javascript shim that lets our object inherit from EventEmitter
var Image = module.exports = require('bindings')('webgl').Image;
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
