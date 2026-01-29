add_library(booking_core
    service/BookingService.cpp
)

target_include_directories(booking_core
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(booking_core
    PUBLIC ${QT_CORE_LIB}
)

add_executable(booking_cli
    cli/main.cpp
)

target_link_libraries(booking_cli
    PRIVATE booking_core
)
