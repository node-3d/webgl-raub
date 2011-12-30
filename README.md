This is a port of WebGL for desktops: windows, linux, mac

This is an extension of creationix/node-webgl and their great example com.creationix.minimason that you can find in examples/wavefront.js.

Dependencies
============
- node-sdl
This requires SDL to be installed in your system: 
sudo apt-get install libsdl-dev libghc-sdl-ttf-dev libsdl-image1.2-dev
npm install -g sdl

- freeimage
sudo apt-get install libfreeimage-dev

Installation
============
node-waf configure build

Usage
=====
examples/   contains examples from other the web
test/       contains lessons from learningwebgl.com and other tests

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
