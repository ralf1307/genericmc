qrc_resources = []  

subdir('OSX')
qrc_resources += qrc_resources_OSX

subdir('backgrounds')
qrc_resources += qrc_resources_backgrounds

subdir('documents')
qrc_resources += qrc_resources_documents

subdir('flat')
qrc_resources += qrc_resources_flat

subdir('genericmc')
qrc_resources += qrc_resources_genericmc

subdir('iOS')
qrc_resources += qrc_resources_iOS

subdir('pe_blue')
qrc_resources += qrc_resources_pe_blue

subdir('pe_colored')
qrc_resources += qrc_resources_pe_colored

subdir('pe_dark')
qrc_resources += qrc_resources_pe_dark

subdir('pe_light')
qrc_resources += qrc_resources_pe_light

#  'GenericMC.icns',
#  'GenericMC.ico',
#  'GenericMC.manifest',
#  'assets',
#  'genericmc.rc',

src_resources = []
src_resources += qt.compile_resources(
  sources: qrc_resources
  )
