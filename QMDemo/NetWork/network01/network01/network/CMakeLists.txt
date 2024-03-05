qt_add_library(network STATIC
    tcpclient.cpp
    tcpclient.h
    queue.h
)

target_link_libraries(network PRIVATE Qt6::Network)
target_include_directories(network INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

