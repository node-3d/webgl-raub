{
	'variables': {
		'platform' : '<(OS)',
		'variant'  : 'default',
		'bcm_host' : '<!(node -e "console.log(+require(\\"fs\\").existsSync(\\"/opt/vc/include/bcm_host.h\\"))")',
		'opengl_root'   : '<!(node -e "console.log(require(\'node-deps-opengl-raub\').root)")',
		'opengl_include': '<(opengl_root)/include',
		'opengl_bin'    : '<!(node -e "console.log(require(\'node-deps-opengl-raub\').bin)")',
	},
	'conditions': [
		# Replace gyp platform with node platform, blech
		['platform == "mac"', {'variables': {'platform': 'darwin'}}],
		['platform == "win"', {'variables': {'platform': 'win32'}}],
		# Detect Raspberry PI
		['platform == "linux" and target_arch=="arm" and bcm_host==1', {'variables': {'variant': 'raspberry'}}],
	],
	'targets': [
		{
			'target_name': 'webgl',
			'defines': [ 'VERSION=0.5.5' ],
			'sources': [
				'src/bindings.cc',
				'src/image.cc',
				'src/webgl.cc',
			],
			'include_dirs': [
				"<!(node -e \"require('nan')\")",
				'<(opengl_include)',
			],
			'library_dirs': [ '<(opengl_bin)' ],
			'conditions': [
				[
					'OS=="mac"',
					{
						'libraries': ['-lGLEW','-lfreeimage','-framework OpenGL'],
						'include_dirs': ['/usr/local/include'],
						'library_dirs': ['/usr/local/lib'],
					}
				],
				[
					'OS=="linux" and variant=="default"',
					{
						'libraries': [ '-lfreeimage','-lGLEW','-lGL' ]
					}
				],
				[
					'OS=="linux" and variant=="raspberry"',
					{
						'library_dirs': ['/opt/vc/lib/'],
						'include_dirs': ['/opt/vc/include/'],
						'libraries': ['-lfreeimage','-lGLESv2'],
						'defines': ['__RASPBERRY__'],
					}
				],
				[
					'OS=="win"',
					{
						'libraries': [ 'FreeImage.lib', 'glfw3dll.lib', 'glew32.lib', 'opengl32.lib' ],
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
			'target_name'  : 'copy_binary',
			'type'         : 'none',
			'dependencies' : ['webgl'],
			'message'      : 'Copying the addon into the platform-specific directory.',
			'copies'       : [
				{
					'destination' : '<(module_root_dir)/bin_<(platform)',
					'conditions'  : [
						[
							'OS=="linux"',
							{ 'files' : [] }
						],
						[
							'OS=="mac"',
							{ 'files' : [] }
						],
						[
							'OS=="win"',
							{ 'files' : [ '<(module_root_dir)/build/Release/webgl.node' ] },
						],
					]
				}
			],
		},
		
		{
			'target_name'  : 'remove_temporaries',
			'type'         : 'none',
			'dependencies' : ['copy_binary'],
			'message'      : 'Removing temporary files.',
			'actions'      : [
				{
					'action_name' : 'action_remove1',
					'inputs'      : ['build/Release/webgl.*'],
					'outputs'     : ['build'],
					'conditions'  : [
						[ 'OS=="linux"', { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="mac"'  , { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="win"'  , { 'action' : [ '<(module_root_dir)/_del', '<@(_inputs)' ] } ],
					],
				},
				{
					'action_name' : 'action_remove2',
					'inputs'      : ['build/Release/obj/webgl/*.obj'],
					'outputs'     : ['build'],
					'conditions'  : [
						[ 'OS=="linux"', { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="mac"'  , { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="win"'  , { 'action' : [ '<(module_root_dir)/_del', '<@(_inputs)' ] } ],
					],
				},
				{
					'action_name' : 'action_remove3',
					'inputs'      : ['build/Release/obj/webgl/*.pdb'],
					'outputs'     : ['build'],
					'conditions'  : [
						[ 'OS=="linux"', { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="mac"'  , { 'action' : [ 'rm -rf <@(_inputs)' ] } ],
						[ 'OS=="win"'  , { 'action' : [ '<(module_root_dir)/_del', '<@(_inputs)' ] } ],
					],
				},
			],
		},
	]
}
