var nodejs = (typeof window === 'undefined');
if (nodejs) {
  WebGL = require('../../index');
  Image = WebGL.Image;
  document = WebGL.document();
  alert = log = console.log;
}

document.setTitle("ShaderToy");
requestAnimationFrame = document.requestAnimationFrame;

var vsSource = [ 
                "attribute vec2 pos;", 
                "void main() {",
                "  gl_Position = vec4(pos.x,pos.y,0.0,1.0);", 
                "}" ].join("\n");

var fsSource = [ 
                "void main() {", 
                "  gl_FragColor = vec4(0.0,0.0,0.0,1.0);",
                "}" ].join("\n");

function createGLTexture(ctx, image, texture) {
  ctx.enable(ctx.TEXTURE_2D);
  ctx.bindTexture(ctx.TEXTURE_2D, texture);
  ctx.texImage2D(ctx.TEXTURE_2D, 0, ctx.RGBA, ctx.RGBA, ctx.UNSIGNED_BYTE,
      image);
  ctx.texParameteri(ctx.TEXTURE_2D, ctx.TEXTURE_MAG_FILTER, ctx.LINEAR);
  ctx.texParameteri(ctx.TEXTURE_2D, ctx.TEXTURE_MIN_FILTER,
      ctx.LINEAR_MIPMAP_LINEAR);
  ctx.texParameteri(ctx.TEXTURE_2D, ctx.TEXTURE_WRAP_S, ctx.REPEAT);
  ctx.texParameteri(ctx.TEXTURE_2D, ctx.TEXTURE_WRAP_T, ctx.REPEAT);
  ctx.generateMipmap(ctx.TEXTURE_2D)
  ctx.bindTexture(ctx.TEXTURE_2D, null);
}
function loadImageTexture(gl, url) {
  var texture = gl.createTexture();
  texture.image = new Image();
  texture.image.crossOrigin = '';
  texture.image.onload = function() {
    createGLTexture(gl, texture.image, texture)
  }
  texture.image.src = url;
  return texture;
}

function Effect(gl, xres, yres) {
  this.mGLContext = gl;
  this.mQuadVBO = null;
  this.mProgram = null;
  this.mXres = xres;
  this.mYres = yres;
  this.mTexture0 = null;
  this.mTexture1 = null;
  this.mTexture2 = null;
  this.mTexture3 = null;

  var vertices = new Float32Array([ 
                                    -1., -1., 1., 
                                    -1., -1., 1., 
                                    1., -1., 1.,
                                    1., -1., 1. ]);

  //--------------------------------------

  this.mQuadVBO = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, this.mQuadVBO);
  gl.bufferData(gl.ARRAY_BUFFER, vertices, gl.STATIC_DRAW);

  var res = this.NewShader(fsSource);
}

Effect.prototype.NewShader = function(shaderCode) {
  var gl = this.mGLContext;

  var tmpProgram = gl.createProgram();

  var vs = gl.createShader(gl.VERTEX_SHADER);
  var fs = gl.createShader(gl.FRAGMENT_SHADER);

  gl.shaderSource(vs, vsSource);
  gl.shaderSource(fs, shaderCode);

  gl.compileShader(vs);
  gl.compileShader(fs);

  //-------------
  if (!gl.getShaderParameter(vs, gl.COMPILE_STATUS)) {
    var infoLog = gl.getShaderInfoLog(vs);
    gl.deleteProgram(tmpProgram);
    return "VS ERROR: " + infoLog;
    ;
  }

  if (!gl.getShaderParameter(fs, gl.COMPILE_STATUS)) {
    var infoLog = gl.getShaderInfoLog(fs);
    gl.deleteProgram(tmpProgram);
    return "FS ERROR: " + infoLog;
  }

  //-------------

  gl.attachShader(tmpProgram, vs);
  gl.attachShader(tmpProgram, fs);

  gl.deleteShader(vs);
  gl.deleteShader(fs);

  gl.linkProgram(tmpProgram);

  if (this.mProgram != null)
    gl.deleteProgram(this.mProgram);

  this.mProgram = tmpProgram;

  log("Shader compiled successfully");
}

Effect.prototype.NewTexture = function(slot, txt) {
  var gl = this.mGLContext;

  var tmpTexture = (txt == "") ? null : loadImageTexture(gl, txt);

  if (slot == 0) {
    if (this.mTexture0 != null)
      gl.deleteTexture(this.mTexture0);
    this.mTexture0 = tmpTexture;
  }
  if (slot == 1) {
    if (this.mTexture1 != null)
      gl.deleteTexture(this.mTexture1);
    this.mTexture1 = tmpTexture;
  }
  if (slot == 2) {
    if (this.mTexture2 != null)
      gl.deleteTexture(this.mTexture2);
    this.mTexture2 = tmpTexture;
  }
  if (slot == 3) {
    if (this.mTexture3 != null)
      gl.deleteTexture(this.mTexture3);
    this.mTexture3 = tmpTexture;
  }
}

