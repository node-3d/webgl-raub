'use strict';

const glfw	= require('node-glfw');
const webgl = require('./webgl');


module.exports = function () {
	
	if (process.platform !== 'win32') {
		process.on('SIGINT', function () { process.exit(0); });
	}
	
	var window;
	
	glfw.Init();
	
	glfw.events.on('quit', function () { process.exit(0); });
	glfw.events.on('keydown', function (evt) {
		if (evt.keyCode === 27) process.exit(0);	// ESC
	});
	
	
	const platform = {
		
		type: 'nodeGLFW',
		
		ratio: 1, // ratio between window and framebuffer, normally 1 except on screens like Mac Retina
		
		
		setTitle(title) {
			glfw.SetWindowTitle(window, title);
		},
		
		
		setIcon() { },
		
		
		flip() {
			glfw.SwapBuffers(window);
		},
		
		
		getElementById(name) {
			return this.createElement(name);
		},
		
		
		createElement(name, width, height) {
			if (name.toLowerCase().indexOf('canvas') >= 0) {
				this.createWindow(width || 800, height || 600);
				this.canvas = this;
				webgl.canvas = this;
				return this;
			}
			return null;
		},
		
		
		createWindow(width, height) {
			var attribs = glfw.WINDOW;
			
			if (width == 0 || height == 0) {
				attribs = glfw.FULLSCREEN;
				width = height = 0;
			}
			
			var resizeListeners = [], rl = glfw.events.listeners("framebuffer_resize");
			for (let l = 0, ln = rl.length; l < ln; ++l) {
				resizeListeners[l] = rl[l];
			}
			
			glfw.events.removeAllListeners("framebuffer_resize");
			
			glfw.DefaultWindowHints();
			
			// we use OpenGL 2.1, GLSL 1.20. Comment this for now as this is for GLSL 1.50
			//glfw.OpenWindowHint(glfw.OPENGL_FORWARD_COMPAT, 1);
			//glfw.OpenWindowHint(glfw.OPENGL_VERSION_MAJOR, 3);
			//glfw.OpenWindowHint(glfw.OPENGL_VERSION_MINOR, 2);
			//glfw.OpenWindowHint(glfw.OPENGL_PROFILE, glfw.OPENGL_CORE_PROFILE);
			glfw.WindowHint(glfw.RESIZABLE, 1);
			glfw.WindowHint(glfw.VISIBLE, 1);
			glfw.WindowHint(glfw.DECORATED, 1);
			glfw.WindowHint(glfw.RED_BITS, 8);
			glfw.WindowHint(glfw.GREEN_BITS, 8);
			glfw.WindowHint(glfw.BLUE_BITS, 8);
			glfw.WindowHint(glfw.DEPTH_BITS, 24);
			glfw.WindowHint(glfw.REFRESH_RATE, 0);
			
			if ( ! (window = glfw.CreateWindow(width, height)) ) {
				glfw.Terminate();
				throw "Can't initialize GL surface";
			}
			
			glfw.MakeContextCurrent(window);
			
			glfw.SetWindowTitle("webgl");
			
			// make sure GLEW is initialized
			webgl.Init();
			
			glfw.SwapBuffers(window);
			glfw.SwapInterval(0); // Disable VSync (we want to get as high FPS as possible!)
			
			for (let l = 0, ln = resizeListeners.length; l < ln; ++l) {
				glfw.events.addListener("framebuffer_resize", resizeListeners[l]);
			}
			
			var sizeWin = glfw.GetWindowSize(window);
			var sizeFB	= glfw.GetFramebufferSize(window);
			this.ratio	= sizeFB.width / sizeWin.width;
			this.width	= this.drawingBufferWidth = sizeFB.width;
			this.height = this.drawingBufferHeight = sizeFB.height;
		},
		
		
		getContext() { return webgl; },
		
		
		on(name, callback) { this.addEventListener(name,callback); },
		
		
		addEventListener(name, callback) {
			if (callback && typeof(callback) === 'function') {
				if(name === 'resize') {
					name = 'framebuffer_resize';
					const tmpcb = callback;
					const self  = callback.this;
					callback = (evt) => {
						platform.width  = evt.width;
						platform.height = evt.height;
						tmpcb.call(self,evt);
					}
				}
				else if(name === 'mousemove' || name === 'mousedown' || name === 'mouseup') {
					const tmpcb = callback;
					const self  = callback.this;
					callback = (evt) => {
						evt.x *= platform.ratio;
						evt.y *= platform.ratio;
						tmpcb.call(self,evt);
					}
				}
				glfw.events.on(name, callback);
			}
		},
		removeEventListener(name, callback) {
			if (callback && typeof(callback) === 'function') {
				if(name === 'resize') {
					name = 'framebuffer_resize';
				}
				glfw.events.removeListener(name, callback);
			}
		},
		requestAnimationFrame(callback, delay) {
			glfw.SwapBuffers(window);
			glfw.PollEvents();
			
			var timer = setImmediate;//process.nextTick;
			var d = 16;
			if (delay == undefined || delay > 0) {
				timer = setTimeout;
				d = delay;
			}
			timer(() => callback(glfw.GetTime()*1000.0), d);
		}
	};
	
	Object.defineProperty(platform, 'onkeydown', {
		set(cb) { this.on('keydown', cb); }
	});
	
	Object.defineProperty(platform, 'onkeyup', {
		set(cb) { this.on('keyup', cb); }
	});
	
	return platform;
	
};

