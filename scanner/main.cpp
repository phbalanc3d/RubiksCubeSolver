#include <opencv2/opencv.hpp>
#include <fstream>
#include "../patternDatabase/CornerDB.h"
#include "../models/cubeBitboard.h"
#include "../scanner/CubeScanner.h"
#include "../solvers/idastarsolver.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace cv;
int main() {
    string dbFile = "../patternDatabase/db/cornerDB.bin";

    // Step 1 — DB generation
    ifstream file(dbFile, ios::binary);
    if (file.good()) {
        cout << "Corner DB already exists\n";
    } else {
        cout << "Generating Corner DB...\n";
        CornerDB<RubiksCubeBitboard> cornerDB(dbFile, 0xFF);
        cornerDB.bfsAndStore(8);
        cout << "Corner DB generated\n";
    }
    file.close();

    // Step 2 — TEST SCRAMBLE (bypasses scanner)
    RubiksCubeBitboard cube;
    cube.u(); cube.r(); cube.f();

    cout << "[Test] Applied U R F — solution should be F' R' U'\n";
    cout << "[Debug] Corner indices: ";
for (int i = 0; i < 8; i++)
    cout << (int)cube.getCornerIndex(i) << " ";
cout << "\n";

cout << "[Debug] Corner orientations: ";
for (int i = 0; i < 8; i++)
    cout << (int)cube.getCornerOrientation(i) << " ";
cout << "\n";

// ADD after scramble, before solver:
int orientSum = 0;
for (int i = 0; i < 8; i++)
    orientSum += cube.getCornerOrientation(i);
cout << "[Debug] Orientation sum: " << orientSum << " mod3=" << (orientSum % 3) << "\n";

RubiksCubeBitboard solved;
int solvedSum = 0;
for (int i = 0; i < 8; i++)
    solvedSum += solved.getCornerOrientation(i);
cout << "[Debug] Solved orientation sum: " << solvedSum << " mod3=" << (solvedSum % 3) << "\n";


// Check solved cube too:

cout << "[Debug] Solved heuristic: " << /* compute index */ "\n";
CornerDB<RubiksCubeBitboard> testDB(dbFile);
cout << "[Debug] Solved DB value: " << (int)testDB.getNumMoves(testDB.getDatabaseIndex(solved)) << "\n";
cout << "[Debug] Scrambled DB value: " << (int)testDB.getNumMoves(testDB.getDatabaseIndex(cube)) << "\n";
    cube.print();

    // Step 3 — Solver
    cout << "\n[Solver] Running IDA*...\n";
    auto startTime = chrono::high_resolution_clock::now();

    IDAstarSolver<RubiksCubeBitboard> solver(cube, dbFile);
    cout << "[Debug] Heuristic at start: " << solver.heuristic(solver.rubiksCube) << "\n";

    vector<RubiksCube::Move> moves = solver.solve();
    auto endTime = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double>(endTime - startTime).count();

    // Step 4 — Output
    cout << "[Debug] solve() returned " << moves.size() << " moves\n";

    if (moves.empty()) {
        cout << "No solution found!\n";
        return 1;
    }

    cout << "\n====== SOLUTION ======\n";
    cout << "Moves : " << moves.size() << "\n";
    cout << "Time  : " << elapsed << " seconds\n";
    cout << "Sequence: ";
    for (int i = 0; i < (int)moves.size(); i++) {
        cout << RubiksCube::getMove(moves[i]);
        if (i != (int)moves.size() - 1) cout << " -> ";
    }
    cout << "\n=====================\n";

    // Step 5 — Verify
    for (auto m : moves) cube.applyMove(m);
    cout << "[Verify] Cube solved: " << (cube.isSolved() ? "YES" : "NO") << "\n";

    return 0;
}
/*int main() {
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
        CubeScanner scanner(1, 80);
        bool success = scanner.scanCube(cube);  // ← now returns bool
        if (!success) {
            cerr << "[Scanner] Failed to scan the cube." << "\n";
            return -1;
        }
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

cout << "[Debug] isSolved at start: " << solver.rubiksCube.isSolved() << "\n";
cout << "[Debug] Heuristic value: " << solver.heuristic(solver.rubiksCube) << "\n";

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
}*/





