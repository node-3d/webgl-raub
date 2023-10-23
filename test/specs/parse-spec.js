'use strict';

const { readFileSync } = require('node:fs');


const parseSpec = (name) => {
	const text = readFileSync(`${__dirname}/${name}.idl`).toString();
	
	const constants = text.match(
		/const GL\w+ \w+/g,
	).map(
		(str) => str.replace(/const GL\w+ /, ''),
	);
	
	const methods = text.match(
		/\w+\(/g,
	).map(
		(str) => str.replace(/\($/, ''),
	).filter(
		(str) => (str !== 'typedef' && str !== 'Constructor')
	).filter(
		(a, i, v) => (v.indexOf(a) === i)
	).sort();
	
	return {
		constants,
		methods,
	};
};

module.exports = {
	parseSpec,
};