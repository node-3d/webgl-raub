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
        'VERSION=0.1.4'
      ],
      'sources': [ 
          'src/bindings.cc',
          'src/image.cc',
          'src/webgl.cc',
      ],
      'include_dirs': [
        './deps/include',
      ],
      'library_dirs': [
        './deps/<(platform)',
      ],
      'conditions': [
        ['OS=="mac"', {'libraries': ['-lGLEW','-lfreeimage','-framework OpenGL']}],
        ['OS=="linux"', {'libraries': ['-lfreeimage','-lGLEW','-lGL']}],
        ['OS=="win"', {
          'libraries': [
            'freeimage64.lib','glew64s.lib','opengl32.lib'
            ],
          'defines' : [
            'WIN32_LEAN_AND_MEAN',
            'VC_EXTRALEAN'
          ],
          'cflags' : [
          '/Ox','/Ob2','/Oi','/Ot','/Oy','/GL','/GF','/Gm-','/EHsc','/MT','/GS','/Gy','/GR-','/Gd','/wd"4530"','/wd"4251"' 
          ],
          'ldflags' : [
            '/OPT:REF','/OPT:ICF','/LTCG'
          ]
          }
        ],
      ],
    }
  ]
}
