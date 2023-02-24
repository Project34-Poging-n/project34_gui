cmake_minimum_required(VERSION 3.25.2)

# Projectname
project(project34_gui VERSION 1.0)

# Set standard C++ version to C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# Create executable
add_executable(${PROJECT_NAME} src/main.cpp)