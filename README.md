# WebGL for Node.js

WebGL crossplatform addon with minimized dependencies.


## Install

```
npm i -s webgl-raub
```

Note: as this is a compiled addon, compilation tools must be in place on your system.
Such as MSVS13 for Windows, where **ADMIN PRIVELEGED** `npm i -g windows-build-tools` most probably helps.


## Usage

This is an implementation of WebGL for Node.js.

```js
const webgl = require('webgl-raub');
```

Here `webgl` is what contains all the WebGL api - `WebGLRenderingContext`.
However a window is required to exercise your GL skills on. There is
[a nice implementation](https://github.com/raub/node-glfw) for that,
though different ones are quite possible.

As soon as you create and set up a window, simply follow the
[WebGLRenderingContext docs](https://developer.mozilla.org/en-US/docs/Web/API/WebGLRenderingContext).

NOTE: If you are planning to use browser WebGL libs, be aware of their browser-affinity.
You would have to provide several additional interfaces to mimic the browser.
There is [node-glfw](https://github.com/raub/node-glfw) module, which exports the
`Document` class. It can be used the following way:

```
const webgl = require('webgl-raub');
const { Document } = require('glfw-raub');

Document.setWebgl(webgl); // plug this WebGL impl into the Document

const doc = new Document();
global.document = global.window = doc;

const canvas = document.createElement('canvas'); // === doc
const gl = canvas.getContext('webgl'); // === webgl
```


---

## Three.js

Being a low level interface, WebGL requires a lot of effort to build apps. For
that matter there are numerous frameworks around it. One of them is
[three.js](https://threejs.org/). It is known to work well on Node.js with this
implementation of WebGL.


You can try to use three.js your own way, but there is
a far better option: [node-3d-core](https://github.com/raub/node-3d-core),
which gets you two more steps ahead for free.
