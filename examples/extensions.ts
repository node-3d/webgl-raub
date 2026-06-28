import { Document } from '@node-3d/glfw';

import { webgl as gl } from '@node-3d/webgl';


Document.setWebgl(gl);
// oxlint-disable-next-line no-unused-vars
const doc = new Document();

console.log('----- WebGL -----');
console.log(gl.getSupportedExtensions().toSorted().join('\n'));
console.log('----- NATIVE -----');
console.log(gl.getGLExtensions().toSorted().join('\n'));




