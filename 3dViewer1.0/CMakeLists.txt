cmake_minimum_required(VERSION 3.5)

project(gpt_help VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)


set(PROJECT_SOURCES
        ./parser/parser.c
        ./parser/parser.h
        ./gifmaker/dgif_lib.c
        ./gifmaker/egif_lib.c
        ./gifmaker/gif_err.c
        ./gifmaker/gif_font.c
        ./gifmaker/gif_hash.c
        ./gifmaker/gif_hash.h
        ./gifmaker/gif_lib_private.h
        ./gifmaker/gif_lib.h
        ./gifmaker/gifalloc.c
        ./gifmaker/qgifglobal.h
        ./gifmaker/qgifimage_p.h
        ./gifmaker/qgifimage.h
        ./gifmaker/qgifimage.cpp
        ./gifmaker/quantize.c
        main.cpp
        widget.cpp
        widget.h
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(gpt_help
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET gpt_help APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(gpt_help SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(gpt_help
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(gpt_help PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(gpt_help PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)

set_target_properties(gpt_help PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(gpt_help)
endif()
