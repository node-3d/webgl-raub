import { Document } from '@node-3d/glfw';

import { webgl as gl } from '@node-3d/webgl';


Document.setWebgl(gl);
// oxlint-disable-next-line no-unused-vars
const doc = new Document();

console.log(`
OpenGL
	vendor    : ${gl.getParameter(gl.VENDOR)}
	version   : ${gl.getParameter(gl.VERSION)}
	glsl      : ${gl.getParameter(gl.SHADING_LANGUAGE_VERSION)}
	renderer  : ${gl.getParameter(gl.RENDERER)}
	extensions: ${gl.getSupportedExtensions().length}
`);




