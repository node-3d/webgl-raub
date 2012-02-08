var SDL = require('sdl');
var WebGL = require('./webgl');

module.exports = function () {

  process.on('SIGINT', function () { process.exit(0); });
  
  SDL.init(SDL.INIT.VIDEO);
//  SDL.events.on('event', console.dir);
  SDL.events.on('QUIT', function () { process.exit(0); });
  SDL.events.on("KEYDOWN", function (evt) {
    if (evt.sym === 99 && evt.mod === 64) process.exit(0); // Control+C
    if (evt.sym === 27) process.exit(0);  // ESC
  });
  var platform = {
    type: "nodeSDL",
    loadTexture: loadTexture,
    setTitle: setTitle,
    setIcon: setIcon,
    flip: SDL.GL.swapBuffers,
    getElementById: function(name) {
      return this;
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
      this.width = screen.w; this.height = screen.h;
      WebGL.viewport(0, 0, screen.w, screen.h);
    },
    getContext: function(name) {
      return WebGL;
    },
    on: function (name, callback) {
      if (name === "mousemove") name = "MOUSEMOTION";
      SDL.events.on(name, callback);
    },
    requestAnimationFrame: function (callback, delay) {
      SDL.GL.swapBuffers();
      var timer= (delay==0) ? process.nextTick : setTimeout;
      var d= (delay==undefined || delay<0) ? 16 : delay;
      timer(function(){
          callback(new Date().getTime());
        }, d);
    }
  };

  return platform;
  
  function loadTexture(path, callback) {
    var gl = WebGL;
    try {
      // TODO: Get actual image from SDL and convert it
      var gltexture = gl.createTexture();
      gl.bindTexture(gl.TEXTURE_2D, gltexture);
      gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, img);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
      gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
    } catch(err) {
      return callback(err);
    }
    callback(null, gltexture);
  }

  function setTitle(title) {
    SDL.WM.setCaption(title, title);
  }

  function setIcon(path) {
    var img = SDL.IMG.load(path)
    SDL.WM.setIcon(img);
  }
};

