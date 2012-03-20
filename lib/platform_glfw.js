var GLFW = require('node-glfw');
var WebGL = require('./webgl');

module.exports = function () {

  process.on('SIGINT', function () { process.exit(0); });
  
  var events;
  var platform;
  Object.defineProperty(GLFW, 'events', {
    get: function () {
      if (events) return events;
      events = new (require('events').EventEmitter);
      
      var _emit=events.emit;
      events.emit=function() {
        var args = Array.prototype.slice.call(arguments);
        var evt= args[1]; // args[1] is the event, args[0] is the type of event
        //console.log("emitting event: "+require('util').inspect(args));
        evt.preventDefault = function () {};
        evt.stopPropagation = function () {};
        if(evt.type==='resize' && platform) {
          platform.width=evt.width;
          platform.height=evt.height;
        }
        _emit.apply(this,args);
      };
      return events;
    }
  });

  GLFW.Init();
  //  GLFW.events.on('event', console.dir);
  GLFW.events.on('quit', function () { process.exit(0); });
  GLFW.events.on("keydown", function (evt) {
    if (evt.keyCode === 'C'.charCodeAt(0) && evt.ctrlKey) process.exit(0); // Control+C
    if (evt.keyCode === 27) process.exit(0);  // ESC
  });

  platform = {
    type: "nodeGLFW",
    setTitle: GLFW.SetWindowTitle,
    setIcon: function(){},
    flip: GLFW.SwapBuffers,
    getElementById: function(name) {
      return null; //this;
    },
    createElement: function(name, width, height) {
      if(name.indexOf('canvas')>=0) {
        this.createWindow(width || 800, height || 800);
        this.canvas = this;
        WebGL.canvas = this;
        return this;
      }
      return null;
    },
    createWindow: function(width, height) {
      var attribs=GLFW.WINDOW;
      
      if(width==0 || height==0) {
        attribs = GLFW.FULLSCREEN;
        width=height=0;
      }
      
      var resizeListeners=GLFW.events.listeners('resize');
      GLFW.events.removeAllListeners('resize');
      
      GLFW.OpenWindowHint(GLFW.WINDOW_NO_RESIZE, 0);
      
      // we use OpenGL 2.1, GLSL 1.20. Comment this for now as this is for GLSL 1.50
      //GLFW.OpenWindowHint(GLFW.OPENGL_FORWARD_COMPAT, 1);
      //GLFW.OpenWindowHint(GLFW.OPENGL_VERSION_MAJOR, 3);
      //GLFW.OpenWindowHint(GLFW.OPENGL_VERSION_MINOR, 2);
      //GLFW.OpenWindowHint(GLFW.OPENGL_PROFILE, GLFW.OPENGL_CORE_PROFILE);
      
      if(!GLFW.OpenWindow( width, height, 
          0,0,0,0, // r,g,b,a bits
          24,0, // depth, stencil bits
          attribs ) )
        throw "Can't initialize GL surface";
      
      //GLFW.SwapBuffers();
      
      for(l in resizeListeners)
        GLFW.events.addListener('resize',resizeListeners[l]);
      
      var size=GLFW.GetWindowSize();
      this.width = this.drawingBufferWidth=size.width; 
      this.height = this.drawingBufferHeight=size.height;
    },
    getContext: function(name) {
      return WebGL;
    },
    on: function (name, callback) {
      GLFW.events.on(name, callback);
    },
    addEventListener: function(name,callback) {
      GLFW.events.on(name,callback);
    },
    removeEventListener: function(name,callback) {
      GLFW.events.removeListener(name,callback);
    },
    requestAnimationFrame: function (callback, delay) {
      GLFW.SwapBuffers();
      var timer= (delay==0) ? process.nextTick : setTimeout;
      var d= (delay==undefined || delay<0) ? 16 : delay;
      timer(function(){
          callback(new Date().getTime());
        }, d);
    }
  };

  Object.defineProperty(platform, 'AntTweakBar', {
    get: function(cb) {
      return new GLFW.AntTweakBar();
    }
  });
  
  Object.defineProperty(platform, 'onkeydown', {
    set: function(cb) {
      this.on('keydown',cb);
    }
  });
  
  Object.defineProperty(platform, 'onkeyup', {
    set: function(cb) {
      this.on('keyup',cb);
    }
  });

  return platform;
};

