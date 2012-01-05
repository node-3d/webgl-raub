from os import popen
import sys

srcdir = '.'
blddir = 'build'
VERSION = '0.0.0'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')


def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = "webgl"
  obj.cxxflags = ["-pthread", "-Wall"]

  if sys.platform.startswith('darwin'):
    obj.includes = ["/opt/local/include"]
    obj.libpath = ["/opt/local/lib"]
    obj.linkflags = ["-lfreeimage"]
    obj.uselib = ["GL", "GLU", "GLUT"]
    obj.framework = ['OpenGL','GLUT','Cocoa']
  elif sys.platform.startswith('linux'):
    obj.uselib = ["GL", "FREEIMAGE"]
    obj.linkflags = ["-lGL", "-lfreeimage"]
  else:
    obj.linkflags = ["-lGLESv2"]

  obj.source = bld.path.ant_glob('src/*.cc')
