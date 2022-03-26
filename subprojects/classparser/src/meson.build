moc_src = [
'classparser.cpp',
'annotations.cpp',
]

# Private headers
moc_srch = [
'annotations.h',
'classfile.h',
'constants.h',
'errors.h',
'javaendian.h',
'membuffer.h',
]

src = []

src += qt.compile_moc(
sources: moc_src,
headers: moc_srch,
dependencies: qt_dep,
include_directories: inc_dir,
)

classparser_lib_static = static_library('classparser',
  dependencies: qt_dep,
  sources: src,
  include_directories: inc_dir
  )
