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
    RubiksCube &applyMove(Move move);
    RubiksCube &invert(Move move);
    virtual RubiksCube &f()=0;

    virtual RubiksCube &fPrime()=0;

    virtual RubiksCube &f2()=0;

    virtual RubiksCube &b()=0;

    virtual RubiksCube &bPrime()=0;

    virtual RubiksCube &b2()=0;

    virtual RubiksCube &l()=0;

    virtual RubiksCube &lPrime()=0;

    virtual RubiksCube &l2()=0;

    virtual RubiksCube &r()=0;

    virtual RubiksCube &rPrime()=0;

    virtual RubiksCube &r2()=0;

    virtual RubiksCube &u()=0;

    virtual RubiksCube &uPrime()=0;

    virtual RubiksCube &u2()=0;

    virtual RubiksCube &d()=0;

    virtual RubiksCube &dPrime()=0;

    virtual RubiksCube &d2()=0;

};