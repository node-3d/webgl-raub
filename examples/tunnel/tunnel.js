//
// Ported from http://www.rozengain.com/blog/2010/08/10/using-webgl-glsl-shaders-to-create-a-tunnel-effect/
//

var nodejs = (typeof window === 'undefined');
if(nodejs) {
  WebGL = require('../../index');
  Image = WebGL.Image;
  document = WebGL.document();
  alert=console.log;

  //Read and eval library
  var fs=require('fs');
  eval(fs.readFileSync(__dirname+ '/sylvester.js','utf8'));
  eval(fs.readFileSync(__dirname+ '/glUtils.js','utf8'));
}

document.setTitle("Tunnel");
requestAnimationFrame = document.requestAnimationFrame;

var shaders= {
    "shader-fs" : 
      [     
       "#ifdef GL_ES",
       "precision highp float;",
       "#endif",
       "uniform sampler2D uSampler;",
       "varying vec4 vColor;",
       "varying vec2 vTextureCoord;",
       "void main(void) {",
       "  // -- get the pixel from the texture",
       "  vec4 textureColor = texture2D(uSampler, vec2(vTextureCoord.s, vTextureCoord.t));",
       "  // -- multiply the texture pixel with the vertex color",
       "  gl_FragColor = vColor * textureColor;",
       "}"
       ].join("\n"),

       "shader-vs" : 
         [ 
          "// -- 'attribute': read-only per-vertex data, available only within vertex shaders.",
          "// -- the vertex position (x, y, z)",
          "  attribute vec3 aVertexPosition;",
          "// -- the vertex color (r, g, b, a)",
          "  attribute vec4 aVertexColor;",
          "// -- the texture coordinate for this vertex (u, v)",
          "attribute vec2 aTextureCoord;",
          "// -- 'uniform': remains constant during each shader execution.",
          "// -- model-view matrix",
          "uniform mat4 uMVMatrix;",
          "// -- projection matrix",
          "uniform mat4 uPMatrix;",
          "// -- the time value (changes every frame)",
          "uniform float fTime;",
          "// -- 'varying': output of the vertex shader that corresponds to read-only interpolated input",
          "//    of the fragment shader",
          "// -- the color",
          "varying vec4 vColor;",
          "// -- the texture coordinates",
          "varying vec2 vTextureCoord;",
          "void main(void) {",
          "   vec3 pos=aVertexPosition; ",
          "  // -- displace the x coordinate based on the time and the z position ",
          "  pos.x += cos(fTime + (aVertexPosition.z/4.0)); ",
          "  // -- displace the y coordinate based on the time and the z position ",
          "  pos.y += sin(fTime + (aVertexPosition.z/4.0)); ",
          "  // -- transform the vertex ",
          "  gl_Position = uPMatrix * uMVMatrix * vec4(pos, 1.0); ",
          "  // -- copy the vertex color",
          "  vColor = aVertexColor; ",
          "  // -- displace the texture's y (v) coordinate. This gives the illusion of movement.",
          "  vec2 texcoord=aTextureCoord; ",
          "  texcoord.y = texcoord.y + (fTime); ",
          "  // -- copy the texture coordinate ",
          "  vTextureCoord = texcoord; ",
          "}"
          ].join("\n")
};

var vertices = [];
var indices = [];
var colors = [];
var uvs = [];

var radius = 7;
var currentRadius = radius;
var segments = 24;
var spacing = 2;
var numRings = 18;
var index=0;
var currentTime = 0;
var drawingMode;

