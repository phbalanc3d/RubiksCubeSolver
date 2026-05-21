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
     RubiksCube1dArray() {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    cube[i * 9 + j * 3 + k] = getColorChar(Color(i));
                }
            }
        }
    }
    Color getColor(Face face, unsigned row, unsigned col) const override {
        char color = cube[getIndex((int)face, (int)row, (int)col)];
        switch (color) {
            case 'B':
                return Color::BLUE;
            case 'R':
                return Color::RED ;
            case 'G':
                return Color::GREEN;
            case 'O':
                return Color::ORANGE;
            case 'Y':
                return Color::YELLOW;
            default:
                return Color::WHITE;
        }
    }
    bool isSolved() const override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (this->cube[getIndex(i, j, k)] == getColorChar(Color(i))) continue;
                    return false;
                }
            }
        }
        return true;
    }
     RubiksCube &u() override {
        this->rotateFace(0);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(4, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 0, 2 - i)] = cube[getIndex(1, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(1, 0, 2 - i)] = cube[getIndex(2, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, 0, 2 - i)] = cube[getIndex(3, 0, 2 - i)];
        for (int i = 0; i < 3; i++) cube[getIndex(3, 0, 2 - i)] = temp_arr[i];

        return *this;
    }
     RubiksCube &uPrime() override {
        this->u();
        this->u();
        this->u();

        return *this;
    }
     RubiksCube &u2() override {
        this->u();
        this->u();
        return *this;
    }

    RubiksCube &l() override {
        this->rotateFace(1);

        char temp_arr[3] = {};
        for (int i = 0; i < 3; i++) temp_arr[i] = cube[getIndex(0, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(0, i, 0)] = cube[getIndex(4, 2 - i, 2)];
        for (int i = 0; i < 3; i++) cube[getIndex(4, 2 - i, 2)] = cube[getIndex(5, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(5, i, 0)] = cube[getIndex(2, i, 0)];
        for (int i = 0; i < 3; i++) cube[getIndex(2, i, 0)] = temp_arr[i];

        return *this;
    }
    
     RubiksCube &lPrime() override {
        this->l();
        this->l();
        this->l();

        return *this;
    }
     RubiksCube &l2() override {
        this->l();
        this->l();

        return *this;
     }
};