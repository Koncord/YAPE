set(FONTEDITOR_UI
        ${CMAKE_SOURCE_DIR}/files/ui/FontEditor.ui
        ${CMAKE_SOURCE_DIR}/files/ui/SymbolSelector.ui
)
set(FONTEDITOR_SOURCE
        main.cpp
        FontEditor.cpp
        SymbolSelector.cpp
        FontModel.cpp
        Canvas.cpp
)

set(FONTEDITOR_HEADER_MOC
        FontEditor.hpp
        SymbolSelector.hpp
        FontModel.hpp
        Canvas.hpp
)

set(FONTEDITOR_HEADER
        ${FONTEDITOR_HEADER_MOC}
)

source_group(fonteditor FILES ${FONTEDITOR_SOURCE} ${FONTEDITOR_HEADER})

set(QT_USE_QTGUI 1)
#qt5_add_resources(FONTEDITOR_RCC_SRCS ${CMAKE_SOURCE_DIR}/files/fonteditor/fonteditor.qrc)
qt5_wrap_ui(FONTEDITOR_UI_HEADERS ${FONTEDITOR_UI})
qt5_wrap_cpp(FONTEDITOR_MOC_SRCS ${FONTEDITOR_HEADER_MOC})

include_directories(${CMAKE_CURRENT_BINARY_DIR}) # for find ui_*.h files in building directory

add_executable(fonteditor
        ${FONTEDITOR_SOURCE}
        ${FONTEDITOR_HEADER}
        ${FONTEDITOR_MOC_SRCS}
        ${FONTEDITOR_RCC_SRCS}
        ${FONTEDITOR_UI_HEADERS}
)

target_link_libraries(fonteditor components)

# Use the Widgets and Core module from Qt 5.
if (${CMAKE_MAJOR_VERSION} LESS 3)
    qt5_use_modules(fonteditor Widgets Core)
else()
    target_link_libraries(fonteditor Qt5::Widgets Qt5::Core)
endif()
