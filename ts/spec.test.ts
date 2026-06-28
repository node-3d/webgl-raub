import assert from 'node:assert/strict';
import { describe, it } from 'node:test';
import { parseSpec } from './specs/parse-spec.ts';
import type { ParsedSpec } from './specs/parse-spec.ts';
import { webgl } from './index.ts';
import type { TWebGL } from './index.ts';

const parsedWebgl103 = parseSpec('webgl103');
const parsedWebgl200 = parseSpec('webgl200');

const testSpec = (name: string, parsed: ParsedSpec) => {
	describe(name, () => {
		for (const constant of parsed.constants) {
			it(`\`${constant}\` constant exposed`, () => {
				assert.ok(webgl[constant as keyof TWebGL] !== undefined);
			});
		}
		
		for (const method of parsed.methods) {
			it(`\`${method}()\` method exposed`, () => {
				assert.strictEqual(typeof webgl[method as keyof TWebGL], 'function');
			});
		}
	});
};

describe('WebGL Specs', () => {
	testSpec('WebGL 1.03', parsedWebgl103);
	testSpec('WebGL 2.00', parsedWebgl200);
	
	return Promise.resolve();
});

