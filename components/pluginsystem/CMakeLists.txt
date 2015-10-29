project (DeviceAPI)
cmake_minimum_required(VERSION 2.8)

set (SOURCE_FILES
        DeviceAPI.cpp
)

set (HEADER_FILES
        Functions.hpp
	DeviceAPI.hpp
	Events.hpp
)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" AND NOT APPLE)
        add_definitions(-fPIC)
    endif()
endif ()

add_definitions(-pedantic-errors -pedantic -Wfatal-errors -Wextra -Wall -std=gnu++1y)

add_library(deviceapi STATIC ${SOURCE_FILES} ${HEADER_FILES})
