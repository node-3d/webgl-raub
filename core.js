'use strict';

require('segfault-raub');

require('deps-opengl-raub');

const { bin } = require('addon-tools-raub');

const core = require(`./${bin}/webgl`);


module.exports = core;
