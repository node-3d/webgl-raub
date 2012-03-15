nodejs=true;

var WebGL=require('../index'),
    Image = WebGL.Image,
    document = WebGL.document();

var gl, log=console.log, alert=log;

function initGL(canvas) {
  try {
    gl = canvas.getContext("experimental-webgl");
    gl.viewportWidth = canvas.width;
    gl.viewportHeight = canvas.height;
  } catch (e) {
    alert("Could not initialise WebGL, sorry :-(");
    process.exit(-1);
  }
}


(function webGLStart() {
  var canvas = document.createElement("test-canvas");
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
  
  extensions.forEach(function(extension) {
    log("looking for "+extension+": "+gl.getExtension(extension));
  });
}());
