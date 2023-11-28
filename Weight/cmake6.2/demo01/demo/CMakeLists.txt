cmake_minimum_required(VERSION 3.16)

project(demo VERSION 1.0.0 LANGUAGES CXX)

# 元对象编译
set(CMAKE_AUTOMOC ON)
# 资源文件编译
set(CMAKE_AUTORCC ON)
# ui文件编译
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_subdirectory(src/app)
add_subdirectory(src/thread)




