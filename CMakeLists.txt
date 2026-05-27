cmake_minimum_required(VERSION 3.15)
project(cube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# OpenCV
set(OPENCV_INCLUDE "C:/opencv/build/include")
set(OPENCV_LIB "C:/opencv/build/x64/vc16/lib/opencv_world4100.lib")

add_executable(scanner
    scanner/main.cpp
    scanner/CubeScanner.cpp
    models/cube.cpp
    models/cubeBitboard.cpp
    patternDatabase/patternDatabase.cpp
    patternDatabase/nibbleArray.cpp
    patternDatabase/CornerPatternDatabase.cpp
    patternDatabase/math.cpp
)

target_include_directories(scanner PRIVATE ${OPENCV_INCLUDE} ${CMAKE_SOURCE_DIR})

target_link_libraries(scanner ${OPENCV_LIB})