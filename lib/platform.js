var sfml = require('node_sfml');
var WebGL = require('./webgl');

module.exports = {
  sfml : sfml,
  document : function () {
    process.on('SIGINT', function () { process.exit(0); });
    
    /*SDL.events.on('QUIT', function () { process.exit(0); });
    SDL.events.on("KEYDOWN", function (evt) {
      if (evt.sym === 99 && evt.mod === 64) process.exit(0); // Control+C
      if (evt.sym === 27) process.exit(0);  // ESC
    });*/
    var window;
    var events;
    
    var platform = {
      type: "nodeSFML",
      setTitle: function(title) {
        if(window)
          window.SetTitle(title);
      },
      setIcon: function(filename) {
        // TODO
      },
      flip: function() {
        if(window)
          window.Display();
      },
      getElementById: function(name) {
        return this;
      },
      createWindow : function(width, height) {
        window = new sfml.RenderWindow(new sfml.VideoMode(width, height),
            "SFML window", sfml.Style.Default, new sfml.ContextSettings(8));
  
        Object.defineProperty(window, 'events', {
          get : function() {
            if (events)
              return events;
            events = new (require('events').EventEmitter);
            var now = Date.now();
            setInterval(function() {
              var after = Date.now();
              var delta = after - now;
              now = after;
              var data;
              // console.log(require('util').inspect(this))
              while (data = window.PollEvent()) {
                // console.log(require('util').inspect(data))
                events.emit('event', data);
                events.emit(data.Type, data);
              }
              events.emit('tick', delta);
            }, 16);
            return events;
          }
        });
  
        this.width = width; this.height = height;
        return window;
      },
      getContext: function(name) {
        return WebGL;
      },
      on: function (name, callback) {
        if(!window) return;
        
        window.events.on(name, callback);
      },
      requestAnimationFrame: function (callback, delay) {
        if(!window) return;
        
        window.Display();
        var timer= (delay==0) ? process.nextTick : setTimeout;
        var d= (delay==undefined || delay<0) ? 16 : delay;
        timer(function(){
            callback(new Date().getTime());
          }, d);
      }
    };
  
    return platform;
  }
  
}
