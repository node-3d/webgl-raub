'use strict';

const path = require('node:path');

const {
	copy,
} = require('addon-tools-raub');

const {
	bin,
} = require('deps-opengl-raub');


const fail = (error) => {
	console.error(error);
	process.exit(-1);
};


(async () => {
	try {
		await copy(path.resolve(`${__dirname}/opengl32.dll`), `${bin}/opengl32.dll`);
	} catch (error) {
		fail(error);
	}
})();
