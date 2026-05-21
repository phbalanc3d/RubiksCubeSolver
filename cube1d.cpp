#pragma once

#include "cube.h"

class RubiksCube1dArray : public RubiksCube{
    private:
    static inline int getIndex(int face,int row,int col){

        return face*9 + row*3 + col;
    }
    //rotates the face in clockwise dirn
    void rotateFace(int ind) {
        char temp_arr[9] = {};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                temp_arr[i * 3 + j] = cube[getIndex(ind, i, j)];
            }
        }
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 0, i)] = temp_arr[getIndex(0, 2 - i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, i, 2)] = temp_arr[getIndex(0, 0, i)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2, 2 - i)] = temp_arr[getIndex(0, i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(ind, 2 - i, 0)] = temp_arr[getIndex(0, 2, 2 - i)];
    }


    public:
    char cube[54];  
};