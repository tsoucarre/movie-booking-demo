add_executable(booking_tests
    TheaterTests.h
    TheaterTests.cpp
    main.cpp
)

target_link_libraries(booking_tests
    PRIVATE
        booking_core
        Qt6::Concurrent
        Qt6::Test
)

add_test(
    NAME booking_tests
    COMMAND booking_tests
)
