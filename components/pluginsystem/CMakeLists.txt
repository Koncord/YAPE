project (DeviceAPI)

set (SOURCE_FILES
    private/DeviceAPI.cpp
    private/PipeAPI.cpp
    private/PluginInfo.cpp
)

set (HEADER_FILES
    private/InternalFunc.hpp
    Functions.hpp
	DeviceAPI.hpp
	Events.hpp
    PipeAPI.hpp
    PluginInfo.hpp
)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
        add_definitions(-fPIC)
    endif()
endif ()

add_definitions(-pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=gnu++14)

add_library(deviceapi STATIC ${SOURCE_FILES} ${HEADER_FILES})
