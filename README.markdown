This is a port of WebGL for desktops: windows, linux, mac

This is an extension of creationix/node-webgl and their great example com.creationix.minimason.

Dependencies
============
- node-sdl
This requires SDL to be installed in your system: 
sudo apt-get install libsdl-dev libghc-sdl-ttf-dev libsdl-image1.2-dev
npm install -g sdl

Installation
============
npm install -g node-webgl

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

Remember to add this on top of your fragment shaders:
```C
#ifdef GL_ES
precision highp float;
#endif
```