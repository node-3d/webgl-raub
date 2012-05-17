{
  'targets': [
    {
      'target_name': 'node-webgl',
      'defines': [
        'VERSION=0.1.1'
      ],
      'sources': [ 
          'src/bindings.cc',
          'src/image.cc',
          'src/webgl.cc',
      ],
      'conditions': [
        ['OS=="mac"', {'libraries': ['-framework OpenGL']}],
      ],
      'libraries': [
        '-lfreeimage',
      ],
    }
  ]
}
