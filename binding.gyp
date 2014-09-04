{
  'variables': {
    'platform': '<(OS)',
  },
  'conditions': [
    # Replace gyp platform with node platform, blech
    ['platform == "mac"', {'variables': {'platform': 'darwin'}}],
    ['platform == "win"', {'variables': {'platform': 'win32'}}],
  ],
  'targets': [
    {
      'target_name': 'webgl',
      'defines': [
        'VERSION=0.4.3'
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
      'library_dirs': [
        '<(module_root_dir)/deps/<(platform)',
      ],
      'conditions': [
        ['OS=="mac"', {
          'libraries': ['-lGLEW','-lfreeimage','-framework OpenGL']}],
        ['OS=="linux"', {'libraries': ['-lfreeimage','-lGLEW','-lGL']}],
        ['OS=="win"', {
          'libraries': [
            'freeimage64.lib','glew64s.lib','opengl32.lib'
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
