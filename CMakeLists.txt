cmake_minimum_required(VERSION 3.16)

project(calendar VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/database.cpp
    src/eventdialog.cpp
    src/categorydialog.cpp
    src/colorcelldelegate.cpp
    src/categorybadgedelegate.cpp
    src/tagchipdelegate.cpp

    src/mainwindow.h
    src/database.h
    src/eventdialog.h
    src/categorydialog.h
    src/colorcelldelegate.h
    src/categorybadgedelegate.h
    src/tagchipdelegate.h

    src/mainwindow.ui
    src/eventdialog.ui
    src/categorydialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calendar
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(calendar
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(calendar PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

set_target_properties(calendar PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calendar)
endif()
