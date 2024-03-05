qt_add_library(thread STATIC
    ThreadWorkerControl.h
)

target_link_libraries(thread PRIVATE Qt6::Core)
target_include_directories(thread PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



