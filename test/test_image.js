'use strict';

const { Image } = require('..');


const img = new Image();

img.onload = function () {
  console.log(`Image 'onload' called.`);
};

img.src = `${__dirname}/img/glass.gif`;
