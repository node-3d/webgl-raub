{
	'variables': {
		'bin': '<!(node -p "require(\'addon-tools-raub\').getBin()")',
		'gl_include': '<!(node -p "require(\'deps-opengl-raub\').include")',
		'gl_bin': '<!(node -p "require(\'deps-opengl-raub\').bin")',
	},
	'targets': [{
		'target_name': 'webgl',
		'includes': ['../node_modules/addon-tools-raub/utils/common.gypi'],
		'sources': [
			'cpp/bindings.cpp',
		],
		'include_dirs': [
			'<!@(node -p "require(\'addon-tools-raub\').getInclude()")',
			'<(gl_include)',
		],
		'library_dirs': ['<(gl_bin)'],
		'conditions': [
			['OS=="linux"', {
				'libraries': [
					"-Wl,-rpath,'$$ORIGIN'",
					"-Wl,-rpath,'$$ORIGIN/../node_modules/deps-opengl-raub/<(bin)'",
					"-Wl,-rpath,'$$ORIGIN/../../deps-opengl-raub/<(bin)'",
					'<(gl_bin)/libGLEW.so.2.2',
					'<(gl_bin)/libGL.so',
					'<(gl_bin)/libXrandr.so',
				],
			}],
			['OS=="mac"', {
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/deps-opengl-raub/<(bin)',
					'-Wl,-rpath,@loader_path/../../deps-opengl-raub/<(bin)',
					'<(gl_bin)/glew.dylib',
				],
			}],
			['OS=="win"', {
				'libraries': ['glew32.lib', 'opengl32.lib'],
			}],
		],
	}]
}
