cmake_minimum_required(VERSION 3.1.0)

 project(demo07 VERSION 1.0.0 LANGUAGES CXX)

 set(CMAKE_CXX_STANDARD 11)
 set(CMAKE_CXX_STANDARD_REQUIRED ON)

 set(CMAKE_AUTOMOC ON)
 set(CMAKE_AUTORCC ON)
 set(CMAKE_AUTOUIC ON)

 if(CMAKE_VERSION VERSION_LESS "3.7.0")
     set(CMAKE_INCLUDE_CURRENT_DIR ON)
 endif()

 find_package(Qt5 COMPONENTS Widgets REQUIRED multimedia)

 if(WIN32)
     add_compile_options(/W4)
     add_compile_options(/wd4819)
     add_compile_options(/wd4244)
     add_compile_options(/wd4458)
 endif()

 add_executable(demo07
     widget.ui
     widget.cpp widget.h
     main.cpp
     videowidget.cpp videowidget.h
     Media/audioplay.cpp Media/audioplay.h Media/audiothread.cpp Media/audiothread.h Media/decode.cpp Media/decode.h Media/decodethread.cpp Media/decodethread.h Media/demux.cpp Media/demux.h Media/demuxthread.cpp Media/demuxthread.h Media/resample.cpp Media/resample.h Media/videocall.h Media/videothread.cpp Media/videothread.h

 )

target_include_directories(demo07 PRIVATE "F:\\ffmpeg-6.1.1-full_build-shared\\include")
target_link_directories(demo07 PRIVATE "F:\\ffmpeg-6.1.1-full_build-shared\\lib")

target_link_libraries(demo07 Qt5::Widgets
    Qt5::Multimedia
    avcodec.lib
    avdevice.lib
    avfilter.lib
    avformat.lib
    avutil.lib
    postproc.lib
    swresample.lib
    swscale.lib

)
