qt = import('qt5')
qt_modules = ['Core', 'Xml', 'Network', 'Concurrent', 'Gui']
qt_dep = dependency('qt5', modules: qt_modules)

src_core = files(
  # LOGIC - Base classes and infrastructure
  'BaseInstaller.h',
  'BaseInstaller.cpp',
  'BaseVersionList.h',
  'BaseVersionList.cpp',
  'InstanceList.h',
  'InstanceList.cpp',
  'InstanceTask.h',
  'InstanceTask.cpp',
  'LoggedProcess.h',
  'LoggedProcess.cpp',
  'MessageLevel.cpp',
  'MessageLevel.h',
  'BaseVersion.h',
  'BaseInstance.h',
  'BaseInstance.cpp',
  'NullInstance.h',
  'GMCZip.h',
  'GMCZip.cpp',
  'GMCStrings.h',
  'GMCStrings.cpp',

  # Basic instance manipulation tasks (derived from InstanceTask)
  'InstanceCreationTask.h',
  'InstanceCreationTask.cpp',
  'InstanceCopyTask.h',
  'InstanceCopyTask.cpp',
  'InstanceImportTask.h',
  'InstanceImportTask.cpp',

  # Use tracking separate from memory management
  'Usable.h',

  # Prefix tree where node names are strings between separators
  'SeparatorPrefixTree.h',

  # WARNING: globals live here
  'Env.h',
  'Env.cpp',

  # String filters
  'Filter.h',
  'Filter.cpp',

  # JSON parsing helpers
  'Json.h',
  'Json.cpp',

  'FileSystem.h',
  'FileSystem.cpp',

  'Exception.h',

  # RW lock protected map
  'RWStorage.h',

  # A variable that has an implicit default value and keeps track of changes
  'DefaultVariable.h',

  # a smart pointer wrapper intended for safer use with Qt signal/slot mechanisms
  'QObjectPtr.h',

  # Compression support
  'GZip.h',
  'GZip.cpp',

  # Command line parameter parsing
  'Commandline.h',
  'Commandline.cpp',

  # Version number string support
  'Version.h',
  'Version.cpp',

  # A Recursive file system watcher
  'RecursiveFileSystemWatcher.h',
  'RecursiveFileSystemWatcher.cpp',
  )

subdir('pathmatcher')
subdir('net')
subdir('launch')
subdir('updater')
subdir('notifications')
subdir('news')
subdir('icons')
subdir('minecraft')
subdir('screenshots')
subdir('tasks')
subdir('settings')
subdir('java')
subdir('translations')
subdir('tools')
subdir('meta')
subdir('modplatform')


src_genericmc = files(
  # Application base
  'GenericMC.h',
  'GenericMC.cpp',
  'UpdateController.cpp',
  'UpdateController.h',

  # GUI - general utilities
  'DesktopServices.h',
  'DesktopServices.cpp',
  'GuiUtil.h',
  'GuiUtil.cpp',
  'ColumnResizer.h',
  'ColumnResizer.cpp',
  'InstanceProxyModel.h',
  'InstanceProxyModel.cpp',
  'VersionProxyModel.h',
  'VersionProxyModel.cpp',
  'ColorCache.h',
  'ColorCache.cpp',
  'HoeDown.h',

  # Super secret!
  'KonamiCode.h',
  'KonamiCode.cpp',

  # GUI - windows
  'MainWindow.h',
  'MainWindow.cpp',
  'InstanceWindow.h',
  'InstanceWindow.cpp',

  # FIXME: maybe find a better home for this.
  'SkinUtils.cpp',
  'SkinUtils.h',

  # Processes
  'LaunchController.h',
  'LaunchController.cpp',

  # page provider for instances
  'InstancePageProvider.h',

  # Common java checking UI
  'JavaCommon.h',
  'JavaCommon.cpp',
  )

subdir('icons')
subdir('pagedialog')
subdir('setupwizard')
subdir('themes')
subdir('pages')
subdir('dialogs')
subdir('pagedialog')
subdir('widgets')
subdir('groupview')
subdir('resources')

src = []
qt.compile_ui()
qt.compile_moc()
qt.compile_translations()
