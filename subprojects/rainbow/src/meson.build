qt = import('qt5')
qt_modules = ['Core', 'Gui']
qt_dep = dependency('qt5', modules: qt_modules)

src = [
  'rainbow.cpp'
]

rainbow_lib = library('rainbow',
  sources: src,
  dependencies: qt_dep,
  include_directories: inc_dir,
  )

rainbow_dep = declare_dependency(
  link_with: rainbow_lib,
  include_directories: inc_dir
)

