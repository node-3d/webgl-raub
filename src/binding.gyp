{
	'variables': {
		'bin'        : '<!(node -p "require(\'addon-tools-raub\').bin")',
		'gl_include' : '<!(node -p "require(\'deps-opengl-raub\').include")',
		'gl_bin'     : '<!(node -p "require(\'deps-opengl-raub\').bin")',
	},
	'targets': [{
		'target_name': 'webgl',
		'sources': [
			'cpp/attrib.cpp',
			'cpp/bindings.cpp',
			'cpp/blend.cpp',
			'cpp/buffers.cpp',
			'cpp/framebuffers.cpp',
			'cpp/instances.cpp',
			'cpp/programs.cpp',
			'cpp/renderbuffers.cpp',
			'cpp/shaders.cpp',
			'cpp/stencil.cpp',
			'cpp/textures.cpp',
			'cpp/transformfeedback.cpp',
			'cpp/uniform.cpp',
			'cpp/vertexarrays.cpp',
			'cpp/webgl.cpp',
		],
		'cflags!': ['-fno-exceptions'],
		'cflags_cc!': ['-fno-exceptions'],
		'include_dirs': [
			'<!@(node -p "require(\'addon-tools-raub\').include")',
			'<(gl_include)',
		],
		'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
		'library_dirs': ['<(gl_bin)'],
		'conditions': [
			[
				'OS=="linux"',
				{
					'libraries': [
						"-Wl,-rpath,'$$ORIGIN'",
						"-Wl,-rpath,'$$ORIGIN/../node_modules/deps-opengl-raub/<(bin)'",
						"-Wl,-rpath,'$$ORIGIN/../../deps-opengl-raub/<(bin)'",
						'<(gl_bin)/libGLEW.so.2.0',
						'<(gl_bin)/libGL.so',
						'<(gl_bin)/libXrandr.so',
					],
					'defines': ['__linux__'],
				}
			],
			[
				'OS=="mac"',
				{
					'libraries': [
						'-Wl,-rpath,@loader_path',
						'-Wl,-rpath,@loader_path/../node_modules/deps-opengl-raub/<(bin)',
						'-Wl,-rpath,@loader_path/../../deps-opengl-raub/<(bin)',
						'<(gl_bin)/glew.dylib',
					],
					'defines': ['__APPLE__'],
				}
			],
			[
				'OS=="win"',
				{
					'libraries': ['glew32.lib', 'opengl32.lib'],
					'defines' : [
						'WIN32_LEAN_AND_MEAN',
						'VC_EXTRALEAN',
						'_WIN32',
					],
					'msvs_version'  : '2013',
					'msvs_settings' : {
						'VCCLCompilerTool' : {
							'AdditionalOptions' : [
								'/O2','/Oy','/GL','/GF','/Gm-','/EHsc',
								'/MT','/GS','/Gy','/GR-','/Gd',
							]
						},
						'VCLinkerTool' : {
							'AdditionalOptions' : ['/OPT:REF','/OPT:ICF','/LTCG']
						},
					},
				}
			],
		],
	}]
}
