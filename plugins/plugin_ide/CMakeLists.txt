project(plugin_ide)

set(PLUGIN_IDE_UI
        FormDisplay.ui
        FormEditor.ui
        FormGui.ui
        FormMem.ui
        )
set(PLUGIN_IDE_SOURCE
        main.cpp
        Compiler.cpp
        FormDisplay.cpp
        FormEditor.cpp
        FormGui.cpp
        FormMem.cpp
        )

set(PLUGIN_IDE_HEADER_MOC
        FormDisplay.hpp
        FormEditor.hpp
        FormGui.hpp
        FormMem.hpp
        )

set(PLUGIN_IDE_HEADER
        ${PLUGIN_IDE_HEADER_MOC}
        Compiler.hpp
        )

source_group(fonteditor FILES ${PLUGIN_IDE_SOURCE} ${PLUGIN_IDE_HEADER})

set(QT_USE_QTGUI 1)
qt5_add_resources(PLUGIN_IDE_RCC_SRCS icons.qrc)
qt5_wrap_ui(PLUGIN_IDE_UI_HEADERS ${PLUGIN_IDE_UI})
qt5_wrap_cpp(PLUGIN_IDE_MOC_SRCS ${PLUGIN_IDE_HEADER_MOC})

include_directories(${CMAKE_CURRENT_BINARY_DIR}) # for find ui_*.h files in building directory

add_library(plugin_ide SHARED
        ${PLUGIN_IDE_SOURCE}
        ${PLUGIN_IDE_HEADER}
        ${PLUGIN_IDE_MOC_SRCS}
        ${PLUGIN_IDE_RCC_SRCS}
        ${PLUGIN_IDE_UI_HEADERS}
        )

# Fix for not visible pthreads functions for linker with glibc 2.15
if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
    target_link_libraries(plugin_ide ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(plugin_ide deviceapi components)

# Use the Widgets and Core module from Qt 5.
if (${CMAKE_MAJOR_VERSION} LESS 3)
    qt5_use_modules(plugin_ide Widgets Core)
else()
    target_link_libraries(plugin_ide Qt5::Widgets Qt5::Core)
endif()