Effect.prototype.Paint = function(time, mouseOriX, mouseOriY, mousePosX,
    mousePosY) {

  var gl = this.mGLContext;

  gl.viewport(0, 0, this.mXres, this.mYres);

  gl.useProgram(this.mProgram);

  var l1 = gl.getAttribLocation(this.mProgram, "pos");
  var l2 = gl.getUniformLocation(this.mProgram, "time");
  var l3 = gl.getUniformLocation(this.mProgram, "resolution");
  var l4 = gl.getUniformLocation(this.mProgram, "mouse");

  var t0 = gl.getUniformLocation(this.mProgram, "tex0");
  var t1 = gl.getUniformLocation(this.mProgram, "tex1");

  gl.bindBuffer(gl.ARRAY_BUFFER, this.mQuadVBO);
  if (l2 != null)
    gl.uniform1f(l2, time);
  if (l3 != null)
    gl.uniform2f(l3, this.mXres, this.mYres);
  if (l4 != null)
    gl.uniform4f(l4, mousePosX, this.mYres - 1 - mousePosY, mouseOriX,
        this.Yres - 1 - mouseOriY);

  gl.vertexAttribPointer(l1, 2, gl.FLOAT, false, 0, 0);

  gl.enableVertexAttribArray(l1);

  if (t0 != null) {
    gl.uniform1i(t0, 0);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, this.mTexture0);
  }
  if (t1 != null) {
    gl.uniform1i(t1, 1);
    gl.activeTexture(gl.TEXTURE1);
    gl.bindTexture(gl.TEXTURE_2D, this.mTexture1);
  }

  gl.drawArrays(gl.TRIANGLES, 0, 6);
  gl.disableVertexAttribArray(l1);
}

Effect.prototype.SetSize = function(xres, yres) {
  this.mXres = xres;
  this.mYres = yres;
}

var mCanvas, mGLContext, mEffect;
var startTime=-1;
var mMouseOriX=-1, mMouseOriY=-1, mMousePosX=-1, mMousePosY=-1;

function initGL() {
  mCanvas = document.createElement("canvas",512,512);
  try {
    mGLContext = mCanvas.getContext("experimental-webgl");
  } catch (e) {
    alert("This demo requires a WebGL-enabled browser.");
    return false;
  }

  mEffect = new Effect(mGLContext, mCanvas.width, mCanvas.height);

  return true;
}

function render(t) {
  if(startTime==-1 && t!=undefined)
    startTime=t;
  var time = t - startTime;
  
  mEffect.Paint(time/1000.0, mMouseOriX, mMouseOriY, mMousePosX, mMousePosY);
  mGLContext.flush();
  requestAnimationFrame(render,0);
}

if(initGL()) {
  document.on("resize",function(evt){
    //console.log('resize to: ('+evt.width+", "+evt.height+")");
    mGLContext.viewportWidth=evt.width;
    mGLContext.viewportHeight=evt.height;
    mEffect.SetSize(evt.width,evt.height);
  });
  document.on("mousedown", function(ev) {
    mMouseOriX = ev.x;
    mMouseOriY = ev.y;
  });
  document.on("mousemove", function(ev) {
    if (mMouseOriX > 0) {
      mMousePosX = ev.pageX;
      mMousePosY = ev.pageY;
    }
  });
  document.on("mouseup", function(ev) {
    mMouseOriX = -1;
    mMouseOriY = -1;
  });

  var presets=__dirname+ '/presets/';
  //mEffect.NewShader(require('fs').readFileSync(presets+ 'deform.fs','utf8'));
  //mEffect.NewTexture(0, presets+ 'tex3.jpg')

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'water.fs','utf8'));
  //mEffect.NewTexture(0, presets+ 'tex0.jpg')

  mEffect.NewShader(require('fs').readFileSync(presets+ 'mandelbulb.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'landscape.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'clod.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'droid.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'slisesix.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'square_tunnel.fs','utf8'));
  //mEffect.NewTexture(0, presets+ 'tex0.jpg')

  //mEffect.NewShader(require('fs').readFileSync(presets+ '704.fs','utf8'));
  
  //mEffect.NewShader(require('fs').readFileSync(presets+ 'earth.fs','utf8'));
  //mEffect.NewTexture(0, presets+ 'earth_day.jpg')
  
  //mEffect.NewShader(require('fs').readFileSync(presets+ 'sult.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'kinderpainter.fs','utf8'));
  //mEffect.NewTexture(0, presets+ 'tex0.jpg')

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'red.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'quaternion.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'lunaquatic.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'metatunnel.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'leizex.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'mandel.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'julia.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'shapes.fs','utf8'));

  //mEffect.NewShader(require('fs').readFileSync(presets+ 'apple.fs','utf8'));
  
  render();
}
  