function generateGeometry() {
  for(var ring=0; ring<numRings; ring++)
  {
    for(var segment=0; segment<segments; segment++)
    {
      var degrees = (360/segments) * segment;
      var radians = (Math.PI/180) * degrees;
      var x = Math.cos(radians) * currentRadius;
      var y = Math.sin(radians) * currentRadius;
      var z = ring * -spacing;

      vertices.push(x, y, z);
      if(segment < (segments-1)/ 2)
        uvs.push((1.0/(segments))*segment*2, (1.0/4)*ring);
      else
        uvs.push(2.0-((1.0/(segments))*segment*2), (1.0/4)*ring);
        
      var color = 1.0-((1.0/(numRings-1))*ring);
      colors.push(color, color, color, 1.0);

      if(ring<numRings-1) {
        if(segment < segments-1) {
          indices.push(index, index + segments + 1, index + segments);
          indices.push(index, index+1, index + segments + 1);
        } else {
          indices.push(index, index + 1, index + segments);
          indices.push(index, index - segments + 1, index + 1);
        }
      }

      index++;
    }
    currentRadius -= radius/numRings;
  }
};

generateGeometry();

var gl;

function initGL(canvas) {
  try {
    gl = canvas.getContext("experimental-webgl");
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;
  } catch (e) {
  }
  if (!gl) {
    alert("Could not initialise WebGL, sorry :-(");
  }
}


function getShader(gl, id) {
  var shader;
  if(nodejs) {
    if (!shaders.hasOwnProperty(id)) return null;
    var str = shaders[id];

    if (id.match(/-fs/)) {
      shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (id.match(/-vs/)) {
      shader = gl.createShader(gl.VERTEX_SHADER);
    } else { return null; }

  }
  else {
    var shaderScript = document.getElementById(id);
    if (!shaderScript) {
      return null;
    }

    var str = "";
    var k = shaderScript.firstChild;
    while (k) {
      if (k.nodeType == 3) {
        str += k.textContent;
      }
      k = k.nextSibling;
    }
    if (shaderScript.type == "x-shader/x-fragment") {
      shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (shaderScript.type == "x-shader/x-vertex") {
      shader = gl.createShader(gl.VERTEX_SHADER);
    } else {
      return null;
    }
  }

  gl.shaderSource(shader, str);
  gl.compileShader(shader);

  if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
    alert(gl.getShaderInfoLog(shader));
    return null;
  }

  return shader;
}

var shaderProgram;

function initShaders() {
  var fragmentShader = getShader(gl, "shader-fs");
  var vertexShader = getShader(gl, "shader-vs");

  shaderProgram = gl.createProgram();
  gl.attachShader(shaderProgram, vertexShader);
  gl.attachShader(shaderProgram, fragmentShader);
  gl.linkProgram(shaderProgram);

  if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
    alert("Could not initialise shaders");
  }

  gl.useProgram(shaderProgram);

  shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
  gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

  shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
  gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);

  shaderProgram.textureCoordAttribute = gl.getAttribLocation(shaderProgram, "aTextureCoord");
  gl.enableVertexAttribArray(shaderProgram.textureCoordAttribute);

  shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
  shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");
  shaderProgram.fTimeUniform = gl.getUniformLocation(shaderProgram, "fTime");
}


var mvMatrix;
var mvMatrixStack = [];

function mvPushMatrix(m) {
  if (m) {
    mvMatrixStack.push(m.dup());
    mvMatrix = m.dup();
  } else {
    mvMatrixStack.push(mvMatrix.dup());
  }
}

function mvPopMatrix() {
  if (mvMatrixStack.length == 0) {
    throw "Invalid popMatrix!";
  }
  mvMatrix = mvMatrixStack.pop();
  return mvMatrix;
}

function loadIdentity() {
  mvMatrix = Matrix.I(4);
}


function multMatrix(m) {
  mvMatrix = mvMatrix.x(m);
}

function mvTranslate(v) {
  var m = Matrix.Translation($V([v[0], v[1], v[2]])).ensure4x4();
  multMatrix(m);
}

function mvRotate(ang, v) {
  var arad = ang * Math.PI / 180.0;
  var m = Matrix.Rotation(arad, $V([v[0], v[1], v[2]])).ensure4x4();
  multMatrix(m);
}

var pMatrix;
function perspective(fovy, aspect, znear, zfar) {
  pMatrix = makePerspective(fovy, aspect, znear, zfar);
}


