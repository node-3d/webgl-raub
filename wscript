from os import popen
import sys

srcdir = '.'
blddir = 'build'
VERSION = '0.1.0'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')

def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = "node_webgl"
  obj.cxxflags = ["-g", "-pthread", "-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE","-fPIC"]

  if sys.platform.startswith('darwin'):
    obj.linkflags = ["-lfreeimage"]
    obj.framework = ['OpenGL']
  elif sys.platform.startswith('linux'):
    obj.uselib = ["GL", "FREEIMAGE"]
    obj.linkflags = ["-lGL", "-lfreeimage","-lXrandr","-lX11"]
  else:
    obj.linkflags = ["-lGLESv2"]

  obj.source = bld.path.ant_glob('src/*.cc')
