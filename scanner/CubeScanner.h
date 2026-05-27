#pragma once

#include <opencv2/opencv.hpp>
#include "../models/cube.h"
#include "../models/cubeBitboard.h"

#include <vector>
#include <map>
#include <iostream>

using namespace std;
using namespace cv;

class CubeScanner {

public:

    CubeScanner(int camIndex = 0, int boxSize = 60);

    ~CubeScanner();

    // uses RubiksCubeBitboard specifically since it's your concrete type
    void scanCube(RubiksCubeBitboard& cube);

private:

    VideoCapture cap;

    int boxSize;

    static const map<RubiksCube::Color, Scalar> colorMap;

    RubiksCube::Color classifyColor(const Vec3b& bgr);

    Vec3b medianColor(
        const Mat& frame,
        int centerX,
        int centerY,
        int region = 5
    );

    vector<vector<RubiksCube::Color>> captureFace();

    Mat drawColorFace(
        const vector<vector<RubiksCube::Color>>& faceGrid
    );

    Mat drawFullCube(
        const vector<vector<vector<RubiksCube::Color>>>& cubeGrid
    );
};