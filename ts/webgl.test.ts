import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { webgl } from './index.ts';

const constants = [
	'contextAttributes', 'drawingBufferWidth', 'drawingBufferHeight',
] as const;

const methods = [
	'init', 'useWebGL2', 'getContextAttributes',
] as const;

describe('WebGL', () => {
	it('exports an object', () => {
		assert.strictEqual(typeof webgl, 'object');
	});
	
	for (const constant of constants) {
		it(`\`${constant}\` constant exposed`, () => {
			assert.ok(webgl[constant] !== undefined);
		});
	}
	
	for (const method of methods) {
		it(`\`${method}()\` method exposed`, () => {
			assert.strictEqual(typeof webgl[method], 'function');
		});
	}
});

