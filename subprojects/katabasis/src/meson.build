qt = import('qt5')
qt_modules = ['Core', 'Network']
qt_dep = dependency('qt5', modules: qt_modules)

src = [
'JsonResponse.h',
'JsonResponse.cpp',
]

moc_srch = [
'../include/katabasis/Bits.h',
'../include/katabasis/Globals.h',
'../include/katabasis/OAuth2.h',
'../include/katabasis/PollServer.h',
'../include/katabasis/Reply.h',
'../include/katabasis/ReplyServer.h',
'../include/katabasis/RequestParameter.h',
]

moc_src = [
'OAuth2.cpp',
'PollServer.cpp',
'Reply.cpp',
'ReplyServer.cpp',
]


src += qt.compile_moc(
sources: moc_src,
headers: moc_srch,
dependencies: qt_dep,
)

katabasis_lib = library('katabasis',
  sources: src,
  dependencies: qt_dep,
  include_directories: inc_dir,
  )

katabasis_dep = declare_dependency(
  link_with: katabasis_lib,
  include_directories: inc_dir
)

