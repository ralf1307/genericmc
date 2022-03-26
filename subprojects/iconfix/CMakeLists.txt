cmake_minimum_required(VERSION 3.1)
project(iconfix)

find_package(Qt5Core REQUIRED QUIET)
find_package(Qt5Widgets REQUIRED QUIET)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake/")
include(GenerateExportHeader)

set(ICONFIX_SOURCES
include/xdgicon.h
xdgicon.cpp
internal/qhexstring_p.h
internal/qiconloader.cpp
internal/qiconloader_p.h
)

add_library(GENERICMC_iconfix SHARED ${ICONFIX_SOURCES})
target_include_directories(GENERICMC_iconfix PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}" )

target_link_libraries(GENERICMC_iconfix Qt5::Core Qt5::Widgets)

set_target_properties(GENERICMC_iconfix PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN 1)
generate_export_header(GENERICMC_iconfix)

# Install it
install(
    TARGETS GENERICMC_iconfix
    RUNTIME DESTINATION ${LIBRARY_DEST_DIR}
    LIBRARY DESTINATION ${LIBRARY_DEST_DIR}
)
