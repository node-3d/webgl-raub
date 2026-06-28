import { readFileSync } from 'node:fs';

export type ParsedSpec = {
	constants: string[];
	methods: string[];
};

const parseSpec = (name: string): ParsedSpec => {
	const text = readFileSync(new URL(`${name}.idl`, import.meta.url)).toString();
	
	const constants = text.match(
		/const GL\w+ \w+/gu,
	)?.map(
		(str) => str.replace(/const GL\w+ /u, ''),
	) ?? [];
	
	const methods = text.match(
		/\w+\(/gu,
	)?.map(
		(str) => str.replace(/\($/u, ''),
	).filter(
		(str) => (str !== 'typedef' && str !== 'Constructor')
	).filter(
		(a, i, v) => (v.indexOf(a) === i)
	).toSorted() ?? [];
	
	return {
		constants,
		methods,
	};
};

export { parseSpec };
