#include "models/cube1d.cpp"
#include "solvers/dfssolver.h"

#include <bits/stdc++.h>
using namespace std;

int main(){
    RubiksCube1dArray cube1d;
    cube1d.randomShuffle(3);
    cube1d.print();

    DFSSolver<RubiksCube1dArray> solver(cube1d,8);
    vector<RubiksCube::Move> moves = solver.solve();
    cout<<"Solution:\n";

    for(auto move : moves){

        cout<<cube1d.getMove(move)<<" ";
    }

    cout<<"\n";
    return 0;
}