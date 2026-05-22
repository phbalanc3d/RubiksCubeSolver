#pragma once
#include<bits/stdc++.h>
#include "../models/cube.h"
#include "dfssolver.h"

template<typename T>
class IDDFSSolver {

    private:
    int maxidepth;
    vector<RubiksCube::MOVE> moves;

    public:
    T rubiksCube;

    IDDFSSolver(T _rubiksCube, int _max_search_depth = 7) {
        rubiksCube = _rubiksCube;
        maxidepth = _max_search_depth;
    }

    vector<RubiksCube::MOVE> solve() {
        for (int i = 1; i <= maxidepth; i++) {
            // making the obj of dfs class then applying the dfs solver to it then checking if the cube is solved or not
            DFSSolver<T> dfsSolver(rubiksCube, i);
            moves = dfsSolver.solve();
            if (dfsSolver.rubiksCube.isSolved()) {
                rubiksCube = dfsSolver.rubiksCube;
                break;
            }
        }
        return moves;
    }
};
