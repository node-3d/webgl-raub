{
	'variables': {
		'platform' : '<(OS)',
		'variant'  : 'default',
		'bcm_host' : '<!(node -e "console.log(+require(\\"fs\\").existsSync(\\"/opt/vc/include/bcm_host.h\\"))")',
		'deps_root': '<!(node -e "console.log(require(\'node-deps-opengl-raub\'))")',
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
				'<(deps_root)/include',
			],
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
						'library_dirs': [ '<(deps_root)/bin_<(platform)' ],
						'libraries': [
							'glew32.lib',
							'opengl32.lib',
							'FreeImage.lib'
						],
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
			'target_name': 'copy_binary',
			'type':'none',
			'dependencies' : ['webgl'],
			'conditions': [
				[
					'OS=="linux"',
					{
						'copies': [
							{
								'destination': '<(module_root_dir)/bin_linux',
								'files': [
									'<(module_root_dir)/build/Release/webgl.node',
								]
							}
						]
					}
				],
				[
					'OS=="mac"',
					{
						'copies': [
							{
								'destination': '<(module_root_dir)/bin_darwin',
								'files': [
									'<(module_root_dir)/build/Release/webgl.node',
								]
							}
						]
					}
				],
				[
					'OS=="win"',
					{
						'copies': [
							{
								'destination': '<(module_root_dir)/bin_win32',
								'files': [
									'<(module_root_dir)/build/Release/webgl.node',
									'<(deps_root)/bin_<(platform)/FreeImage.dll',
									'<(deps_root)/bin_<(platform)/glew32.dll',
								]
							}
						]
					},
				],
				
			],
			
		}
	]
}
