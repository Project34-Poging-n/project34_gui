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
    headers/homescreen.hpp
)

# Define all cxx files in the project
set(SOURCE_FILES src/main.cpp)
set(SERIAL_FILES src/serial.cpp)
set(GUI_FILES src/homescreen.cpp)

# Configure GTK+
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

# Generate library files for the serial interface
add_library(serialInterface STATIC ${SERIAL_FILES})
target_include_directories(serialInterface PUBLIC headers)
include_directories(${GTKMM_INCLUDE_DIRS})

# Generate library files for the gui
add_library(guiInterface STATIC ${GUI_FILES})
target_include_directories(guiInterface PUBLIC headers)
include_directories(${GTKMM_INCLUDE_DIRS})

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
add_definitions (${GTKMM_CFLAGS_OTHER})
target_link_libraries(${PROJECT_NAME} PRIVATE serialInterface)
target_link_libraries(${PROJECT_NAME} PRIVATE guiInterface)
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTKMM_LIBRARIES})