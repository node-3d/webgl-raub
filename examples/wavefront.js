Platform = require('../lib/platform')(640,480);
Platform.setTitle("Traveling Wavefronts");
gl = Platform.gl;

gl.viewportWidth = Platform.width;
gl.viewportHeight = Platform.height;

var shaders = {
    "shader-vs": [
      "attribute vec3 aPos;",
      "attribute vec2 aTexCoord;",
      "varying   vec2 pixel;",
      "void main(void) {",
      "   gl_Position = vec4(aPos, 1.);",
      "   pixel = aTexCoord;",
      "}"].join("\n"),

    "shader-fs-blur-horizontal": [
      "#ifdef GL_ES",
      "precision highp float;",
      "#endif",
      "// original shader from http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/",
      "// horizontal blur fragment shader",
      "uniform sampler2D src_tex;",
      "varying vec2 pixel;",
      "uniform vec2 pixelSize;",
      "void main(void) // fragment",
      "{",
      " float h = pixelSize.x;",
      " vec4 sum = vec4(0.0);",
      " sum += texture2D(src_tex, vec2(pixel.x - 4.0*h, pixel.y) ) * 0.05;",
      " sum += texture2D(src_tex, vec2(pixel.x - 3.0*h, pixel.y) ) * 0.09;",
      " sum += texture2D(src_tex, vec2(pixel.x - 2.0*h, pixel.y) ) * 0.12;",
      " sum += texture2D(src_tex, vec2(pixel.x - 1.0*h, pixel.y) ) * 0.15;",
      " sum += texture2D(src_tex, vec2(pixel.x + 0.0*h, pixel.y) ) * 0.16;",
      " sum += texture2D(src_tex, vec2(pixel.x + 1.0*h, pixel.y) ) * 0.15;",
      " sum += texture2D(src_tex, vec2(pixel.x + 2.0*h, pixel.y) ) * 0.12;",
      " sum += texture2D(src_tex, vec2(pixel.x + 3.0*h, pixel.y) ) * 0.09;",
      " sum += texture2D(src_tex, vec2(pixel.x + 4.0*h, pixel.y) ) * 0.05;",
      "    gl_FragColor.xyz = sum.xyz/0.99; // normalize",
      " gl_FragColor.a = 1.;",
      "}"].join("\n"),
    "shader-fs-blur-vertical": [
      "#ifdef GL_ES",
      "precision highp float;",
      "#endif",
      "// original shader from http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/",
      "// vertical blur fragment shader",
      "uniform sampler2D src_tex;",
      "varying vec2 pixel;",
      "uniform vec2 pixelSize;",
      "void main(void) // fragment",
      "{",
      " float v = pixelSize.y;",
      " vec4 sum = vec4(0.0);",
      " sum += texture2D(src_tex, vec2(pixel.x, - 4.0*v + pixel.y) ) * 0.05;",
      " sum += texture2D(src_tex, vec2(pixel.x, - 3.0*v + pixel.y) ) * 0.09;",
      " sum += texture2D(src_tex, vec2(pixel.x, - 2.0*v + pixel.y) ) * 0.12;",
      " sum += texture2D(src_tex, vec2(pixel.x, - 1.0*v + pixel.y) ) * 0.15;",
      " sum += texture2D(src_tex, vec2(pixel.x, + 0.0*v + pixel.y) ) * 0.16;",
      " sum += texture2D(src_tex, vec2(pixel.x, + 1.0*v + pixel.y) ) * 0.15;",
      " sum += texture2D(src_tex, vec2(pixel.x, + 2.0*v + pixel.y) ) * 0.12;",
      " sum += texture2D(src_tex, vec2(pixel.x, + 3.0*v + pixel.y) ) * 0.09;",
      " sum += texture2D(src_tex, vec2(pixel.x, + 4.0*v + pixel.y) ) * 0.05;",
      "    gl_FragColor.xyz = sum.xyz/0.99;",
      " gl_FragColor.a = 1.;",
      "}"].join("\n"),

    "shader-fs-advance": [
      "#ifdef GL_ES",
      "precision highp float;",
      "#endif",
      "",
      " uniform sampler2D sampler_prev;",
      " uniform sampler2D sampler_prev_n;",
      " uniform sampler2D sampler_blur;",
      " uniform sampler2D sampler_noise;",
      " uniform sampler2D sampler_noise_n;",
      "",
      " varying vec2 pixel;",
      " uniform vec2 pixelSize;",
      " uniform vec4 rnd;",
      " uniform vec2 mouse;",
      " uniform float time;",
      " uniform float fps;",
      "",
      "void main(void) {",
      " // grabbing the blurred gradients",
      " vec2 d = pixelSize*4.;",
      " vec4 dx = (texture2D(sampler_blur, pixel + vec2(1,0)*d) - texture2D(sampler_blur, pixel - vec2(1,0)*d))*0.5;",
      " vec4 dy = (texture2D(sampler_blur, pixel + vec2(0,1)*d) - texture2D(sampler_blur, pixel - vec2(0,1)*d))*0.5;",
      " ",
      " vec2 zoom_in = pixel + vec2(dx.x,dy.x)*pixelSize*8.; // adding the traveling wave front",
      " vec2 rand_noise = texture2D(sampler_noise, zoom_in + vec2(rnd.x, rnd.y)).xy;",
      " gl_FragColor.x = texture2D(sampler_prev, zoom_in).x + (rand_noise.x-0.5)*0.0025 - 0.002; // decay with error diffusion",
      " gl_FragColor.x -= (texture2D(sampler_blur, zoom_in + (rand_noise-0.5)*pixelSize).x -",
      "           texture2D(sampler_prev, zoom_in + (rand_noise-0.5)*pixelSize)).x*0.062; // reaction-diffusion",
      "",
      " gl_FragColor.a = 1.;",
      "}"].join("\n"),
    "shader-fs-composite": [
      "#ifdef GL_ES",
      "precision highp float;",
      "#endif",
      "",
      " uniform sampler2D sampler_prev;",
      " uniform sampler2D sampler_prev_n;",
      " uniform sampler2D sampler_blur;",
      " uniform sampler2D sampler_noise;",
      " uniform sampler2D sampler_noise_n;",
      "",
      " varying vec2 pixel;",
      " uniform vec2 pixelSize;",
      " uniform vec2 aspect;",
      " uniform vec4 rnd;",
      " uniform vec2 mouse;",
      " uniform float time;",
      "",
      "void main(void) {",
      "",
      " vec2 lightSize=vec2(4.);",
      "",
      " // grabbing the blurred gradients",
      " vec2 d = pixelSize*2.;",
      " vec4 dx = (texture2D(sampler_blur, pixel + vec2(1,0)*d) - texture2D(sampler_blur, pixel - vec2(1,0)*d))*0.5;",
      " vec4 dy = (texture2D(sampler_blur, pixel + vec2(0,1)*d) - texture2D(sampler_blur, pixel - vec2(0,1)*d))*0.5;",
      "",
      " // adding the pixel gradients",
      " d = pixelSize*1.;",
      " dx += texture2D(sampler_prev, pixel + vec2(1,0)*d) - texture2D(sampler_prev, pixel - vec2(1,0)*d);",
      " dy += texture2D(sampler_prev, pixel + vec2(0,1)*d) - texture2D(sampler_prev, pixel - vec2(0,1)*d);",
      "",
      " vec2 displacement = vec2(dx.x,dy.x)*lightSize; // using only the red gradient as displacement vector",
      " float light = pow(max(1.-distance(0.5+(pixel-0.5)*aspect*lightSize + displacement,0.5+(mouse-0.5)*aspect*lightSize),0.),4.);",
      "// vec4 rd = 0.85-(1.-texture2D(sampler_prev,pixel-vec2(dx.x,dy.x)*pixelSize*2.5).x) + light*0.18;",
      " //rd = mix(rd, 1., light*(1.-texture2D(sampler_blur,pixel-vec2(dx.x,dy.x)*pixelSize*4.)).x); ",
      "",
      " // recoloring the lit up red channel",
      " vec4 rd = vec4(texture2D(sampler_prev,pixel+vec2(dx.x,dy.x)*pixelSize*8.).x)*vec4(0.7,1.5,2.0,1.0)-vec4(0.3,1.0,1.0,1.0);",
      " gl_FragColor = mix(rd,vec4(8.0,6.,2.,1.), light*0.75*vec4(1.-texture2D(sampler_prev,pixel+vec2(dx.x,dy.x)*pixelSize*8.).x)); ",
      " ",
      " //gl_FragColor = texture2D(sampler_prev, pixel); // bypass",
      " gl_FragColor.a = 1.;",
      "}"].join("\n")
  };

  function getShader(gl, id) {
    if (!shaders.hasOwnProperty(id)) return null;
    var str = shaders[id];
    var shader;
    if (id.match(/-fs/)) {
      shader = gl.createShader(gl.FRAGMENT_SHADER);
    } else if (id.match(/-vs/)) {
      shader = gl.createShader(gl.VERTEX_SHADER);
    } else { return null; }
    gl.shaderSource(shader, str);
    gl.compileShader(shader);
    if (gl.getShaderParameter(shader, gl.COMPILE_STATUS) == 0)
      throw new Error(gl.getShaderInfoLog(shader));
    return shader;
  }



  requestAnimFrame = Platform.requestAnimationFrame;

  var gl;
  var prog_advance;
  var prog_composite;
  var prog_blur_horizontal;
  var prog_blur_vertical;
  var FBO_main;
  var FBO_main2;
  var FBO_helper;
  var FBO_blur;
  var FBO_noise;
  var texture_main_l; // main, linear
  var texture_main_n; // main, nearest (accurate pixel access on the same buffer)
  var texture_main2_l; // main double buffer, linear
  var texture_main2_n; // main double buffer, nearest (accurate pixel access on the same buffer)
  var texture_helper; // to be used when a buffer for multi-pass shader programs is needed (2-pass Gaussian blur)
  var texture_blur; // blur result
  var texture_noise_n; // noise pixel accurate
  var texture_noise_l; // noise interpolated pixel access

  var halted = false;
  var delay = 3;
  var it = 1;
  var frames = 0;
  var fps = 60; // no hurdle for DX10 graphics cards
  var time;
  var mouseX = 0.5;
  var mouseY = 0.5;
  var animation;
  var timer;
  // texture size (must be powers of two, remember 2048x1024 flat could also be a 128x128x128 voxel)
  var sizeX = 256;
  var sizeY = 256; // 2048x1024 flat or 128x128x128 cube
  // viewport size
  var viewX = Platform.width;
  var viewY = Platform.height;

  load();
  function load() {
    clearInterval(timer);
    gl = Platform.gl
    if (!gl) {
      alert("Your browser does not support WebGL");
      return;
    }
    
  Platform.on("mousemove", function (evt) {
      mouseX = evt.x / viewX;
      mouseY = 1 - evt.y / viewY;
  });
//    document.onmousemove = function(evt) {
//      mouseX = evt.pageX / viewX;
//      mouseY = 1 - evt.pageY / viewY;
//    };
//    document.onclick = function(evt) {
//      halted = !halted;
//    };
//    c.width = viewX;
//    c.height = viewY;

    prog_advance = gl.createProgram();
    gl.attachShader(prog_advance, getShader(gl, "shader-vs"));
    gl.attachShader(prog_advance, getShader(gl, "shader-fs-advance"));
    gl.linkProgram(prog_advance);

    prog_composite = gl.createProgram();
    gl.attachShader(prog_composite, getShader(gl, "shader-vs"));
    gl.attachShader(prog_composite, getShader(gl, "shader-fs-composite"));
    gl.linkProgram(prog_composite);

    prog_blur_horizontal = gl.createProgram();
    gl.attachShader(prog_blur_horizontal, getShader(gl, "shader-vs"));
    gl.attachShader(prog_blur_horizontal, getShader(gl, "shader-fs-blur-horizontal"));
    gl.linkProgram(prog_blur_horizontal);

    prog_blur_vertical = gl.createProgram();
    gl.attachShader(prog_blur_vertical, getShader(gl, "shader-vs"));
    gl.attachShader(prog_blur_vertical, getShader(gl, "shader-fs-blur-vertical"));
    gl.linkProgram(prog_blur_vertical);

    var posBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, posBuffer);

    var vertices = new Float32Array([ -1, -1, 0, 1, -1, 0, -1, 1, 0, 1, 1, 0 ]);

    var aPosLoc = gl.getAttribLocation(prog_advance, "aPos");
    gl.enableVertexAttribArray(aPosLoc);

    var aTexLoc = gl.getAttribLocation(prog_advance, "aTexCoord");
    gl.enableVertexAttribArray(aTexLoc);

    var texCoords = new Float32Array([ 0, 0, 1, 0, 0, 1, 1, 1 ]);

    var texCoordOffset = vertices.byteLength;

    gl.bufferData(gl.ARRAY_BUFFER, new Uint8Array(texCoordOffset + texCoords.byteLength), gl.STATIC_DRAW);
    gl.bufferSubData(gl.ARRAY_BUFFER, 0, vertices);
    gl.bufferSubData(gl.ARRAY_BUFFER, texCoordOffset, texCoords);
    gl.vertexAttribPointer(aPosLoc, 3, gl.FLOAT, gl.FALSE, 0, 0);
    gl.vertexAttribPointer(aTexLoc, 2, gl.FLOAT, gl.FALSE, 0, texCoordOffset);

    var noisepixels = [];
    var pixels = [];
    for ( var i = 0; i < sizeX; i++) {
      for ( var j = 0; j < sizeY; j++) {
        noisepixels.push(Math.random() * 255, Math.random() * 255, Math.random() * 255, 255);
        pixels.push(0, 0, 0, 255);
      }
    }
    /*
     * if (Math.random() > density) pixels.push(0, 0, 0, 0); else pixels.push(255, 0, 0, 0);
     */

    var rawData = new Uint8Array(noisepixels);
    texture_main_l = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_main_l);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    texture_main_n = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_main_n);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

    rawData = new Uint8Array(noisepixels);
    rawData = new Uint8Array(noisepixels);
    texture_main2_l = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_main2_l);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    texture_main2_n = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_main2_n);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

    rawData = new Uint8Array(pixels);
    texture_helper = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_helper);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    rawData = new Uint8Array(pixels);
    texture_blur = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_blur);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    rawData = new Uint8Array(noisepixels);
    texture_noise_l = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_noise_l);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.LINEAR);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.LINEAR);

    texture_noise_n = gl.createTexture();
    gl.bindTexture(gl.TEXTURE_2D, texture_noise_n);
    gl.pixelStorei(gl.UNPACK_ALIGNMENT, 1);
    gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, sizeX, sizeY, 0, gl.RGBA, gl.UNSIGNED_BYTE, rawData);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
    gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

    // gl.uniform1i(gl.getUniformLocation(prog, "uTexSamp"), 0);
    
    FBO_main = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_main);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture_main_l, 0);

    FBO_main2 = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_main2);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture_main2_l, 0);

    FBO_helper = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_helper);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture_helper, 0);

    FBO_blur = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_blur);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture_blur, 0);

    FBO_noise = gl.createFramebuffer();
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_noise);
    gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, texture_noise_l, 0);

    gl.useProgram(prog_advance);
    setUniforms(prog_advance);

    gl.useProgram(prog_blur_horizontal);
    gl.uniform2f(gl.getUniformLocation(prog_blur_horizontal, "pixelSize"), 1. / sizeX, 1. / sizeY);
    gl.uniform1i(gl.getUniformLocation(prog_blur_horizontal, "src_tex"), 0);

    gl.useProgram(prog_blur_vertical);
    gl.uniform2f(gl.getUniformLocation(prog_blur_vertical, "pixelSize"), 1. / sizeX, 1. / sizeY);
    gl.uniform1i(gl.getUniformLocation(prog_blur_vertical, "src_tex"), 0);

    gl.useProgram(prog_composite);
    setUniforms(prog_composite);

    gl.activeTexture(gl.TEXTURE2);
    gl.bindTexture(gl.TEXTURE_2D, texture_blur);

    gl.activeTexture(gl.TEXTURE3);
    gl.bindTexture(gl.TEXTURE_2D, texture_noise_l);

    gl.activeTexture(gl.TEXTURE4);
    gl.bindTexture(gl.TEXTURE_2D, texture_noise_n);

    calculateBlurTexture();

    timer = setInterval(fr, 500);
    time = new Date().getTime();
    animation = "animate";
    anim();
  }
  function setUniforms(program) {
    gl.uniform2f(gl.getUniformLocation(program, "pixelSize"), 1. / sizeX, 1. / sizeY);
    gl.uniform4f(gl.getUniformLocation(program, "rnd"), Math.random(), Math.random(), Math.random(), Math.random());
    gl.uniform1f(gl.getUniformLocation(program, "fps"), fps);
    gl.uniform1f(gl.getUniformLocation(program, "time"), time || 0);
    gl.uniform2f(gl.getUniformLocation(program, "aspect"), Math.max(1, viewX / viewY), Math.max(1, viewY / viewX));
    gl.uniform2f(gl.getUniformLocation(program, "mouse"), mouseX, mouseY);
    gl.uniform1i(gl.getUniformLocation(program, "sampler_prev"), 0);
    gl.uniform1i(gl.getUniformLocation(program, "sampler_prev_n"), 1);
    gl.uniform1i(gl.getUniformLocation(program, "sampler_blur"), 2);
    gl.uniform1i(gl.getUniformLocation(program, "sampler_noise"), 3);
    gl.uniform1i(gl.getUniformLocation(program, "sampler_noise_n"), 4);
  }
  function calculateBlurTexture() {
    // horizontal
    gl.viewport(0, 0, sizeX, sizeY);
    gl.useProgram(prog_blur_horizontal);
    gl.activeTexture(gl.TEXTURE0);
    if (it < 0) {
      gl.bindTexture(gl.TEXTURE_2D, texture_main2_l);
      gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_helper);
    } else {
      gl.bindTexture(gl.TEXTURE_2D, texture_main_l);
      gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_helper);
    }
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.flush();

    // vertical
    gl.viewport(0, 0, sizeX, sizeY);
    gl.useProgram(prog_blur_vertical);
    gl.activeTexture(gl.TEXTURE0);
    gl.bindTexture(gl.TEXTURE_2D, texture_helper);
    gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_blur);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.flush();

    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.flush();
  }

  function advance() {
    gl.viewport(0, 0, sizeX, sizeY);
    gl.useProgram(prog_advance);
    setUniforms(prog_advance);
    if (it > 0) {
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture_main_l); // interpolated input
      gl.activeTexture(gl.TEXTURE1);
      gl.bindTexture(gl.TEXTURE_2D, texture_main_n); // "nearest" input
      gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_main2); // write to buffer
    } else {
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture_main2_l); // interpolated
      gl.activeTexture(gl.TEXTURE1);
      gl.bindTexture(gl.TEXTURE_2D, texture_main2_n); // "nearest"
      gl.bindFramebuffer(gl.FRAMEBUFFER, FBO_main); // write to buffer
    }
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.flush();

    calculateBlurTexture();
    it = -it;
  }

  function composite() {
    gl.viewport(0, 0, viewX, viewY);
    gl.useProgram(prog_composite);
    setUniforms(prog_composite);
    if (it < 0) {
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture_main_l);
      gl.activeTexture(gl.TEXTURE1);
      gl.bindTexture(gl.TEXTURE_2D, texture_main_n);
    } else {
      gl.activeTexture(gl.TEXTURE0);
      gl.bindTexture(gl.TEXTURE_2D, texture_main2_l);
      gl.activeTexture(gl.TEXTURE1);
      gl.bindTexture(gl.TEXTURE_2D, texture_main2_n);
    }
    gl.bindFramebuffer(gl.FRAMEBUFFER, null);
    gl.clearColor(0,0,0,1);
    gl.clear(gl.COLOR_BUFFER_BIT);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    gl.flush();
    frames++;
  }

  function anim() {

    if (!halted)
      advance();
    composite();
    
//      gl.bindFramebuffer(gl.FRAMEBUFFER, null);
//    gl.clearColor(1,0,0,1);
//    gl.clear(gl.COLOR_BUFFER_BIT);
    //gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
    Platform.flip();
    
    switch (animation) {
    case "animate":
      setTimeout(function () {
                    requestAnimFrame(anim);
                  }, delay);  
      break;
    case "reset":
      load();
      break;
    }
  }
  function setDelay(v) {
    delay = parseInt(v);
  }
  function fr() {
    var ti = new Date().getTime();
    fps = Math.round(1000 * frames / (ti - time));
    frames = 0;
    time = ti;
  }
