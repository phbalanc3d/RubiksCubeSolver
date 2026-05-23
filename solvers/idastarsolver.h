#include<bits/stdc++.h>
#include "../models/cube.h"
using namespace std;

template<typename T>
class IDAstarSolver {

private:
    vector<typename T::Move> moves;
    // Current bound
    int bound;
    // Next bound
    int next_bound;

public:

    T rubiksCube;
    IDAstarSolver(T cube){
        rubiksCube = cube;
    }
    // dummy heuristic 
    int heuristic(T cube){
        return 0;
    }
    //dfs

    bool dfs(int g){
        
        int h = heuristic(rubiksCube);
        int f = g + h;
        if(f > bound){
            next_bound = min(next_bound, f);
            return false;
        }
        // Goal check
        if(rubiksCube.isSolved())
            return true;
        // Try all 18 moves
        for(int i=0;i<18;i++){

            typename T::Move move = static_cast<typename T::Move>(i);
            // Apply move
            rubiksCube.applyMove(move);
            // Store move
            moves.push_back(move);
            // Recursive DFS
            if(dfs(g+1))
                return true;
            // Backtrack
            rubiksCube.invert(move);

            moves.pop_back();
        }

        return false;
    }

    vector<typename T::Move> solve(){

        // Initial bound
        bound = heuristic(rubiksCube);

        while(true){
            next_bound = INT_MAX;

            // Start DFS
            if(dfs(0))
                return moves;
            // Increase bound
            bound = next_bound;
        }
    }

};