function setMatrixUniforms() {
  gl.uniformMatrix4fv(shaderProgram.pMatrixUniform, false, new Float32Array(pMatrix.flatten()));
  gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform, false, new Float32Array(mvMatrix.flatten()));
}


var cubeVertexPositionBuffer;
var cubeVertexColorBuffer;
var cubeVertexIndexBuffer;
function initBuffers() {
  cubeVertexPositionBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
  cubeVertexPositionBuffer.itemSize = 3;
  cubeVertexPositionBuffer.numItems = vertices.length / 3;

  cubeVertexColorBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexColorBuffer);

  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
  cubeVertexColorBuffer.itemSize = 4;
  cubeVertexColorBuffer.numItems = colors.length / 4;

  cubeVertexIndexBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
  gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(indices), gl.STATIC_DRAW);
  cubeVertexIndexBuffer.itemSize = 1;
  cubeVertexIndexBuffer.numItems = indices.length;

  cubeVertexTextureCoordBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(uvs), gl.STATIC_DRAW);
  cubeVertexTextureCoordBuffer.itemSize = 2;
  cubeVertexTextureCoordBuffer.numItems = uvs.length / 2;    
}


var rPyramid = 0;
var rCube = 0;
function drawScene(timestamp) {
  gl.viewport(0, 0, gl.viewportWidth, gl.viewportHeight);
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  perspective(45, gl.viewportWidth / gl.viewportHeight, 0.1, 100.0);
  loadIdentity();

  mvTranslate([0.0, 0.0, -8.0])

  mvPushMatrix();
  mvRotate(rCube, [1, 1, 1]);

  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexPositionBuffer);
  gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, cubeVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexColorBuffer);
  gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, cubeVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0);

  gl.bindBuffer(gl.ARRAY_BUFFER, cubeVertexTextureCoordBuffer);
  gl.vertexAttribPointer(shaderProgram.textureCoordAttribute, cubeVertexTextureCoordBuffer.itemSize, gl.FLOAT, false, 0, 0);
  
  gl.activeTexture(gl.TEXTURE0);
  gl.bindTexture(gl.TEXTURE_2D, tunnelTexture);
  // [mbs bug?] gl.uniform1i(shaderProgram.samplerUniform, 0);
  
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, cubeVertexIndexBuffer);
  setMatrixUniforms();

  currentTime = (currentTime + 0.01);
  gl.uniform1f(shaderProgram.fTimeUniform, currentTime);
  gl.drawElements(drawingMode, cubeVertexIndexBuffer.numItems, gl.UNSIGNED_SHORT, 0);

  mvPopMatrix();

  requestAnimationFrame(drawScene,16); // ~60 fps
  
}

var tunnelTexture;
function initTexture() {
  tunnelTexture = gl.createTexture();
  tunnelTexture.image = new Image();
  tunnelTexture.image.onload=function() {
    handleLoadedTexture(tunnelTexture)
  };

  tunnelTexture.image.src = nodejs ? __dirname+"/texture.jpg" : "texture.jpg";
}

function handleLoadedTexture(texture) {
    gl.bindTexture(gl.TEXTURE_2D, texture);
    gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
    //gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, texture.image.width,texture.image.height,0,gl.RGBA, gl.UNSIGNED_BYTE, texture.image);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.bindTexture(gl.TEXTURE_2D, null);
}

function webGLStart() {
  var canvas = document.createElement("canvas",800,600);

  initGL(canvas);

  document.on("resize", function (evt) {
    // console.log("resize "+canvas.width+" x "+canvas.height);
    gl.viewportWidth=canvas.width;
    gl.viewportHeight=canvas.height;
  });

  toggleTriangles();
  initShaders();
  initTexture();
  initBuffers();

  drawScene();
}

function toggleTriangles() {
  drawingMode = drawingMode == gl.TRIANGLES ? gl.LINE_STRIP : gl.TRIANGLES;
}

webGLStart();

