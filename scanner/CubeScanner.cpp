#include "CubeScanner.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>


using namespace cv;
using namespace std;

inline const map<RubiksCube::Color, Scalar> CubeScanner::colorMap = {
    {RubiksCube::Color::WHITE,  Scalar(255, 255, 255)},
    {RubiksCube::Color::RED,    Scalar(0, 0, 255)},
    {RubiksCube::Color::ORANGE, Scalar(0, 165, 255)},
    {RubiksCube::Color::YELLOW, Scalar(0, 255, 255)},
    {RubiksCube::Color::GREEN,  Scalar(0, 255, 0)},
    {RubiksCube::Color::BLUE,   Scalar(255, 0, 0)}
};

CubeScanner::CubeScanner(int camIndex, int boxSize) : boxSize(boxSize) {
    cap.open(camIndex);
    if (!cap.isOpened()) throw runtime_error("Failed to open webcam");
}

CubeScanner::~CubeScanner() {
    cap.release();
    destroyAllWindows();
}

RubiksCube::Color CubeScanner::classifyColor(const Vec3b& bgr) {
    Mat bgrPixel(1, 1, CV_8UC3, bgr);
    Mat hsvPixel;
    cvtColor(bgrPixel, hsvPixel, COLOR_BGR2HSV);
    Vec3b hsv = hsvPixel.at<Vec3b>(0, 0);
    int h = hsv[0];

    if (
        bgr[2] > 200 && bgr[1] > 200 && bgr[0] > 200 &&
        abs(bgr[2] - bgr[1]) < 30 &&
        abs(bgr[1] - bgr[0]) < 30 &&
        abs(bgr[0] - bgr[2]) < 30
    ) return RubiksCube::Color::WHITE;

    if (h >= 160 && h <= 190) return RubiksCube::Color::RED;
    if (h >= 3   && h <= 19)  return RubiksCube::Color::ORANGE;
    if (h >= 20  && h <= 30)  return RubiksCube::Color::YELLOW;
    if (h >= 60  && h <= 90)  return RubiksCube::Color::GREEN;
    if (h >= 100 && h <= 120) return RubiksCube::Color::BLUE;

    return RubiksCube::Color::WHITE;
}

Vec3b CubeScanner::medianColor(const Mat& frame, int centerX, int centerY, int region) {
    int half = region / 2;
    vector<uchar> B, G, R;
    for (int dy = -half; dy <= half; ++dy)
        for (int dx = -half; dx <= half; ++dx) {
            int x = centerX + dx, y = centerY + dy;
            if (x >= 0 && x < frame.cols && y >= 0 && y < frame.rows) {
                Vec3b bgr = frame.at<Vec3b>(y, x);
                B.push_back(bgr[0]);
                G.push_back(bgr[1]);
                R.push_back(bgr[2]);
            }
        }
    sort(B.begin(), B.end());
    sort(G.begin(), G.end());
    sort(R.begin(), R.end());
    int mid = B.size() / 2;
    return Vec3b(B[mid], G[mid], R[mid]);
}

vector<vector<RubiksCube::Color>> CubeScanner::captureFace() {
    Mat frame;
    int rows, cols;

    while (true) {
        cap >> frame;
        rows = frame.rows;
        cols = frame.cols;
        int startX = (cols - 3 * boxSize) / 2;
        int startY = (rows - 3 * boxSize) / 2;

        for (int i = 0; i <= 3; ++i) {
            line(frame,
                Point(startX, startY + i * boxSize),
                Point(startX + 3 * boxSize, startY + i * boxSize),
                Scalar(255, 255, 255), 2);
            line(frame,
                Point(startX + i * boxSize, startY),
                Point(startX + i * boxSize, startY + 3 * boxSize),
                Scalar(255, 255, 255), 2);
        }

        putText(frame, "Press SPACE to capture", Point(30, 30),
            FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2, LINE_AA);
        imshow("Align Cube Face", frame);
        if (waitKey(30) == 32) break;
    }

    cap >> frame;
    int startX = (cols - 3 * boxSize) / 2;
    int startY = (rows - 3 * boxSize) / 2;

    vector<vector<RubiksCube::Color>> face(3, vector<RubiksCube::Color>(3));
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            int x = startX + j * boxSize + boxSize / 2;
            int y = startY + i * boxSize + boxSize / 2;
            Vec3b bgr = medianColor(frame, x, y);
            face[i][j] = classifyColor(bgr);
        }
    return face;
}

