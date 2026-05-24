#pragma once
#include "../models/cube.h"
#include "patternDatabase.h"
#include "PermutationIndexer.h"
using namespace std;

class CornerPatternDatabase : public PatternDatabase {
    //permutation indexer for 8 corners
    PermutationIndexer<8> permIndexer;
    public:
        CornerPatternDatabase();

        CornerPatternDatabase(uint8_t init_val);

        uint32_t getDatabaseIndex(const RubiksCube& cube) const;
};