cmake_minimum_required(VERSION 3.16)

project(demo02 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)
qt_standard_project_setup()

qt_add_executable(demo02
    mainwindow.ui
    mainwindow.h
    mainwindow.cpp
    main.cpp
    opengl_widget.h opengl_widget.cpp
    res.qrc
    fragment.frag
    vertex.vert
)

target_link_libraries(demo02 PRIVATE Qt6::Widgets
    Qt6::OpenGLWidgets)

set_target_properties(demo02 PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
