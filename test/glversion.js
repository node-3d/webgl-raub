var WebGL=require('../index'),
    document = WebGL.document(),
    log=console.log;

var canvas = document.createElement("canvas");
gl = canvas.getContext("experimental-webgl");
log("OpenGL");
log("  vendor                   : "+gl.getParameter(gl.VENDOR));
log("  version                  : "+gl.getParameter(gl.VERSION));
log("  shading language version : "+gl.getParameter(gl.SHADING_LANGUAGE_VERSION));
log("  renderer                 : "+gl.getParameter(gl.RENDERER));
var extensions=gl.getParameter(gl.EXTENSIONS);
if(extensions) {
  extensions=extensions.split(' ');
  log("  extensions               : "+extensions.length);
  
  var str="";
  for(var i=0;i<extensions.length;i++) {
    str += extensions[i]+" ";
    if(((i+1) % 4)==0) { 
      log(str); 
      str=""; 
    }
  }
}
else
  log("  extensions               : 0");
