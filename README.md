# WebGL for Node.js

WebGL crossplatform addon with minimized dependencies.


## Install

```
npm i -s node-webgl-raub
```

Note: as this is a compiled addon, compilation tools must be in place on your system.
Such as MSVS13 for Windows, where `npm install --global windows-build-tools` most probably helps.


## Use

This module tries to implement the whole required layer of features to run WebGL as if
in a browser. As of now, those are 3: WebGL itself, Image and document.

```js
const { Document, Image, webgl } = require('node-webgl-raub');
```

Here `webgl` is what contains all the WebGL api. However a window is required to
exercise your GL skills on. Then we have `Document` which spawns a new system
window, while also mimicking WEB `document`, `window`, and `canvas`. So this is what
happens:

```
const doc = new Document();
global.document = global.window = doc;
const canvas = document.createElement('canvas'); // === doc
const gl = canvas.getContext('webgl'); // === webgl
```

It allows mimicking browser interfaces to a degree where the majority of WebGL code
works after copy-pasting from a browser environment. If some interfaces are missing,
please do report.

---

`Image` is used to load textures. Consider the following example:

```js
const texture = gl.createTexture();

const image = new Image();

image.onload = () => {
	gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	gl.bindTexture(gl.TEXTURE_2D, texture);
	gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, image);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);
	gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR_MIPMAP_NEAREST);
	gl.generateMipmap(gl.TEXTURE_2D);
	gl.bindTexture(gl.TEXTURE_2D, null);
};

image.src = `${__dirname}/texture.jpg`;
```


## Three.js

Being a low level interface, WebGL requires a lot of effort to build apps. For
that matter there are numerous frameworks around it. One of them is
[three.js](https://threejs.org/). It is known to work well on Node.js with this
implementation of WebGL. You can try to use three.js your own way, but there is
a far better option: [node-3d-ready-raub](https://github.com/raub/node-3d-ready),
which gets you two more steps ahead for free.
