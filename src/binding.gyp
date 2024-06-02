{
	'variables': {
		'bin': '<!(node -p "require(\'addon-tools-raub\').getBin()")',
		'gl_include': '<!(node -p "require(\'deps-opengl-raub\').include")',
		'gl_bin': '<!(node -p "require(\'deps-opengl-raub\').bin")',
	},
	'targets': [{
		'target_name': 'webgl',
		'sources': [
			'cpp/attrib.cpp',
			'cpp/bindings.cpp',
			'cpp/blend.cpp',
			'cpp/buffers.cpp',
			'cpp/clear.cpp',
			'cpp/draw.cpp',
			'cpp/framebuffers.cpp',
			'cpp/programs.cpp',
			'cpp/queries.cpp',
			'cpp/renderbuffers.cpp',
			'cpp/sampler.cpp',
			'cpp/shaders.cpp',
			'cpp/stencil.cpp',
			'cpp/sync.cpp',
			'cpp/textures.cpp',
			'cpp/transformfeedback.cpp',
			'cpp/uniform.cpp',
			'cpp/vertexarrays.cpp',
			'cpp/webgl.cpp',
		],
		'defines': ['UNICODE', '_UNICODE'],
		'cflags_cc': ['-std=c++17', '-fno-exceptions'],
		'cflags': ['-fno-exceptions'],
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
				'defines': ['__linux__'],
			}],
			['OS=="mac"', {
				'libraries': [
					'-Wl,-rpath,@loader_path',
					'-Wl,-rpath,@loader_path/../node_modules/deps-opengl-raub/<(bin)',
					'-Wl,-rpath,@loader_path/../../deps-opengl-raub/<(bin)',
					'<(gl_bin)/glew.dylib',
				],
				'MACOSX_DEPLOYMENT_TARGET': '10.9',
				'defines': ['__APPLE__'],
				'CLANG_CXX_LIBRARY': 'libc++',
				'OTHER_CFLAGS': ['-std=c++17', '-fno-exceptions'],
			}],
			['OS=="win"', {
				'libraries': ['glew32.lib', 'opengl32.lib'],
				'defines': ['WIN32_LEAN_AND_MEAN', 'VC_EXTRALEAN', '_WIN32', '_HAS_EXCEPTIONS=0'],
				'msvs_settings' : {
					'VCCLCompilerTool' : {
						'AdditionalOptions' : [
							'/O2','/Oy','/GL','/GF','/Gm-', '/std:c++17',
							'/EHa-s-c-','/MT','/GS','/Gy','/GR-','/Gd',
						],
					},
					'VCLinkerTool' : {
						'AdditionalOptions' : ['/DEBUG:NONE', '/LTCG', '/OPT:NOREF'],
					},
				},
			}],
		],
	}]
}
