export const cubeFaceColors = [
	[ 1.0, 1.0, 1.0, 0.5 ], // Front face: white
	[ 1.0, 0.0, 0.0, 0.5 ], // Back face: red
	[ 0.0, 1.0, 0.0, 0.5 ], // Top face: green
	[ 0.0, 0.0, 1.0, 0.5 ], // Bottom face: blue
	[ 1.0, 1.0, 0.0, 0.5 ], // Right face: yellow
	[ 1.0, 0.0, 1.0, 0.5 ] // Left face: purple
];

// Repeat each color 4 times. Convert all to flat array.
export const cubeColors = cubeFaceColors.map((c) => [c, c, c, c]).flatMap((c) => c).flatMap((c) => c);

export const cubeVertices = [
	// Front face
	-1.0, -1.0, 1.0,
	1.0, -1.0, 1.0,
	1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0,
	
	// Back face
	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, -1.0, -1.0,
	
	// Top face
	-1.0, 1.0, -1.0,
	-1.0, 1.0, 1.0,
	1.0, 1.0, 1.0,
	1.0, 1.0, -1.0,
	
	// Bottom face
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0, 1.0,
	-1.0, -1.0, 1.0,
	
	// Right face
	1.0, -1.0, -1.0,
	1.0, 1.0, -1.0,
	1.0, 1.0, 1.0,
	1.0, -1.0, 1.0,
	
	// Left face
	-1.0, -1.0, -1.0,
	-1.0, -1.0, 1.0,
	-1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0
];

export const cubeVertexIndices = [
	0, 1, 2, 0, 2, 3, // Front face
	4, 5, 6, 4, 6, 7, // Back face
	8, 9, 10, 8, 10, 11, // Top face
	12, 13, 14, 12, 14, 15, // Bottom face
	16, 17, 18, 16, 18, 19, // Right face
	20, 21, 22, 20, 22, 23 // Left face
];


export const cubeTexCoords = [
	// Front face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	
	// Back face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	
	// Top face
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	
	// Bottom face
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	1.0, 0.0,
	
	// Right face
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
	0.0, 0.0,
	
	// Left face
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0,
];

export const cubeVertexNormals = [
	// Front face
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	
	// Back face
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	0.0, 0.0, -1.0,
	
	// Top face
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	
	// Bottom face
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	0.0, -1.0, 0.0,
	
	// Right face
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	
	// Left face
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0,
	-1.0, 0.0, 0.0
];

export const vertsTri = [
	0.0, 1.0, 0.0,
	-1.0, -1.0, 0.0,
	1.0, -1.0, 0.0
];

export const colorsTri = [
	1.0, 0.0, 0.0, 1.0,
	0.0, 1.0, 0.0, 1.0,
	0.0, 0.0, 1.0, 1.0
];

export const vertsQuad = [
	1.0, 1.0, 0.0,
	-1.0, 1.0, 0.0,
	1.0, -1.0, 0.0,
	-1.0, -1.0, 0.0
];


export const shapeShaders = {
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec4 aVertexColor;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		varying vec4 vColor;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vColor = aVertexColor;
		}
	`,
	fs : `
		#ifdef GL_ES
			precision mediump float;
		#endif
		varying vec4 vColor;
		void main(void) {
			gl_FragColor = vColor;
		}
	`,
};

export const texturedShaders = {
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec2 aTextureCoord;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		varying vec2 vTextureCoord;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vTextureCoord = aTextureCoord;
		}
	`,
	fs : `
		#ifdef GL_ES
			precision mediump float;
		#endif
		varying vec2 vTextureCoord;
		uniform sampler2D uSampler;
		void main(void) {
			gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
		}
	`,
};

export const transparentShaders = {
	fs: `
		#ifdef GL_ES
		  precision mediump float;
		#endif
		varying vec2 vTextureCoord;
		varying vec3 vLightWeighting;
		uniform float uAlpha;
		uniform sampler2D uSampler;
		void main(void) {
			vec4 textureColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
			gl_FragColor = vec4(textureColor.rgb * vLightWeighting, textureColor.a * uAlpha);
		}
	`,
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec3 aVertexNormal;
		attribute vec2 aTextureCoord;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		uniform mat3 uNMatrix;
		uniform vec3 uAmbientColor;
		uniform vec3 uLightingDirection;
		uniform vec3 uDirectionalColor;
		uniform bool uUseLighting;
		varying vec2 vTextureCoord;
		varying vec3 vLightWeighting;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vTextureCoord = aTextureCoord;
			if (!uUseLighting) {
				vLightWeighting = vec3(1.0, 1.0, 1.0);
			} else {
				vec3 transformedNormal = uNMatrix * aVertexNormal;
				float directionalLightWeighting = max(dot(transformedNormal, uLightingDirection), 0.0);
				vLightWeighting = uAmbientColor + uDirectionalColor * directionalLightWeighting;
			}
		}
	`,
};

export const alignedShaders = {
	fs: `
		#ifdef GL_ES
			precision mediump float;
		#endif
		varying vec2 vTextureCoord;
		uniform sampler2D uSampler;
		void main(void) {
			gl_FragColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));
		}
	`,
	vs: `
		attribute vec3 aVertexPosition;
		attribute vec2 aTextureCoord;
		uniform mat4 uMVMatrix;
		uniform mat4 uPMatrix;
		varying vec2 vTextureCoord;
		void main(void) {
			gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);
			vTextureCoord = aTextureCoord;
		}
	`,
};
