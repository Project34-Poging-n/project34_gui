cmake_minimum_required(VERSION 3.25.2)

# Projectname
project(project34_gui VERSION 1.0)

# Set standard compiler to g++
set(CMAKE_CXX_COMPILER g++)

# Set standard C++ version to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include header files
set(HEADER_FILES 
    headers/serial.hpp
)

set(SOURCE_FILES
    src/main.cpp
)

set(LIB_FILES
    src/serial.cpp
)

# Generate library files for the serial interface
add_library(serialInterface STATIC ${LIB_FILES})
target_include_directories(serialInterface PUBLIC headers)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE serialInterface)