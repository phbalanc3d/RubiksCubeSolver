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

uint8_t UNVISITED = 0xF;
template<typename T>
class CornerDB {
private:
    CornerPatternDatabase cornerDB;
    string fileName;
public:
    CornerDB(string _fileName);
    CornerDB(string _fileName, uint8_t init_val);

    bool bfsAndStore(uint8_t maxDepth);

    uint32_t getDatabaseIndex(const T& cube) const {
        return cornerDB.getDatabaseIndex(cube);
    }
    uint8_t getNumMoves(uint32_t index) const {
        return cornerDB.getNumMoves(index);
    }

};

//template implementations inside the .h file because of linker error due to template class and its implementation in different files
template<typename T>
CornerDB<T>::CornerDB(string _fileName)
    : fileName(_fileName), cornerDB(0xFF) {
         // FIX: load existing DB from disk
    ifstream file(_fileName, ios::binary);

    if (file.good()) {
        file.close();
        cornerDB.fromFile(_fileName);
        cout << "[CornerDB] Loaded from " << _fileName << "\n";
    }
}


template<typename T>
CornerDB<T>::CornerDB(string _fileName,uint8_t init_val)
        :fileName(_fileName),cornerDB(init_val){}


template<typename T>
bool CornerDB<T>::bfsAndStore(uint8_t maxDepth) {
    // default constructor for solved cube
    /*T cube;
    queue<T> q;
    q.push(cube);
    cout << "[CornerDB]BFS started" << endl;
    // solved state index
    uint32_t index = cornerDB.getDatabaseIndex(cube);
    // depth of solved state intialy is 0
    cornerDB.setNumMoves(index, 0);*/
    T cube;
queue<T> q;
q.push(cube);

cout << "[CornerDB]BFS started" << endl;

cout << "A" << endl;
uint32_t index = cornerDB.getDatabaseIndex(cube);

cout << "Solved index = " << index << endl;

cout << "B" << endl;
cornerDB.setNumMoves(index, 0);

cout << "C" << endl;
    long long cnt = 0;

while(!q.empty()) {
    cnt++;

    if(cnt % 100000 == 0){
        cout << "Visited: " << cnt << endl;
    }
    
        T curr = q.front();
        q.pop();
        uint8_t currDepth = cornerDB.getNumMoves(cornerDB.getDatabaseIndex(curr));
        // stop deeper expansion cuz its childern wil have depth more than maxDepth
        if(currDepth == maxDepth) continue;

for(int move = 0;move < 18;move++) {
            T child = curr;
// this creates the child like all the neighbours of the current cube after applying one move
            child.applyMove(RubiksCube::Move(move));
            uint32_t childIndex =cornerDB.getDatabaseIndex(child);
//if unvisited then

 if(cornerDB.getNumMoves(childIndex)== UNVISITED) {
                cornerDB.setNumMoves(childIndex,currDepth + 1);
                q.push(child);
            }
        }
    }

    for(uint32_t i = 0;i < cornerDB.getSize();i++) {
        if(cornerDB.getNumMoves(i)== UNVISITED) {
            cornerDB.setNumMoves(i,maxDepth + 1);
        }
    }

    cout << "[CornerDB]Saving DB..." << endl;
cornerDB.toFile(fileName);
cout << "[CornerDB]DB saved!" << endl;
return true;
}


