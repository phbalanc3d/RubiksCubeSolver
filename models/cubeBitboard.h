#pragma once
#include "cube.h"

class RubiksCubeBitboard : public RubiksCube {
private:
    uint64_t solved_side_config[6]{};
    Color centerColors[6]; 

    int arr[3][3] = {{0, 1, 2},
                     {7, 8, 3},
                     {6, 5, 4}};

    uint64_t one_8 = (1ULL << 8) - 1;
    uint64_t one_24 = (1ULL << 24) - 1;

    void rotateFace(int ind);

    void rotateSide(
        int s1, int s1_1,int s1_2, int s1_3,

        int s2, int s2_1,int s2_2, int s2_3
    );
    int get5bitCorner(string corner);

public:
    uint64_t bitboard[6]{};

    // your existing data members
    //uint64_t bits1, bits2;   // whatever your bitboard fields are

    RubiksCubeBitboard();

    Color getColor(Face face, unsigned row, unsigned col) const override;
    
    void setColor(Face face, int row, int col, Color color) override;

    bool isSolved() const override;

    RubiksCube& f() override;
    RubiksCube& fPrime() override;
    RubiksCube& f2() override;
    RubiksCube& b() override;
    RubiksCube& bPrime() override;
    RubiksCube& b2() override;
    RubiksCube& l() override;
    RubiksCube& lPrime() override;
    RubiksCube& l2() override;
    RubiksCube& r() override;
    RubiksCube& rPrime() override;
    RubiksCube& r2() override;
    RubiksCube& u() override;
    RubiksCube& uPrime() override;
    RubiksCube& u2() override;
    RubiksCube& d() override;
    RubiksCube& dPrime() override;
    RubiksCube& d2() override;

    uint64_t getCorners();

    bool operator==(const RubiksCubeBitboard& r1) const;
    RubiksCubeBitboard& operator=(const RubiksCubeBitboard& r1);
};

struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard& cube) const;
};