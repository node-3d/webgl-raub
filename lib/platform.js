var SDL = require('sdl');
var WebGL = require('./webgl');

module.exports = function () {

  process.on('SIGINT', function () { process.exit(0); });
  
  SDL.init(SDL.INIT.VIDEO);
//  SDL.events.on('event', console.dir);
  SDL.events.on('quit', function () { process.exit(0); });
  SDL.events.on("keydown", function (evt) {
    if (evt.sym === 99 && evt.mod === 64) process.exit(0); // Control+C
    if (evt.sym === 27) process.exit(0);  // ESC
  });
  var platform = {
    type: "nodeSDL",
    setTitle: setTitle,
    setIcon: setIcon,
    flip: SDL.GL.swapBuffers,
    getElementById: function(name) {
      return null;
    },
    createElement: function(name, width, height) {
      if(name.indexOf('canvas') != -1) {
        this.createWindow(width || 800,height || 800);
        this.canvas = this;
        WebGL.canvas = this;
        return this;
      }
      return null;
    },
    createWindow: function(width, height) {
      SDL.GL.setAttribute(SDL.GL.DOUBLEBUFFER, 1);

      var attribs=SDL.SURFACE.OPENGL;
      
      if(width==0 || height==0) {
        attribs |= SDL.SURFACE.FULLSCREEN;
        width=height=0;
      }
      else
        attribs |= SDL.SURFACE.RESIZABLE;
      
      var screen = SDL.setVideoMode(width, height, 0, attribs);
      this.width = this.drawingBufferWidth = screen.w; 
      this.height = this.drawingBufferHeight = screen.h;
      WebGL.viewport(0, 0, screen.w, screen.h);
    },
    getContext: function(name, options) {
      return WebGL;
    },
    on: function (name, callback) {
      var cb=callback;
      
      if (name === "resize") {
        var self=this;
        cb=function(evt) {
          if(WebGL.canvas) {
            WebGL.canvas.width = evt.width;
            WebGL.canvas.height = evt.height;
          }
          self.createWindow(evt.width, evt.height);
          callback(evt);
        }
      }
      
      SDL.events.addListener(name, cb);
    },
    addEventListener: function(name,callback) {
      this.on(name,callback);
    },
    removeEventListener: function(name,callback) {
      SDL.events.removeListener(name,callback);
    },
    requestAnimationFrame: function (callback, delay) {
      SDL.GL.swapBuffers();
      var timer= (delay==0) ? process.nextTick : setTimeout;
      var d= (delay==undefined || delay<0) ? 16 : delay;
      timer(function(){
          callback(new Date().getTime());
        }, d);
    },
  };

  Object.defineProperty(platform, 'onkeydown', {
    set: function(callback) { 
      this.on('keydown', callback);
      },
  });
  Object.defineProperty(platform, 'onkeyup', {
    set: function(callback) { 
      this.on('keyup', callback);
      },
  });

  return platform;
  
  function setTitle(title) {
    SDL.WM.setCaption(title, title);
  }

  function setIcon(path) {
    var img = SDL.IMG.load(path)
    SDL.WM.setIcon(img);
  }
};

