cmake_minimum_required(VERSION 3.25.1)

# Projectname
project(project34_gui VERSION 1.0)

# Set standard compiler to g++
set(CMAKE_MAKE_PROGRAM make FORCE)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

# Set standard C++ version to C++14
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Include header files
set(HEADER_FILES 
    headers/serial.hpp
    headers/homescreen.hpp
    headers/window.hpp
    headers/loginscreen.hpp
    headers/saldoscreen.hpp
    headers/checkoutscreen.hpp
    headers/slowcheckoutscreen.hpp
)

# Define all cxx files in the project
set(SOURCE_FILES src/main.cpp)
set(SERIAL_FILES src/serial.cpp)

# Define all cxx files for the gui library
set(GUI_FILES  
    src/screen/homescreen.cpp
    src/screen/loginscreen.cpp
    src/screen/saldoscreen.cpp
    src/screen/checkoutscreen.cpp
    src/screen/slowcheckoutscreen.cpp
    src/window.cpp
)

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