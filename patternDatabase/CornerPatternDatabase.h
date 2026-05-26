#pragma once
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
#include "../models/cube.h"
#include "patternDatabase.h"
#include "PermutationIndexer.h"
using namespace std;
const string CORNER_DB_FILE = "patternDatabase/db/cornerDB.bin";
class CornerPatternDatabase : public PatternDatabase {
    //permutation indexer for 8 corners
    PermutationIndexer<8> permIndexer;
    public:
        CornerPatternDatabase();

        CornerPatternDatabase(uint8_t init_val);

        uint32_t getDatabaseIndex(const RubiksCube& cube) const;
};