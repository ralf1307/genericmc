src = [
'autolink.c',
'buffer.c',
'document.c',
'escape.c',
'html.c',
'html_blocks.c',
'html_smartypants.c',
'stack.c',
'version.c',
]

hoedown_lib_static = static_library('hoedown', 
  include_directories: inc_dir,
  sources: src,
  )

hoedown_dep = declare_dependency(
  link_with : hoedown_lib_static,
  include_directories: inc_dir,
  )
