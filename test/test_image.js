var Image = require('../lib/image');

var img = new Image();

img.onload=function() {
  console.log("web onload called");
}

img.src=__dirname+"/node_logo.png";