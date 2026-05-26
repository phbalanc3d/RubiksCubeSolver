cmake_minimum_required(VERSION 3.15)

project(cube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OpenCV path
set(OpenCV_DIR "C:/opencv/build")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Webcam scanner executable
add_executable(scanner
    scanner/main.cpp
)

# Link OpenCV
target_link_libraries(scanner ${OpenCV_LIBS})