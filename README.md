# WebGL for Node.js

This is a part of [Node3D](https://github.com/node-3d) project.

[![NPM](https://badge.fury.io/js/webgl-raub.svg)](https://badge.fury.io/js/webgl-raub)
[![ESLint](https://github.com/node-3d/webgl-raub/actions/workflows/eslint.yml/badge.svg)](https://github.com/node-3d/webgl-raub/actions/workflows/eslint.yml)
[![Test](https://github.com/node-3d/webgl-raub/actions/workflows/test.yml/badge.svg)](https://github.com/node-3d/webgl-raub/actions/workflows/test.yml)
[![Cpplint](https://github.com/node-3d/webgl-raub/actions/workflows/cpplint.yml/badge.svg)](https://github.com/node-3d/webgl-raub/actions/workflows/cpplint.yml)

```console
npm i -s webgl-raub
```

> This addon is ABI-compatible across Node.js versions. **There is no compilation** during the `npm install`.

![Example](examples/screenshot.jpg)

**TL;DR**: For a quick start, use [3d-core-raub](https://github.com/node-3d/3d-core-raub)
or look at [Examples](/examples).

```js
import webgl from 'webgl-raub';
```

Here `webgl` contains the **WebGL/OpenGL** API, like a `WebGLRenderingContext` instance would.
* See [WebGLRenderingContext docs](https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext)
    for reference.
* See [TS declarations](/index.d.ts) for the full list of exports.
* There are also non-WebGL methods exported in case you want to use advanced OpenGL functions.
* The addon **does not provide** a window control system, you can use
    [glfw-raub](https://github.com/node-3d/glfw-raub) (or anything else!) to create a window.

The JS API mostly maps the native OpenGL function calls. E.g.:

```cpp
// gl.clear(target)
DBG_EXPORT JS_METHOD(clear) { NAPI_ENV;
	REQ_INT32_ARG(0, target);
	glClear(target);
	RET_WEBGL_VOID;
}
```

You can optionally call `webgl.init()` after the GL context becomes available - this translates
into a `glewInit()` call. See [GLEW docs](https://glew.sourceforge.net/basic.html) for what
it does and if you need it (probably "yes"?).

To use browser **WebGL** libs, like [three.js](https://threejs.org/),
several additional interfaces must also be provided to mimic the browser.

* Package [glfw-raub](https://github.com/node-3d/glfw-raub) provides window/context handling
and additional browser-like interfaces.
* Package [image-raub](https://github.com/node-3d/glfw-raub) loads and serves the image data as web
[Image](https://developer.mozilla.org/en-US/docs/Web/API/HTMLImageElement#example) would.

See [this example](/examples/textured.mjs) using both **GLFW** and **Image**.
The main idea being as follows:

```js
import Image from 'image-raub';
import webgl from 'webgl-raub';
import glfw from 'glfw-raub';
const { Document } = glfw;

Document.setImage(image); // plug Image impl into the Document
Document.setWebgl(webgl); // plug WebGL impl into the Document

const doc = new Document({ width: 1600, height: 900, vsync: true });
...
```

Similarly, these modules are utilized in [3d-core-raub](https://github.com/node-3d/3d-core-raub).
Using [3d-core-raub](https://github.com/node-3d/3d-core-raub), you can skip setting up
most environment features for those libs.


## WebGL Libs

* [three.js](https://threejs.org/) - known to work well on **Node.js** with this
implementation of **WebGL**.
* [PixiJS](https://pixijs.com/) - seems to work with some minor hacks, as proven by this
[example](https://github.com/node-3d/3d-core-raub/blob/master/examples/pixi/index.js).


## MacOS Note

Some features may depend on OpenGL profile being used. Core profile
is necessary for VAO and other OpenGL 3.2+ features. Depending on your windowing
backend, set the OpenGL profile of your preference.
In case [glfw-raub](https://github.com/node-3d/glfw-raub) is used,
the profile can be set through the `Window`/`Document`
[constructor](https://github.com/node-3d/glfw-raub#class-window) or with
`glfw.windowHint` calls.
