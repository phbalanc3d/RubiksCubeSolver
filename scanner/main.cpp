#include <opencv2/opencv.hpp>
#include <fstream>
#include "../patternDatabase/CornerDB.h"
#include "../models/cubeBitboard.cpp"
#include "../scanner/CubeScanner.h"
#include "../solvers/idastarsolver.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;

int main() {
    //step 1 pattern database generation
string dbFile = "../patternDatabase/db/cornerDB.bin";

ifstream file(dbFile,ios::binary);

if(file.good()) {

    cout << "Corner DB already exists" << endl;

}
else {

    cout << "Generating Corner DB..." << endl;

    CornerDB<RubiksCubeBitboard> cornerDB(dbFile,0xFF);

    cornerDB.bfsAndStore(8);

    cout << "Corner DB generated and stored" << endl;
}
file.close();
//step 2 scanning the cube
RubiksCubeBitboard cube;

    try {
        CubeScanner scanner(0, 60);
        scanner.scanCube(cube);
    } catch (exception& e) {
        cerr << "[Scanner] Error: " << e.what() << "\n";
        return -1;
    }

cout << "\n[Cube] Scanned state:\n";
cube.print();
//step 3 solving the cube using IDA* and cornerDB
cout << "\n[Solver] Running IDA* with Corner Pattern Database...\n";
    
auto startTime = chrono::high_resolution_clock::now();
IDAstarSolver<RubiksCubeBitboard> solver(cube, dbFile);
vector<RubiksCube::Move> moves = solver.solve();
auto endTime = chrono::high_resolution_clock::now();
double elapsed = chrono::duration<double>(endTime - startTime).count();

//step4 output 
if (moves.empty()) {
        cout << "[Solver] No solution found. Re-scan the cube carefully.\n";
        return 1;
    }
cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║           SOLUTION FOUND             ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║ Moves  : " << moves.size() << "\n";
    cout << "║ Time   : " << elapsed << " seconds\n";
    cout << "║ Sequence:\n║  ";
    for (int i = 0; i < (int)moves.size(); i++) {
        cout << RubiksCube::getMove(moves[i]);
        if (i != (int)moves.size() - 1) cout << " -> ";
        if ((i + 1) % 8 == 0) cout << "\n║  ";
    }
    cout << "\n╚══════════════════════════════════════╝\n";

    //step5 verify
    for (auto m : moves)
        cube.applyMove(m);

    cout << "\n[Verify] Cube solved: " << (cube.isSolved() ? "YES " : "NO") << "\n";

    return 0; 
}





