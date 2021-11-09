cmake_minimum_required(VERSION 3.1)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_BUILD_DIR}" IS_IN_SOURCE_BUILD)
if(IS_IN_SOURCE_BUILD)
    message(FATAL_ERROR "You are building GenericMC in-source. Please separate the build tree from the source tree.")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_HOST_SYSTEM_VERSION MATCHES ".*[Mm]icrosoft.*" OR
        CMAKE_HOST_SYSTEM_VERSION MATCHES ".*WSL.*"
    )
        message(FATAL_ERROR "Building GenericMC is not supported in Linux-on-Windows distributions.")
    endif()
endif()

if(WIN32)
    # In Qt 5.1+ we have our own main() function, don't autolink to qtmain on Windows
    cmake_policy(SET CMP0020 OLD)
endif()

project(genericmc)
enable_testing()


##################################### Set CMake options #####################################
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

# Output all executables and shared libs in the main build folder, not in subfolders.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
if(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
endif()
set(CMAKE_JAVA_TARGET_OUTPUT_DIR ${PROJECT_BINARY_DIR}/jars)

######## Set compiler flags ########
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_C_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)
include(GenerateExportHeader)
set(CMAKE_CXX_FLAGS " -Wall -pedantic -Werror -Wno-deprecated-declarations -D_GLIBCXX_USE_CXX11_ABI=0 -fstack-protector-strong --param=ssp-buffer-size=4 -O3 -D_FORTIFY_SOURCE=2 ${CMAKE_CXX_FLAGS}")
if(UNIX AND APPLE)
    set(CMAKE_CXX_FLAGS " -stdlib=libc++ ${CMAKE_CXX_FLAGS}")
endif()
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror=return-type")

##################################### Set Application options #####################################

######## Set version numbers ########
set(GENERICMC_VERSION_MAJOR    0)
set(GENERICMC_VERSION_MINOR    6)
set(GENERICMC_VERSION_HOTFIX   13)

# Build number
set(GENERICMC_VERSION_BUILD -1 CACHE STRING "Build number. -1 for no build number.")

# Build platform.
set(GENERICMC_BUILD_PLATFORM "" CACHE STRING "A short string identifying the platform that this build was built for. Only used by the notification system and to display in the about dialog.")

# The metadata server
set(GENERICMC_META_URL "https://meta.multimc.org/v1/" CACHE STRING "URL to fetch GenericMC's meta files from.")

option(GENERICMC_EMBED_SECRETS "Determines whether to embed secrets. Secrets are separate and non-public." OFF)

#### Check the current Git commit and branch
include(GetGitRevisionDescription)
get_git_head_revision(GENERICMC_GIT_REFSPEC GENERICMC_GIT_COMMIT)

message(STATUS "Git commit: ${GENERICMC_GIT_COMMIT}")
message(STATUS "Git refspec: ${GENERICMC_GIT_REFSPEC}")

set(GENERICMC_RELEASE_VERSION_NAME "${GENERICMC_VERSION_MAJOR}.${GENERICMC_VERSION_MINOR}.${GENERICMC_VERSION_HOTFIX}")

#### Custom target to just print the version.
add_custom_target(version echo "Version: ${GENERICMC_RELEASE_VERSION_NAME}")
add_custom_target(tcversion echo "\\#\\#teamcity[setParameter name=\\'env.GENERICMC_VERSION\\' value=\\'${GENERICMC_RELEASE_VERSION_NAME}\\']")

################################ 3rd Party Libs ################################

# Find the required Qt parts
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Xml REQUIRED)

# The Qt5 cmake files don't provide its install paths, so ask qmake.
include(QMakeQuery)
query_qmake(QT_INSTALL_PLUGINS QT_PLUGINS_DIR)
query_qmake(QT_INSTALL_IMPORTS QT_IMPORTS_DIR)
query_qmake(QT_INSTALL_LIBS QT_LIBS_DIR)
query_qmake(QT_INSTALL_LIBEXECS QT_LIBEXECS_DIR)
query_qmake(QT_HOST_DATA QT_DATA_DIR)
set(QT_MKSPECS_DIR ${QT_DATA_DIR}/mkspecs)

