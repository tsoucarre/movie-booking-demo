add_executable(booking_tests
    main.cpp
)

target_link_libraries(booking_tests
    PRIVATE
        booking_core
)

add_test(
    NAME booking_tests
    COMMAND booking_tests
)
