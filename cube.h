#pragma once
#include<bits/stdc++.h>
using namespace std;

class RubiksCube{
public:
    enum class Face{
        FRONT,
        BACK,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };
    enum class Color{
        WHITE,
        YELLOW,
        RED,
        ORANGE,
        BLUE,
        GREEN
    };
    enum class Move{
        L,LPrime, L2,
        R,RPrime, R2,
        U,UPrime, U2,
        D,DPrime, D2,
        F,FPrime, F2,
        B,BPrime, B2        
    };
    virtual Color getColor(Face face,unsigned row,unsigned col) const=0;
    static char getColorChar(Color color);
    virtual bool isSolved() const=0;
    static string getMove(Move ind);
    void print() const;
    vector<Move> randomShuffle(unsigned int times);
};