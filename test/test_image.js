'use strict';

const Image = require('../lib/image');


const img = new Image();

img.onload = function () {
  console.log("web onload called");
};

img.src = 'img/glass.gif';
