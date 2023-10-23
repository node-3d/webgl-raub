'use strict';

const assert = require('node:assert').strict;
const { describe, it } = require('node:test');

const { parseSpec } = require('./specs/parse-spec');
const webgl = require('..');


const parsedWebgl103 = parseSpec('webgl103');
const parsedWebgl200 = parseSpec('webgl200');

const testSpec = (name, parsed) => {
	describe(name, () => {
		parsed.constants.forEach((constant) => {
			it(`\`${constant}\` constant exposed`, () => {
				assert.ok(webgl[constant] !== undefined);
			});
		});
		
		parsed.methods.forEach((method) => {
			it(`\`${method}()\` method exposed`, () => {
				assert.strictEqual(typeof webgl[method], 'function');
			});
		});
	});
};

describe('WebGL Specs', () => {
	testSpec('WebGL 1.03', parsedWebgl103);
	testSpec('WebGL 2.00', parsedWebgl200);
	
	return Promise.resolve();
});
