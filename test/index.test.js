'use strict';

const assert = require('node:assert').strict;
const { describe, it } = require('node:test');
const webgl = require('..');


const constants = [
	'contextAttributes', 'drawingBufferWidth', 'drawingBufferHeight',
];

const methods = [
	'init', 'useWebGL2', 'getContextAttributes',
];


describe('WebGL', () => {
	it('exports an object', () => {
		assert.strictEqual(typeof webgl, 'object');
	});
	
	constants.forEach((constant) => {
		it(`\`${constant}\` constant exposed`, () => {
			assert.ok(webgl[constant] !== undefined);
		});
	});
	
	methods.forEach((method) => {
		it(`\`${method}()\` method exposed`, () => {
			assert.strictEqual(typeof webgl[method], 'function');
		});
	});
});
