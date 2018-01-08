'use strict';

const glfw  = require('node-glfw-raub');
const { Window } = glfw;

const webgl = require('./webgl');
const Img   = require('./image');


const ESC_KEY = 27;


class Document extends glfw.Window {
	
	constructor(opts = {}) {
		
		super(opts);
		
		if ( ! opts.ignoreQuit ) {
			
			if (process.platform !== 'win32') {
				process.on('SIGINT', () => process.exit(0));
			}
			
			this.on('quit', () => process.exit(0));
			this.on('keydown', e => e.keyCode === ESC_KEY && process.exit(0));
			
		}
		
		// Make sure GLEW is initialized
		webgl.Init();
		
		this.swapBuffers();
		
		const sizeWin = this.size;
		const sizeFB  = this.framebufferSize;
		
		this._ratio  = sizeFB.width / sizeWin.width;
		
		this.requestAnimationFrame = this._requestAnimationFrame.bind(this);
		
	}
	
	
	get context() { return webgl; }
	
	get body() { return this; }
	
	get ratio() { return this._ratio; }
	get devicePixelRatio() { return this._ratio; }
	
	get innerWidth() { return this._width; }
	set innerWidth(v) { this._width = v; }
	get innerHeight() { return this._height; }
	set innerHeight(v) { this._height = v; }
	
	get clientWidth() { return this._width; }
	set clientWidth(v) { this._width = v; }
	get clientHeight() { return this._height; }
	set clientHeight(v) { this._height = v; }
	
	get width() { return this._width; }
	set width(v) { this._width = v; }
	get height() { return this._height; }
	set height(v) { this._height = v; }
	
	set onkeydown(cb) { this.on('keydown', cb); }
	set onkeyup(cb) { this.on('keyup', cb); }
	
	get style() {
		const that = this;
		return {
			get width() { return that.width; },
			set width(v) { that.width = parseInt(v); },
			get height() { return that.height; },
			set height(v) { that.height = parseInt(v); },
		};
	}
	
	
	getContext() { return webgl }
	
	getElementById() { return null; }
	
	getElementsByTagName(tag) { return tag === 'canvas' ? this : null; }
	
	
	createElementNS(_0, name) { return this.createElement(name); }
	
	createElement(name, width, height) {
		
		name = name.toLowerCase();
		
		if (name.indexOf('canvas') >= 0) {
			
			return this;
			
		} else if (name.indexOf('img') >= 0) {
			
			const img = new Img();
			img.addEventListener = img.on;
			return img;
			
		}
		
		return null;
		
	}
	
	
	dispatchEvent(event) { this.emit(event.type, event); }
	
	addEventListener(name, callback) { this.on(name, callback); }
	
	removeEventListener(name, callback) { this.removeListener(name, callback); }
	
	
	_requestAnimationFrame(cb) {
		this.swapBuffers();
		glfw.PollEvents();
		setImmediate(() => cb(Date.now()));
	}
	
};


global.HTMLImageElement = Img;
global.HTMLCanvasElement = Document;


module.exports = Document;
