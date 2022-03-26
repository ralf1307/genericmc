project('genericmc', 'cpp')

cmake = import('cmake')

hoedown_dep = dependency('hoedown', fallback: ['hoedown', 'hoedown_dep'])
libnbtplusplus_proj = cmake.subproject('libnbtplusplus')
libnbtplusplus_dep = libnbtplusplus_proj.dependency('nbt++')
#libnbtplusplus_dep = dependency('libnbtplusplus', fallback : ['libnbtplusplus', 'libnbtplusplus_dep'])
quazip_dep = dependency('quazip', method: 'auto', fallback: ['quazip', 'quazip_dep'])
optional_bare_dep = dependency('optional-bare', fallback: ['optional-bare', 'optional_bare_dep'])
katabasis_dep = dependency('katabasis', fallback: ['katabasis', 'katabasis_dep'])

# Things, that are not packaged most likly
rainbow_dep = dependency('rainbow', fallback: ['rainbow', 'rainbow_dep'])
iconfix_dep = dependency('iconfix', fallback: ['iconfix', 'iconfix_dep'])
localpeer_dep = dependency('localpeer', fallback: ['localpeer', 'localpeer_dep'])
classparser_dep = dependency('classparser', fallback: ['classparser', 'classparser_dep'])
tomlc99_dep = dependency('tomlc99', fallback:['tomlc99', 'tomlc99_dep'])
systeminfo_dep = dependency('systeminfo', fallback: ['systeminfo', 'systeminfo_dep'])
javacheck_dep = dependency('javacheck', fallback: ['javacheck', 'javacheck_dep'])
xz_embedded_proj = cmake.subproject('xz-embedded')
xz_embedded_dep = xz_embedded_proj.dependency('xz-embedded')
#xz_embedded_dep = dependency('xz_embedded', fallback: ['xz_embedded', 'xz_embedded_dep'])
launcher_dep = dependency('launcher_dep', fallback: ['launcher', 'launcher_dep'])

subdir('src')
