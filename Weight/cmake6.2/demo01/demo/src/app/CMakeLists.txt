qt_add_executable(demo
    widget.ui
    widget.cpp
    widget.h
    main.cpp
)

target_link_libraries(demo PRIVATE worker Qt6::Widgets)

set_target_properties(demo PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
