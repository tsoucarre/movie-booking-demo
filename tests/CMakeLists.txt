add_executable(booking_tests
    BookingServiceTests.cpp
)

target_link_libraries(booking_tests
    PRIVATE
        booking_core
        ${QT_CORE_LIB}
        ${QT_TEST_LIB}
)
