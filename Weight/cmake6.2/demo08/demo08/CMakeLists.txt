cmake_minimum_required(VERSION 3.16)
project(DEMO01 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(E:\\ffmpeg-6.1-full_build-shared\\include)
link_directories(E:\\ffmpeg-6.1-full_build-shared\\lib)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core GUi)
qt_standard_project_setup()
add_subdirectory(thread)

qt_add_executable(helloworld
    widget.ui
    widget.cpp
    widget.h
    main.cpp
    media.h media.cpp
    ffmpeg_widget.h ffmpeg_widget.cpp


)

target_link_libraries(helloworld PRIVATE Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    worker
    avformat.lib
    avcodec.lib
    avutil.lib
    swscale.lib)

 set_target_properties(helloworld PROPERTIES
     WIN32_EXECUTABLE ON
     MACOSX_BUNDLE ON
 )
