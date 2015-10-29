project(YAPE)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)
include(Macros)

# Find the Qt librarys
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

# Find the Boost librarys
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.50.0 COMPONENTS filesystem system)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found.")
endif()

if (UNIX AND NOT APPLE)
    find_package (Threads)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")

option(BUILD_PLUGIN_API "Build plugin api library" ON)
option(BUILD_CORE "Build Core" ON)
option(BUILD_FONTEDITOR "Build FontEditor" ON)
option(BUILD_PLUGINS "Build Plugins" ON)
option(BUILD_UNITTESTS "Enable Unittests with Google C++ Testing Framework" OFF)
if (CMAKE_CXX_COMPILER_ID STREQUAL GNU OR CMAKE_CXX_COMPILER_ID STREQUAL Clang)
    option(OPTION_GNU_LTO "Build with Link-Time Optimization" ON)
endif()

set(PLUGIN_OUTPUT_PATH "${YAPE_BINARY_DIR}/plugins")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${YAPE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${YAPE_BINARY_DIR}")

include_directories("." 
	SYSTEM)

add_subdirectory (components)

if (BUILD_CORE)
    add_subdirectory(apps/Core)
endif()

if (BUILD_FONTEDITOR)
    add_subdirectory(apps/FontEditor)
endif()

if (BUILD_PLUGIN_API OR BUILD_PLUGINS)
    add_subdirectory(components/pluginsystem)
endif()

if (BUILD_PLUGINS)
    include_directories(components/pluginsystem)
    add_subdirectory(plugins)
endif()

if (BUILD_UNITTESTS)
    add_subdirectory(apps/test_suite)
endif()
