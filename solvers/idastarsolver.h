#pragma once

#include <vector>
#include <string>
#include <climits>

#include "../models/cube.h"
#include "../patternDatabase/CornerDB.h"

using namespace std;

template<typename T>
class IDAstarSolver {

private:
    vector<typename T::Move> moves;
    // Current bound
    int bound;
    // Next bound
    int next_bound;
//chnage 
    CornerDB<T> cornerDB;

public:

    T rubiksCube;

    IDAstarSolver(T cube, string fileName)
    : rubiksCube(cube), cornerDB(fileName) {}
    //heuristic 
    int heuristic(T& cube){
        return cornerDB.getNumMoves(cornerDB.getDatabaseIndex(cube));
    }
    //dfs

    bool dfs(int g){
        
        int h = heuristic(rubiksCube);
        int f = g + h;
        //pruning
        if(f > bound){
            next_bound = min(next_bound, f);
            return false;
        }
        // Goal check
        if(rubiksCube.isSolved())
            return true;
         //bfs model
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
            //if unsolvable then its the guard
            if (next_bound == INT_MAX) return {};
            // Increase bound
            bound = next_bound;
        }
    }

};
