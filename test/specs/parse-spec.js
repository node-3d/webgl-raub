'use strict';

const { read } = require('addon-tools-raub');

const parseSpec = async (name) => {
	const text = await read(`${__dirname}/${name}.idl`);
	
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
	
	console.log(constants.join(', '));
	console.log(methods.join(', '));
	
	return {
		constants,
		methods,
	};
};

module.exports = {
	parseSpec,
};