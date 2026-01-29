cmake_minimum_required(VERSION 3.30)

project(MovieBookingService
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 QUIET COMPONENTS Core Test)
message(STATUS "Qt6_FOUND = ${Qt6_FOUND}")
message(STATUS "Qt6_DIR   = ${Qt6_DIR}")

set(QT_CORE_LIB Qt6::Core)
set(QT_TEST_LIB Qt6::Test)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
