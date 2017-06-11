set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}")

option(BUILD_PLUGIN_BASEIO "Build plugin BaseIO" ON)
option(BUILD_PLUGIN_IDE "Build plugin IDE" ON)

if (BUILD_PLUGIN_BASEIO)
    add_subdirectory( plugin_baseIO )
endif()

if (BUILD_PLUGIN_IDE)
    add_subdirectory( plugin_ide )
endif()