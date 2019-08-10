'use strict';

const install = require('addon-tools-raub/install');


const prefix = 'https://github.com/node-3d/glfw-raub/releases/download';
const tag    = process.env.npm_package_config_install;

install(`${prefix}/${tag}`);
