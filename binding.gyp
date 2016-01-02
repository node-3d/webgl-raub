{
  'variables': {
    'platform': '<(OS)',
    'variant': 'default',
    'bcm_host': '<!(test ! -e /opt/vc/include/bcm_host.h ; echo $?)',
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
      'defines': [
        'VERSION=0.5.5'
      ],
      'sources': [
          'src/bindings.cc',
          'src/image.cc',
          'src/webgl.cc',
      ],
      'include_dirs': [
        "<!(node -e \"require('nan')\")",
        '<(module_root_dir)/deps/include',
      ],
      'conditions': [
        ['OS=="mac"',
          {
            'libraries': ['-lGLEW','-lfreeimage','-framework OpenGL'],
            'include_dirs': ['/usr/local/include'],
            'library_dirs': ['/usr/local/lib'],
          }
        ],
        ['OS=="linux" and variant=="default"', {
          'libraries': [
            '-lfreeimage','-lGLEW','-lGL']
          }
        ],
        ['OS=="linux" and variant=="raspberry"',
          {
            'library_dirs': ['/opt/vc/lib/'],
            'include_dirs': ['/opt/vc/include/'],
            'libraries': ['-lfreeimage','-lGLESv2'],
            'defines': ['__RASPBERRY__'],
          }
        ],
        ['OS=="win"',
          {
            'include_dirs': [
              './deps/include',
              ],
            'library_dirs': [
              './deps/windows/lib/<(target_arch)',
              ],
            'libraries': [
              'glew32.lib',
              'opengl32.lib',
              'FreeImage.lib'
              ],
            'defines' : [
              'WIN32_LEAN_AND_MEAN',
              'VC_EXTRALEAN'
            ],
            'msvs_settings' : {
              'VCCLCompilerTool' : {
                'AdditionalOptions' : ['/O2','/Oy','/GL','/GF','/Gm-','/EHsc','/MT','/GS','/Gy','/GR-','/Gd']
              },
              'VCLinkerTool' : {
                'AdditionalOptions' : ['/OPT:REF','/OPT:ICF','/LTCG']
              },
            },
          }
        ],
      ],
    }
  ]
}
