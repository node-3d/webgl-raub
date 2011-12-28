nodejs=true;

Platform = require('../lib/platform')(640,480);

var gl, log=console.log;

function initGL(canvas) {
  try {
    if(nodejs) {
      gl = Platform.gl;
      gl.viewportWidth = Platform.width;
      gl.viewportHeight = Platform.height;
    }
    else {
      gl = canvas.getContext("experimental-webgl");
      gl.viewportWidth = canvas.width;
      gl.viewportHeight = canvas.height;
    }
  } catch (e) {
  }
  if (!gl) {
    alert("Could not initialise WebGL, sorry :-(");
  }
}


function webGLStart() {
  var canvas = "";// [mbs] TDB document.getElementById("lesson02-canvas");
  initGL(canvas);
  
  var extensions=gl.getSupportedExtensions();
  var num=extensions.length;
  log("Supported extensions: "+num);
  
  var i=0;
  while(i<num)
    log(extensions[i++]+" "+extensions[i++]+" "+extensions[i++]+" "+extensions[i++]);
  
  var extensions= [ "OES_texture_float", "OES_texture_half_float", "OES_standard_derivatives", 
                    "WEBGL_debug_renderer_info", "WEBGL_debug_shaders",
                    "WEBGL_lose_context", "OES_vertex_array_object" ];
  
  for(i in extensions) {
    var ext=extensions[i];
    log("looking for "+extensions[i]+": "+gl.getExtension(extensions[i]));
  }
}

webGLStart();

