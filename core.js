'use strict';

require('segfault-raub');

require('deps-opengl-raub');

const { getBin } = require('addon-tools-raub');

const core = require(`./${getBin()}/webgl`);


module.exports = core;
