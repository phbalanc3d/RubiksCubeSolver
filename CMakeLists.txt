cmake_minimum_required(VERSION 3.15)
project(cube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Point to OpenCV installation
set(OpenCV_DIR "C:/opencv/build")

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your source files here
add_executable(RubiksCubeSolver
    main.cpp
    # add other .cpp files here as you create them
)

# Link OpenCV to your project
target_link_libraries(RubiksCubeSolver ${OpenCV_LIBS})