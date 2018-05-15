'use strict';

require('deps-opengl-raub');

const { binPath } = require('addon-tools-raub');

const core = require(`./${binPath}/webgl`);


module.exports = core;
