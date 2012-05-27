{
  'targets': [
    {
      'target_name': 'webgl',
      'defines': [
        'VERSION=0.1.1'
      ],
      'sources': [ 
          'src/bindings.cc',
          'src/image.cc',
          'src/webgl.cc',
      ],
      'conditions': [
        ['OS=="mac"', {'libraries': ['-lfreeimage','-framework OpenGL']}],
        ['OS=="linux"', {'libraries': ['-lfreeimage','-lGLEW','-lGL']}],
        ['OS=="win"', {
          'libraries': [
            'freeimage64.lib','glew64s.lib','opengl32.lib'
            ],
          'defines' : [
            'WIN32_LEAN_AND_MEAN',
            'VC_EXTRALEAN'
          ]
          }
        ],
      ],
    }
  ]
}
