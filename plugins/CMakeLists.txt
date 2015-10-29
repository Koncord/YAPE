set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PLUGIN_OUTPUT_PATH}")

option(BUILD_PLUGIN_BASEIO "Build plugin BaseIO" ON)

if (BUILD_PLUGIN_BASEIO)
    add_subdirectory( plugin_baseIO )
endif()
