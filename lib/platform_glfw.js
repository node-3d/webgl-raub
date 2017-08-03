'use strict';

const glfw  = require('node-glfw-raub');
const webgl = require('./webgl');
const Img   = require('./image');


module.exports = function () {
	
	if (process.platform !== 'win32') {
		process.on('SIGINT', function () { process.exit(0); });
	}
	
	let window = null;
	
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
		
		get glfwWindow() { return window; },
		
		get pos() {
			const glfwPos = glfw.GetWindowPos(window)
			return { x: glfwPos.xpos, y: glfwPos.ypos };
		},
		
		set pos(p) {
			return glfw.SetWindowPos(window, p.x, p.y);
		},
		
		setIcon() { },
		
		_width  : 800,
		_height : 600,
		
		get clientWidth() { return this._width;  },
		set clientWidth(v) { this._width = v;  },
		get clientHeight() { return this._height; },
		set clientHeight(v) { this._height = v; },
		get width() { return this._width;  },
		set width(v) { this._width = v;  },
		get height() { return this._height; },
		set height(v) { this._height = v; },
			
		style: {
			get width() { return platform._width;  },
			set width(v) { platform._width = parseInt(v);  },
			get height() { return platform._height; },
			set height(v) { platform._height = parseInt(v); },
		},
		
		flip() {
			glfw.SwapBuffers(window);
		},
		
		
		getElementById(name) {
			return this.createElement(name);
		},
		
		
		createElement(name, width, height) {
			
			name = name.toLowerCase();
			
			if (name.indexOf('canvas') >= 0) {
				
				this._width  = width  || this._width;
				this._height = height || this._height;
				
				this.createWindow(this._width, this._height);
				
				this.canvas  = this;
				webgl.canvas = this;
				return this;
				
			} else if (name.indexOf('img') >= 0) {
				
				const img = new Img();
				img.addEventListener = img.on;
				return img;
				
			}
			
			return null;
			
		},
		
		
		createElementNS(junk, name) { return this.createElement(name); },
		
		
		createWindow(width, height) {
			let attribs = glfw.WINDOW;
			
			if (width == 0 || height == 0) {
				attribs = glfw.FULLSCREEN;
				width = height = 0;
			}
			
			const resizeListeners = [];
			const rl = glfw.events.listeners('framebuffer_resize');
			for (let l = 0, ln = rl.length; l < ln; ++l) {
				resizeListeners[l] = rl[l];
			}
			
			glfw.events.removeAllListeners('framebuffer_resize');
			
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
				throw 'Can\'t initialize GL surface';
			}
			
			glfw.MakeContextCurrent(window);
			
			glfw.SetWindowTitle('WebGL');
			
			// make sure GLEW is initialized
			webgl.Init();
			
			glfw.SwapBuffers(window);
			glfw.SwapInterval(0); // Disable VSync (we want to get as high FPS as possible!)
			
			for (let l = 0, ln = resizeListeners.length; l < ln; ++l) {
				glfw.events.addListener('framebuffer_resize', resizeListeners[l]);
			}
			
			const sizeWin = glfw.GetWindowSize(window);
			const sizeFB  = glfw.GetFramebufferSize(window);
			this.ratio  = sizeFB.width / sizeWin.width;
			this.width  = this.drawingBufferWidth = sizeFB.width;
			this.height = this.drawingBufferHeight = sizeFB.height;
			
		},
		
		
		getContext() { return webgl; },
		
		
		on(name, callback) { this.addEventListener(name,callback); },
		
		
		dispatchEvent: function (event) {
			glfw.events.emit(event.type, event);
		},
		
		
		addEventListener(name, callback) {
			if (callback && typeof(callback) === 'function') {
				if(name === 'resize') {
					name = 'framebuffer_resize';
					const tmpcb = callback;
					const self  = callback.this;
					callback = (evt) => {
						platform._width  = evt.width;
						platform._height = evt.height;
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
		
		
		requestAnimationFrame(cb) {
			glfw.SwapBuffers(window);
			glfw.PollEvents();
			setImmediate(() => cb(Date.now()));
		},
		
	};
	
	Object.defineProperty(platform, 'onkeydown', {
		set(cb) { this.on('keydown', cb); }
	});
	
	Object.defineProperty(platform, 'onkeyup', {
		set(cb) { this.on('keyup', cb); }
	});
	
	global.HTMLImageElement  = Img;
	global.HTMLCanvasElement = platform.constructor;
	
	return platform;
	
};
