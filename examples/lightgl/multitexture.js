var nodejs = (typeof window === 'undefined');
if(nodejs) {
  WebGL = require('../../index');
  Image = WebGL.Image;
  document = WebGL.document();
  alert=console.log;
  window = document;

  //Read and eval library
  var fs=require('fs');
  eval(fs.readFileSync(__dirname+ '/lightgl.js','utf8'));
}

document.setTitle("Multitexture");
requestAnimationFrame = document.requestAnimationFrame;

var angle = 0;
var gl = GL.create();
var mesh = GL.Mesh.plane({ coords: true });
var texture = GL.Texture.fromURL(__dirname+'/'+'texture.png');
var texture2 = GL.Texture.fromURL(__dirname+'/'+'texture2.png');
var shader = new GL.Shader('\
  varying vec2 coord;\
  void main() {\
    coord = gl_TexCoord.xy;\
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;\
  }\
', '\
  uniform sampler2D texture;\
  uniform sampler2D texture2;\
  varying vec2 coord;\
  void main() {\
    gl_FragColor = texture2D(texture, coord) - texture2D(texture2, coord);\
  }\
');

gl.onupdate = function(seconds) {
  angle += 45 * seconds;
};

gl.ondraw = function() {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
  gl.loadIdentity();
  gl.translate(0, 0, -5);
  gl.rotate(30, 1, 0, 0);
  gl.rotate(angle, 0, 1, 0);

  texture.bind(0);
  texture2.bind(1);
  shader.uniforms({
    texture: 0,
    texture2: 1
  }).draw(mesh);
};

gl.fullscreen();
gl.animate();
