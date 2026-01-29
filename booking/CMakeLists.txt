add_library(booking_core
)

target_include_directories(booking_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(booking_core
    PUBLIC Qt6::Core
)
