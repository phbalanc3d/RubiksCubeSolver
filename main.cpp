#include "models/cube1d.cpp"
#include "solvers/iddfs.h"
#include "solvers/idastarsolver.h"

#include <ctime>
#include <bits/stdc++.h>
using namespace std;


int main(){
    srand(time(0));
    RubiksCube1dArray cube1d;
    cube1d.randomShuffle(4);
    cube1d.print();

    IDAstarSolver<RubiksCube1dArray> solver(cube1d);
    vector<RubiksCube1dArray::Move> moves = solver.solve();
    cout<<"Solution:\n";

    for(auto move : moves){
        cout<<cube1d.getMove(move)<<" ";
    }
    cout<<"\n";
    for(auto move: moves){
        cube1d.applyMove(move);
    }

    cout<<cube1d.isSolved()<<endl;
    cube1d.print();
    return 0;
}