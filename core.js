'use strict';

require('segfault-raub');
require('deps-opengl-raub');
const { getBin, createLogger } = require('addon-tools-raub');

createLogger({ name: 'webgl' });

const core = require(`./${getBin()}/webgl.node`);


module.exports = core;
