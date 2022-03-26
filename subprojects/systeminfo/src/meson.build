src = [
'distroutils.cpp'
]

target = target_machine.system()
if target == 'linux'
  src += 'sys_unix.cpp'
elif target == 'windows'
  src += 'sys_win32.cpp'
else
# FIXME(@ralf1307): Check if file exists, otherwise error
  src += 'sys_' + target + '.cpp'
endif

systeminfo_lib_static = static_library('systeminfo',
  sources: src,
  dependencies: qt_dep,
  include_directories: systeminfo_inc,
)

systeminfo_dep = declare_dependency(
  link_with: systeminfo_lib_static,
  include_directories: systeminfo_inc
  )

systeminfo_test = executable('systeminfo_test', 
  sources: 'sys_test.cpp', 
  link_with: systeminfo_lib_static
  )
test('Test systeminfo', systeminfo_test)

