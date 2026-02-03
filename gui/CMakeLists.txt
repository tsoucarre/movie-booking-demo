add_library(booking_gui
    include/MovieBookingWidget.h
    include/SeatsModel.h
    MovieBookingWidget.ui
    MovieBookingWidget.cpp
    SeatsModel.cpp
)

target_include_directories(booking_gui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(booking_gui
    PUBLIC
	booking_core
	Qt6::Core
	Qt6::Widgets
)
