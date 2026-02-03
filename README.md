# Movie Booking Demo

A simple, movie seat booking system implemented in **C++17** using the **Qt 6 framework**.  

## Prerequisites

- **CMake ≥ 3.30**
- **Qt 6**
- A C++17-compatible compiler

## How to build the project

The project buildsystem is based on **CMake**

### Command line

```bash
 - mkdir build
 - cd build
 - cmake ..
 - cmake --build . --config [Debug / Release]
 ```

### Using an IDE
You can also open the project in any IDE supporting CMake
(e.g. Qt Creator, Visual Studio, VSCode, ...) and build it from there.
 
## How to run the tests

You can run the tests using ctest:   
`ctest -C [Debug / Release]`  
Or you can run the booking_tests executable.

## How to run the demo
Simply run the demo executable: `./build/demo/Release/demo.exe`

 - Two combo boxes to select **Movie** and **Theater**
 - The theater list updates based on the selected movie
 - A table view represents theater seats:
   - 🔴 Red = already booked
   - 🟢 Green = available
 - Multiple seats can be selected using **Ctrl + Click**
 - Click **“Book Selected Seats”** to submit the booking request

## How to build the documentation

The project documentation requires **doxygen**.
```bash
doxygen Doxyfile
```
The html doc will be generated in docs/html/index.html

## Improvements ideas

The booking service could be turned into a server executable using **Qt Remote Objects**, allowing multiple clients to connect the same service.