qt_add_library(worker STATIC
    THreadPool.cpp
    THreadPool.h
)

target_link_libraries(worker PRIVATE Qt6::Core)
target_include_directories(worker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})












