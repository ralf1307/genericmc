project('tomlc99', 'c')

tomlc99_inc = include_directories('include')
src = ['src/toml.c']
tomlc99_lib_static = static_library('tomlc99', 
  include_directories: tomlc99_inc,
  sources: src,
  )

tomlc99_dep = declare_dependency(
  link_with : tomlc99_lib_static,
  include_directories: tomlc99_inc,
  )
