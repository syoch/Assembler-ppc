project('tiny-assembler', 'cpp',
  version : '1.0.0',
  license : 'MIT')

install_headers('asm.h')

import('pkgconfig').generate(
  libraries : shared_library(
    'tinyassembler',
    ['asm.cpp'],
    include_directories : include_directories('.'),
    dependencies : [
      dependency('glib-2.0'),
      dependency('tinyutil'),
    ],
    install : true
  ),
  name: 'tinyasm',
  version : '1.0',
  description : 'A Tiny Assembler library'
)