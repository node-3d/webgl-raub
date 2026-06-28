{
	'defines': ['UNICODE', '_UNICODE'],
	'conditions': [
		['OS=="linux"', {
			'defines': ['__linux__'],
			'cflags_cc': ['-std=c++20', '-fno-exceptions'],
		}],
		['OS=="mac"', {
			'MACOSX_DEPLOYMENT_TARGET': '10.9',
			'defines': ['__APPLE__'],
			'CLANG_CXX_LIBRARY': 'libc++',
			'OTHER_CFLAGS': ['-std=c++20', '-fno-exceptions'],
		}],
		['OS=="win"', {
			'defines': ['WIN32_LEAN_AND_MEAN', 'VC_EXTRALEAN', '_WIN32', '_HAS_EXCEPTIONS=0'],
		}],
	],
	'msvs_settings': {
		'VCCLCompilerTool': {
			'RuntimeLibrary': 2,
			'BufferSecurityCheck': 'false',
			'AdditionalOptions!' : ['/MT'],
			'AdditionalOptions' : [
				'/O2', '/GL', '/GS-', '/GR-', '/Gd', '/EHa-s-c-', '/MD',
			],
		},
		'VCLinkerTool': {
			'AdditionalOptions!' : ['/LTCG:INCREMENTAL'],
			'AdditionalOptions' : ['/DEBUG:NONE', '/LTCG', '/OPT:REF', '/OPT:ICF'],
		},
	},
}
