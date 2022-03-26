project('iconfix', 'cpp')

qt = import('qt5')
qt_modules = ['Core', 'Widgets']
qt_dep = dependency('qt5', modules: qt_modules)

src = [
'xdgicon.cpp',
  ]

inc_dir = include_directories('include')
moc_srch = [
  'internal/qhexstring_p.h',
  'internal/qiconloader_p.h',
  ]
moc_src = [
  'internal/qiconloader.cpp'
  ]
src += qt.compile_moc(
sources: moc_src,
headers: moc_srch,
dependencies: qt_dep,
)

iconfix_lib_static = static_library('iconfix',
  sources: src,
  dependencies: qt_dep,
  include_directories: inc_dir,
  )

iconfix_dep = declare_dependency(
  link_with: iconfix_lib_static,
  include_directories: inc_dir
  )
