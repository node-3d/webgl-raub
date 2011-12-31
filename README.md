This is a port of WebGL for desktops: windows, linux, mac

This is an extension of creationix/node-webgl and their great example com.creationix.minimason that you can find in examples/wavefront.js.

Linux
============
- node-sdl
This requires SDL to be installed in your system: 
sudo apt-get install libsdl-dev libghc-sdl-ttf-dev libsdl-image1.2-dev
download and install my SDL module (mikeseven/sdl)

- freeimage
sudo apt-get install libfreeimage-dev

Notes: tested on Ubuntu 11.10 x64.

MAC OSX
=======
- download and install: SDL-1.2.14 (not 1.3.x), SDL_image, SDL_ttf. They should reside in /usr/local/ by default.
- make sure sdl-config is in your PATH and verify 'sdl-config --version' returns 1.2.14.
- download and install freeimage.
- add to your environment: export SDL_VIDEODRIVER=x11
- build and install my SDL module (mikeseven/sdl)
- verify it works e.g. node examples/img.js
- now you can install this module

Notes: tested on MAC OSX 10.6 x64. Some constants are not supported, see src/bindings.cc, lookfor __APPLE__.

Installation
============
node-waf configure build

Usage
=====
examples/   contains examples from other the web
test/       contains lessons from www.learningwebgl.com and other tests

simply type: node test/lesson02.js

Enjoy!

Limitations
===========
WebGL is based on OpenGL ES, a restriction of OpenGL found on desktops, for embedded systems.
Because this module wraps OpenGL, it is possible to do things that may not work on web browsers. 
Please read http://www.khronos.org/webgl/wiki_1_15/index.php/WebGL_and_OpenGL_Differences 
to learn about the differences.

- define nodejs = true
on top of your script in case you need to write some specific calls (e.g. IO) a-la nodeJS.

Look at test/lesson02.js (or any other examples/tests), method getShader(gl, id) uses this variable to distinguish between loading shader scripts from arrays or using DOM document tags.
While these examples use arrays for shaders, you can also use require('fs').readFileSync(filename, 'ascii'). 

- shaders
Remember to add this on top of your fragment shaders:
<pre>
#ifdef GL_ES
precision highp float;
#endif
</pre>

- loading external scripts
If your code uses external libraries, you can load them like this. No code change to external scripts ;-)
<pre>
fs=require('fs');
eval(fs.readFileSync(__dirname+ '/glMatrix-0.9.5.min.js','utf8'));
</pre>

- frame rate
requestAnimationFrame(callback [, delay]) works as in the browser. 
If delay is specified, it is the requested delay in milliseconds between animation frames 
e.g. 16 will provide 1000 / 16 = 62 fps at best, which is the default value if delay is undefined. 
If delay = 0, then the fastest possible framerate on your machine is used.
