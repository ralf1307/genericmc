project('localpeer', 'cpp')

qt = import('qt5')
qt_modules = ['Core', 'Network']
qt_dep = dependency('qt5', modules: qt_modules)


moc_src = [
'src/LocalPeer.cpp',
]
moc_srch = [
'include/LocalPeer.h',
'src/LockedFile.h',
]

inc = include_directories('include')

src = []

target = target_machine.system()
if target == 'linux'
  moc_src += 'src/LockedFile_unix.cpp'
elif target == 'windows'
  moc_src += 'src/LockedFile_win.cpp'
else
# FIXME(@ralf1307): Check if file exists, otherwise error
  moc_src += 'src/LockedFile_' + target + '.cpp'
endif

src += qt.compile_moc(
sources: moc_src,
headers: moc_srch,
dependencies: qt_dep,
include_directories: inc,
)



localpeer_lib_static = static_library('localpeer',
  sources: src,
  dependencies: qt_dep,
  include_directories: inc,
)

localpeer_dep = declare_dependency(
  link_with: localpeer_lib_static,
  include_directories: inc
  )
