#pragma once
#include "CornerPatternDatabase.h"
#include "../models/cube.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>
#include <climits>
#include <functional>
#include <numeric>

using namespace std;
template<typename T>
class CornerDB {
private:
    CornerPatternDatabase cornerDB;
    string fileName;
public:
    CornerDB(string _fileName);
    CornerDB(string _fileName, uint8_t init_val);

    bool bfsAndStore(uint8_t maxDepth);

};

//template implementations inside the .h file because of linker error due to template class and its implementation in different files
template<typename T>
CornerDB<T>::CornerDB(string _fileName)
        :
        fileName(_fileName){}


template<typename T>
CornerDB<T>::CornerDB(
        string _fileName,
        uint8_t init_val)
        :
        fileName(_fileName),
        cornerDB(init_val){}


template<typename T>
bool CornerDB<T>::bfsAndStore(
        uint8_t maxDepth) {
    // default constructor for solved cube
    T cube;
    queue<T> q;
    q.push(cube);
    // solved state index
    uint32_t index = cornerDB.getDatabaseIndex(cube);
    // depth of solved state intialy is 0
    cornerDB.setNumMoves(index, 0);
while(!q.empty()) {
        T curr = q.front();
        q.pop();
        uint8_t currDepth = cornerDB.getNumMoves(cornerDB.getDatabaseIndex(curr));
        // stop deeper expansion cuz its childern wil have depth more than maxDepth
        if(currDepth == maxDepth)
            continue;
for(int move = 0;move < 18;move++) {
            T child = curr;
// this creates the child like all the neighbours of the current cube after applying one move
            child.applyMove(RubiksCube::Move(move));
            uint32_t childIndex =cornerDB.getDatabaseIndex(child);
//if unvisited then
 if(cornerDB.getNumMoves(childIndex)== 255) {
                cornerDB.setNumMoves(childIndex,currDepth + 1);
                q.push(child);
            }
        }
    }
    for(uint32_t i = 0;i < cornerDB.getSize();i++) {
        if(cornerDB.getNumMoves(i)== 255) {
            cornerDB.setNumMoves(i,maxDepth + 1);
        }
    }

cornerDB.toFile(fileName);
return true;
}


