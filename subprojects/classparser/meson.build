project('classparser', 'cpp')

qt = import('qt5')
qt_modules = ['Core']
qt_dep = dependency('qt5', modules: qt_modules)

inc_dir = include_directories('include')

subdir('src')

classparser_dep = declare_dependency(
  link_with: classparser_lib_static,
  include_directories: inc_dir
  )
