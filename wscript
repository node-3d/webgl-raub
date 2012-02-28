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
  conf.check(lib=['GLEW'], libpath=['/opt/local/lib'], uselib_store='GLEW')


def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = "node_webgl"
  obj.cxxflags = ["-pthread", "-Wall"]

  if sys.platform.startswith('darwin'):
    obj.includes = ["/opt/local/include"]
    obj.libpath = ["/opt/local/lib"]
    obj.linkflags = ["-lfreeimage"]
    obj.uselib=['GLFW','GLEW']
    obj.framework = ['OpenGL']
  elif sys.platform.startswith('linux'):
    obj.uselib = ["GL", "FREEIMAGE"]
    obj.linkflags = ["-lGL", "-lfreeimage"]
  else:
    obj.linkflags = ["-lGLESv2"]

  obj.source = bld.path.ant_glob('src/*.cc')
