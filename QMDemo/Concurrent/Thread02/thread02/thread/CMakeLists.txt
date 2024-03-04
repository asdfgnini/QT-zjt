
qt_add_library(worker STATIC
    worker.cpp
    worker.h
)

target_link_libraries(worker PRIVATE Qt6::Core)
target_include_directories(worker INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
