{
	'variables': {
		'rm'             : '<!(node -e "require(\'addon-tools-raub\').rm()")',
		'cp'             : '<!(node -e "require(\'addon-tools-raub\').cp()")',
		'mkdir'          : '<!(node -e "require(\'addon-tools-raub\').mkdir()")',
		'binary'         : '<!(node -e "require(\'addon-tools-raub\').bin()")',
		'opengl_include' : '<!(node -e "require(\'deps-opengl-raub\').include()")',
		'opengl_bin'     : '<!(node -e "require(\'deps-opengl-raub\').bin()")',
	},
	'targets': [
		{
			'target_name': 'webgl',
			'sources': [
				'cpp/bindings.cpp',
				'cpp/webgl.cpp',
			],
			'include_dirs': [
				'<!@(node -e "require(\'addon-tools-raub\').include()")',
				'<(opengl_include)',
			],
			'library_dirs': [ '<(opengl_bin)' ],
			'conditions': [
				[
					'OS=="linux"',
					{
						'libraries': [
							'-Wl,-rpath,<(opengl_bin)',
							'<(opengl_bin)/libglfw.so.3',
							'<(opengl_bin)/libGLEW.so.2.0',
							'<(opengl_bin)/libGL.so',
							'<(opengl_bin)/libXrandr.so',
						],
					}
				],
				[
					'OS=="mac"',
					{
						'libraries': [
							'-Wl,-rpath,<(opengl_bin)',
							'<(opengl_bin)/glfw.dylib',
							'<(opengl_bin)/glew.dylib'
						],
					}
				],
				[
					'OS=="win"',
					{
						'libraries': [ 'glfw3dll.lib', 'glew32.lib', 'opengl32.lib' ],
						'defines' : [
							'WIN32_LEAN_AND_MEAN',
							'VC_EXTRALEAN'
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
		},
		{
			'target_name'  : 'make_directory',
			'type'         : 'none',
			'dependencies' : ['webgl'],
			'actions'      : [{
				'action_name' : 'Directory created.',
				'inputs'      : [],
				'outputs'     : ['build'],
				'action': ['<(mkdir)', '-p', '<(binary)']
			}],
		},
		{
			'target_name'  : 'copy_binary',
			'type'         : 'none',
			'dependencies' : ['make_directory'],
			'actions'      : [{
				'action_name' : 'Module copied.',
				'inputs'      : [],
				'outputs'     : ['binary'],
				'action'      : ['<(cp)', 'build/Release/webgl.node', '<(binary)/webgl.node'],
			}],
		},
		{
			'target_name'  : 'remove_extras',
			'type'         : 'none',
			'dependencies' : ['copy_binary'],
			'actions'      : [{
				'action_name' : 'Build intermediates removed.',
				'inputs'      : [],
				'outputs'     : ['cpp'],
				'conditions'  : [[
					# IF WINDOWS
					'OS=="win"',
					{ 'action' : [
						'<(rm)',
						'<(module_root_dir)/build/Release/webgl.*',
						'<(module_root_dir)/build/Release/obj/webgl/*.*'
					] },
					# ELSE
					{ 'action' : [
						'<(rm)',
						'<(module_root_dir)/build/Release/obj.target/webgl/cpp/bindings.o',
						'<(module_root_dir)/build/Release/obj.target/webgl/cpp/webgl.o',
						'<(module_root_dir)/build/Release/webgl.node'
					] }
				]],
			}],
		},
	]
}