if (Qt5_POSITION_INDEPENDENT_CODE)
    SET(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

####################################### Install layout #######################################

# How to install the build results
set(GENERICMC_LAYOUT "auto" CACHE STRING "The layout for GenericMC installation (auto, win-bundle, lin-bundle, lin-nodeps, lin-system, mac-bundle)")
set_property(CACHE GENERICMC_LAYOUT PROPERTY STRINGS auto win-bundle lin-bundle lin-nodeps lin-system mac-bundle)

if(GENERICMC_LAYOUT STREQUAL "auto")
    if(UNIX AND APPLE)
        set(GENERICMC_LAYOUT_REAL "mac-bundle")
    elseif(UNIX)
        set(GENERICMC_LAYOUT_REAL "lin-system")
    elseif(WIN32)
        set(GENERICMC_LAYOUT_REAL "win-bundle")
    else()
        message(FATAL_ERROR "Cannot choose a sensible install layout for your platform.")
    endif()
else()
    set(GENERICMC_LAYOUT_REAL ${GenericMC_LAYOUT})
endif()

if(GENERICMC_LAYOUT_REAL STREQUAL "mac-bundle")
    set(BINARY_DEST_DIR "genericmc.app/Contents/MacOS")
    set(LIBRARY_DEST_DIR "genericmc.app/Contents/MacOS")
    set(PLUGIN_DEST_DIR "genericmc.app/Contents/MacOS")
    set(RESOURCES_DEST_DIR "genericmc.app/Contents/Resources")
    set(JARS_DEST_DIR "genericmc.app/Contents/MacOS/jars")

    set(BUNDLE_DEST_DIR ".")

    # Apps to bundle
    set(APPS "\${CMAKE_INSTALL_PREFIX}/genericmc.app")

    # Mac bundle settings
    set(MACOSX_BUNDLE_BUNDLE_NAME "GenericMC")
    set(MACOSX_BUNDLE_INFO_STRING "Minecraft launcher and management utility.")
    set(MACOSX_BUNDLE_GUI_IDENTIFIER "de.ralfrachinger.genericmc")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "${GENERICMC_VERSION_MAJOR}.${GENERICMC_VERSION_MINOR}.${GENERICMC_VERSION_HOTFIX}.${GENERICMC_VERSION_BUILD}")
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${GENERICMC_VERSION_MAJOR}.${GENERICMC_VERSION_MINOR}.${GENERICMC_VERSION_HOTFIX}.${GENERICMC_VERSION_BUILD}")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${GENERICMC_VERSION_MAJOR}.${GENERICMC_VERSION_MINOR}.${GENERICMC_VERSION_HOTFIX}.${GENERICMC_VERSION_BUILD}")
    set(MACOSX_BUNDLE_ICON_FILE GenericMC.icns)
    set(MACOSX_BUNDLE_COPYRIGHT "Copyright 2021 Ralf Rachinger & Copyright 2021 GenericMC Contributors & Copyright 2015-2021 MultiMC Contributors")

    # directories to look for dependencies
    set(DIRS ${QT_LIBS_DIR} ${QT_LIBEXECS_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    # install as bundle
    set(INSTALL_BUNDLE "full")

    # Add the icon
    install(FILES launcher/resources/GenericMC.icns DESTINATION ${RESOURCES_DEST_DIR})

elseif(GENERICMC_LAYOUT_REAL STREQUAL "lin-bundle")
    set(BINARY_DEST_DIR "bin")
    set(LIBRARY_DEST_DIR "bin")
    set(PLUGIN_DEST_DIR "plugins")
    set(BUNDLE_DEST_DIR ".")
    set(RESOURCES_DEST_DIR ".")
    set(JARS_DEST_DIR "bin/jars")

    # Apps to bundle
    set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/genericmc")

    # directories to look for dependencies
    set(DIRS ${QT_LIBS_DIR} ${QT_LIBEXECS_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    # install as bundle
    set(INSTALL_BUNDLE "full")

    # Set RPATH
    SET(GENERICMC_BINARY_RPATH "$ORIGIN/")

    # Install basic runner script
    install(PROGRAMS launcher/package/linux/genericmc DESTINATION ${BUNDLE_DEST_DIR})

elseif(GENERICMC_LAYOUT_REAL STREQUAL "lin-nodeps")
    set(BINARY_DEST_DIR "bin")
    set(LIBRARY_DEST_DIR "bin")
    set(PLUGIN_DEST_DIR "plugins")
    set(BUNDLE_DEST_DIR ".")
    set(RESOURCES_DEST_DIR ".")
    set(JARS_DEST_DIR "bin/jars")

    # install as bundle with no dependencies included
    set(INSTALL_BUNDLE "nodeps")

    # Set RPATH
    SET(GENERICMC_BINARY_RPATH "$ORIGIN/")

    # Install basic runner script
    install(PROGRAMS launcher/package/linux/genericmc DESTINATION ${BUNDLE_DEST_DIR})

elseif(GENERICMC_LAYOUT_REAL STREQUAL "lin-system")
    set(GENERICMC_APP_BINARY_NAME "genericmc" CACHE STRING "Name of the genericmc binary")
    set(GENERICMC_BINARY_DEST_DIR "bin" CACHE STRING "Path to the binary directory")
    set(GENERICMC_LIBRARY_DEST_DIR "lib${LIB_SUFFIX}" CACHE STRING "Path to the library directory")
    set(GENERICMC_SHARE_DEST_DIR "share/genericmc" CACHE STRING "Path to the shared data directory")
    set(JARS_DEST_DIR "${GENERICMC_SHARE_DEST_DIR}/jars")

    set(BINARY_DEST_DIR ${GENERICMC_BINARY_DEST_DIR})
    set(LIBRARY_DEST_DIR ${GENERICMC_LIBRARY_DEST_DIR})

    MESSAGE(STATUS "Compiling for linux system with ${GENERICMC_SHARE_DEST_DIR} and GENERICMC_LINUX_DATADIR")
    SET(GENERICMC_APP_BINARY_DEFS "-DGENERICMC_JARS_LOCATION=/usr/${JARS_DEST_DIR}" "-DGENERICMC_LINUX_DATADIR")

    # install as bundle with no dependencies included
    set(INSTALL_BUNDLE "nodeps")

elseif(GENERICMC_LAYOUT_REAL STREQUAL "win-bundle")
    set(BINARY_DEST_DIR ".")
    set(LIBRARY_DEST_DIR ".")
    set(PLUGIN_DEST_DIR ".")
    set(BUNDLE_DEST_DIR ".")
    set(RESOURCES_DEST_DIR ".")
    set(JARS_DEST_DIR "jars")

    # Apps to bundle
    set(APPS "\${CMAKE_INSTALL_PREFIX}/genericmc.exe")

    # directories to look for dependencies
    set(DIRS ${QT_LIBS_DIR} ${QT_LIBEXECS_DIR} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    # install as bundle
    set(INSTALL_BUNDLE "full")
else()
    message(FATAL_ERROR "No sensible install layout set.")
endif()

################################ Included Libs ################################

include(ExternalProject)
set_directory_properties(PROPERTIES EP_BASE External)

option(NBT_BUILD_SHARED "Build NBT shared library" ON)
option(NBT_USE_ZLIB "Build NBT library with zlib support" OFF)
option(NBT_BUILD_TESTS "Build NBT library tests" OFF) #FIXME: fix unit tests.
set(NBT_NAME GenericMC_nbt++)
set(NBT_DEST_DIR ${LIBRARY_DEST_DIR})
add_subdirectory(libraries/libnbtplusplus)

add_subdirectory(libraries/systeminfo) # system information library
add_subdirectory(libraries/hoedown) # markdown parser
add_subdirectory(libraries/launcher) # java based launcher part for Minecraft
add_subdirectory(libraries/javacheck) # java compatibility checker
add_subdirectory(libraries/xz-embedded) # xz compression
add_subdirectory(libraries/quazip) # zip manipulation library
add_subdirectory(libraries/rainbow) # Qt extension for colors
add_subdirectory(libraries/iconfix) # fork of Qt's QIcon loader
add_subdirectory(libraries/LocalPeer) # fork of a library from Qt solutions
add_subdirectory(libraries/classparser) # google analytics library
add_subdirectory(libraries/optional-bare)
add_subdirectory(libraries/tomlc99) # toml parser
add_subdirectory(libraries/katabasis) # An OAuth2 library that tried to do too much

############################### Built Artifacts ###############################

add_subdirectory(buildconfig)

if(GENERICMC_EMBED_SECRETS)
    add_subdirectory(secrets)
else()
    add_subdirectory(notsecrets)
endif()


# NOTE: this must always be last to appease the CMake deity of quirky install command evaluation order.
add_subdirectory(launcher)
