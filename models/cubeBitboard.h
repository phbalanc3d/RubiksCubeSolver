#pragma once
#include "cube.h"

class RubiksCubeBitboard : public RubiksCube {
public:
    // your existing data members
    uint64_t bits1, bits2;   // whatever your bitboard fields are

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
};

struct HashBitboard {
    size_t operator()(const RubiksCubeBitboard& cube) const;
};