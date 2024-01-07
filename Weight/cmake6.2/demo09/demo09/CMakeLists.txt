cmake_minimum_required(VERSION 3.5)

project(demo02 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets Core)
qt_standard_project_setup()
include_directories(E:\\ffmpeg-6.1-full_build-shared\\include)
link_directories(E:\\ffmpeg-6.1-full_build-shared\\lib)

add_subdirectory(thread)

qt_add_executable(demo02
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        opengl_widget.h opengl_widget.cpp
        media.h media.cpp
        res.qrc
)

target_link_libraries(demo02 PRIVATE Qt6::Widgets
    Qt6::OpenGLWidgets
    Qt6::Core
    worker
    avformat.lib
    avcodec.lib
    avutil.lib
    swscale.lib)

set_target_properties(demo02 PROPERTIES
     WIN32_EXECUTABLE ON
     MACOSX_BUNDLE ON
)
