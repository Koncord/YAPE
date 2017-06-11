project(plugin_baseio)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Beeper.cpp Display.cpp BeeperControl.cpp DeviceController.cpp)
set(HEADER_FILES Beeper.hpp Display.hpp BeeperControl.hpp DeviceController.hpp)

if(OPTION_GNU_LTO)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto")
    message(STATUS "LTO enabled.")
endif(OPTION_GNU_LTO)

add_library(plugin_baseio SHARED ${SOURCE_FILES} ${HEADER_FILES} )

target_link_libraries(plugin_baseio ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} deviceapi components)

# Fix for not visible pthreads functions for linker with glibc 2.15
if (UNIX AND NOT APPLE)
    target_link_libraries(plugin_baseio ${CMAKE_THREAD_LIBS_INIT})
endif()
