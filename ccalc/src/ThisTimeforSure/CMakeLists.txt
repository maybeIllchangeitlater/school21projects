cmake_minimum_required(VERSION 3.5)

project(ThisTimeforSure VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR}PrintSupport)


set(PROJECT_SOURCES
        ../s21_to_curva.h
        ../s21_to_curva.c
        ../s21_calculate.c
        ../s21_stack.c
        ../s21_creditcalc.c
        ../s21_deposit_calc.c
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        qcustomplot.cpp
        qcustomplot.h
        anotherwindow.h
        anotherwindow.cpp
        anotherwindow.ui
        creditwindow.h
        creditwindow.cpp
        creditwindow.ui
        depositcalc.h
        depositcalc.cpp
        depositcalc.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ThisTimeforSure
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ThisTimeforSure APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ThisTimeforSure SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ThisTimeforSure
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ThisTimeforSure PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(ThisTimeforSure PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(ThisTimeforSure PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ThisTimeforSure)
endif()
