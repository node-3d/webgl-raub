{
	'variables': {
		'bin': '<!(node -e "import(\'@node-3d/addon-tools\').then((m) => m.printBin())")',
		'gl_include': '<!(node -p "require(\'@node-3d/deps-opengl\').include")',
		'gl_bin': '<!(node -p "require(\'@node-3d/deps-opengl\').bin")',
	},
	'targets': [{
		'target_name': 'webgl',
		'includes': ['common.gypi'],
		'sources': [
			'cpp/bindings.cpp',
		],
		'include_dirs': [
			'<!@(node -e "import(\'@node-3d/addon-tools\').then((m) => m.printInclude())")',
			'<(gl_include)',
		],
		'library_dirs': ['<(gl_bin)'],
		'conditions': [
			['OS=="linux"', {
				'libraries': [
					"-Wl,-rpath,'$$ORIGIN'",
					"-Wl,-rpath,'$$ORIGIN/../node_modules/@node-3d/deps-opengl/<(bin)'",
					"-Wl,-rpath,'$$ORIGIN/../../@node-3d/deps-opengl/<(bin)'",
					'<(gl_bin)/libGLEW.so.2.2',
					'<(gl_bin)/libGL.so',
					'<(gl_bin)/libXrandr.so',
				],
			}],
			['OS=="mac"', {
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/@node-3d/deps-opengl/<(bin)',
					'-Wl,-rpath,@loader_path/../../@node-3d/deps-opengl/<(bin)',
					'<(gl_bin)/glew.dylib',
				],
			}],
			['OS=="win"', {
				'libraries': ['glew32.lib', 'opengl32.lib'],
			}],
		],
	}]
}
