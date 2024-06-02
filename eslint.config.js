'use strict';

const js = require('@eslint/js');


module.exports = [
	js.configs.recommended,
	{
		languageOptions: {
			'parserOptions': {
				'ecmaVersion': 2022,
				sourceType: 'commonjs'
			},
			globals: {
				global: 'readonly',
				require: 'readonly',
				Buffer: 'readonly',
				module: 'readonly',
				console: 'readonly',
				__dirname: 'readonly',
				process: 'readonly',
				setTimeout: 'readonly',
				setImmediate: 'readonly',
				clearImmediate: 'readonly',
			},
		},
		'rules': {
			'arrow-parens': ['error', 'always'],
			'no-trailing-spaces': [
				'error',
				{
					'skipBlankLines': true
				}
			],
			'indent': [
				'error',
				'tab',
				{
					'SwitchCase': 1
				}
			],
			'operator-linebreak': [
				'error',
				'after',
				{
					'overrides': {
						'?': 'before',
						':': 'before'
					}
				}
			],
			'max-len': ['error', 110],
			'quotes': [
				'error',
				'single'
			],
			'semi': [
				'error',
				'always'
			],
			'no-multiple-empty-lines': ['error', { 'max': 3, 'maxEOF': 1, 'maxBOF': 1 }],
			'keyword-spacing': ['error', { 'before': true, 'after': true }],
			'space-before-blocks': ['error'],
			'space-before-function-paren': [
				'error', {'anonymous': 'always', 'named': 'never', 'asyncArrow': 'always'}
			],
			'camelcase': ['error'],
			'no-tabs': [0],
			'no-unused-vars': [
				'error',
				{
					'argsIgnorePattern': '^_',
					'varsIgnorePattern': '^_',
					'caughtErrorsIgnorePattern': '^_'
				}
			],
			'global-require': [0],
			'no-underscore-dangle': [0],
			'no-plusplus': [0],
			'no-shadow': [0],
			'node/no-unpublished-require': [0],
			'no-process-exit': [0],
			'linebreak-style': [0],
			'node/no-missing-require': [0],
			'no-console': [0],
			'node/no-unsupported-features/es-builtins': 0,
			'node/no-unsupported-features/node-builtins': 0,
			'func-names': [
				'error',
				'never',
				{
					'generators': 'never'
				}
			]
		}
	},
];
