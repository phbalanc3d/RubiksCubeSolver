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
//draw grid
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
// Check if cube-like colors detected in grid
        int coloredCells = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                int x = startX + j * boxSize + boxSize / 2;
                int y = startY + i * boxSize + boxSize / 2;
                Vec3b bgr = medianColor(frame, x, y);
                RubiksCube::Color c = classifyColor(bgr);
                // Draw small circle showing detected color
                Scalar detectedColor = colorMap.at(c);
                circle(frame, Point(x, y), 8, detectedColor, FILLED);
                circle(frame, Point(x, y), 8, Scalar(0,0,0), 2);
                coloredCells++;
            }
        }
     // Instructions   
        putText(frame, "SPACE = capture  |  Q = quit", Point(20, 30),
            FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 255), 2, LINE_AA);

        imshow("Align Cube Face", frame);

        int key = waitKey(30);

        if (key == 32) break;      // SPACE to capture
        if (key == 'q' || key == 'Q') {
            destroyAllWindows();
            cap.release();
            exit(0);               // Q to quit entirely
        }
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
        Mat info(80, 400, CV_8UC3, Scalar(30, 30, 30));

        putText(info,
            "Scan face " + to_string(face+1) + "/6: " + faceNames[face],
            Point(20, 30), FONT_HERSHEY_SIMPLEX,
            0.8, Scalar(0, 255, 255), 2);

         putText(info, "Q = quit anytime",
            Point(20, 60), FONT_HERSHEY_SIMPLEX,
            0.6, Scalar(100, 100, 255), 1);
        
        imshow("Instructions", info);
        waitKey(1000); 

        while (true) {
            auto grid = captureFace();
            cubeGrid[face] = grid;

            Mat faceImg = drawColorFace(grid);
            Mat cubeImg = drawFullCube(cubeGrid);

            imshow("Scanned Face", faceImg);
            imshow("Cube Net", cubeImg);

            // Show options
            Mat options(60, 400, CV_8UC3, Scalar(30, 30, 30));
            putText(options, "N = next face  |  R = rescan  |  Q = quit",
                Point(10, 35), FONT_HERSHEY_SIMPLEX,
                0.6, Scalar(255, 255, 255), 1);
            imshow("Options", options);
            
            int key = waitKey(0);
            
            if (key == 'n' || key == 'N') {
                for (int i = 0; i < 3; ++i)
                    for (int j = 0; j < 3; ++j)
                        cube.setColor(
                            static_cast<RubiksCube::Face>(face),
                            i, j, grid[i][j]);
                destroyWindow("Scanned Face");
                destroyWindow("Options");
                break;
            }
            else if (key == 'q' || key == 'Q') {
                cout << "Scanning cancelled by user." << endl;
                destroyAllWindows();
                cap.release();  
                exit(0);
            }
            
            else if (key == 'r' || key == 'R') {
               destroyWindow("Scanned Face");
                continue;
            }
             else {
                cout << "Invalid key! Press [R] to rescan, [N] for next face, or [Q] to quit." << endl;
            }
        }
    }

    destroyAllWindows();
    cap.release();

    // Validate — check each color appears exactly 9 times
    map<RubiksCube::Color, int> colorCount;
    for (int face = 0; face < 6; face++)
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                colorCount[cubeGrid[face][i][j]]++;

    bool valid = true;
    for (auto& [color, count] : colorCount) {
        if (count != 9) {
            valid = false;
            break;
        } 
    }

    if (!valid) {
        cout << "\n Invalid cube scan! Color counts:" << endl;
        string colorNames[] = {"WHITE","YELLOW","RED","ORANGE","GREEN","BLUE"};
        for (auto& [color, count] : colorCount)
            cout << colorNames[(int)color] << ": " << count << endl;
        cout << "Please re-run and scan again carefully." << endl;
    } else {
        cout << "\n Cube scanned successfully!" << endl;
    }
}