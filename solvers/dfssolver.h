#pragma once

#include<bits/stdc++.h>
#include "../models/cube.h"

using namespace std;
template<typename T>
class DFSSolver {
    private:
        vector<RubiksCube::Move> path;
        int maxidepth;


        bool dfs(int dep) {

        if (rubiksCube.isSolved()) return true;

        if (dep > maxidepth) return false;

        for (int i = 0; i < 18; i++) {

            rubiksCube.move(RubiksCube::Move(i));

            path.push_back(RubiksCube::Move(i));

            if (dfs(dep + 1)) return true;
            //backtrack
            path.pop_back();

            rubiksCube.invert(RubiksCube::Move(i));
        }
        return false;
    }
    public:
    T rubiksCube;

    DFSSolver(T _rubiksCube, int _max_search_depth = 8) {
        rubiksCube = _rubiksCube;
        maxidepth = _max_search_depth;
    }
    vector<RubiksCube::Move> solve() {
        dfs(1);
        return path;
    }

};