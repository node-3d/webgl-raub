import { defineConfig } from '@rslib/core';

export default defineConfig({
	lib: [
		{
			format: 'esm',
			bundle: true,
			autoExtension: false,
			syntax: 'es2024',
			dts: {
				tsgo: true,
			},
			outBase: './ts',
			source: {
				entry: {
					index: './ts/index.ts',
				},
				tsconfigPath: './tsconfig.build.json',
			},
			output: {
				target: 'node',
				distPath: {
					root: './dist',
				},
			},
		},
	],
});