Mat CubeScanner::drawColorFace(const vector<vector<RubiksCube::Color>>& faceGrid) {
    int gridSize = 3 * boxSize;
    int padding = 50;
    Mat result(gridSize + padding, gridSize, CV_8UC3, Scalar(0, 0, 0));

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            Rect box(j * boxSize, i * boxSize, boxSize, boxSize);
            rectangle(result, box, colorMap.at(faceGrid[i][j]), FILLED);
            rectangle(result, box, Scalar(0, 0, 0), 2);
        }

    putText(result, "Press [R] to rescan or [N] for next",
        Point(10, gridSize + 35), FONT_HERSHEY_SIMPLEX,
        0.45, Scalar(255, 255, 255), 1, LINE_AA);
    return result;
}

Mat CubeScanner::drawFullCube(const vector<vector<vector<RubiksCube::Color>>>& cubeGrid) {
    int gap = 5, w = 12 * boxSize, h = 9 * boxSize;
    Mat canvas(h, w, CV_8UC3, Scalar(30, 30, 30));

    auto drawFace = [&](int faceIndex, int row, int col) {
        Point topLeft(col * boxSize, row * boxSize);
        rectangle(canvas,
            Rect(topLeft, Size(3 * boxSize, 3 * boxSize)),
            Scalar(255, 255, 255), 4);

        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                int x = (col + j) * boxSize;
                int y = (row + i) * boxSize;
                Rect rect(x, y, boxSize - gap, boxSize - gap);
                rectangle(canvas, rect,
                    colorMap.at(cubeGrid[faceIndex][i][j]), FILLED);
                rectangle(canvas, rect, Scalar(0, 0, 0), 2);
            }
    };

    drawFace(0, 0, 3);
    drawFace(1, 3, 0);
    drawFace(2, 3, 3);
    drawFace(3, 3, 6);
    drawFace(4, 3, 9);
    drawFace(5, 6, 3);

    return canvas;
}

void CubeScanner::scanCube(RubiksCubeBitboard& cube) {
    vector<vector<vector<RubiksCube::Color>>> cubeGrid(
        6, vector<vector<RubiksCube::Color>>(
            3, vector<RubiksCube::Color>(3, RubiksCube::Color::WHITE)));

        vector<string> faceNames = {"UP", "LEFT", "FRONT", "RIGHT", "BACK", "DOWN"};

    for (int face = 0; face < 6; face++) {
         cout << "[Scanner] Scanning face " << (face+1) << "/6: "
             << faceNames[face] << "\n";
        while (true) {
            auto grid = captureFace();
            cubeGrid[face] = grid;

            Mat faceImg = drawColorFace(grid);
            Mat cubeImg = drawFullCube(cubeGrid);

            imshow("Scanned Face", faceImg);
            imshow("Cube Net", cubeImg);

            int key = waitKey(0);
            
            if (key == 'n' || key == 'N') {
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        cube.setColor(
                            static_cast<RubiksCube::Face>(face),
                            i, j, grid[i][j]);
                destroyWindow("Scanned Face");
                break;
            }
            else if (key == 'r' || key == 'R') {
                cout << "[Scanner] Rescanning face " << faceNames[face] << "...\n";
            }
            else {
                cout << "[Scanner] Invalid key. Press [R] to rescan or [N] for next.\n";
            }
        }
    }

    cap.release();
    destroyAllWindows();
    cout << "[Scanner] All 6 faces scanned.\n";
}