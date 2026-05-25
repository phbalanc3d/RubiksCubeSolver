#pragma once
#include "CornerPatternDatabase.h"
#include "../models/cube.h"
#include <bits/stdc++.h>

using namespace std;
template<typename T>
class CornerDB {
private:
    CornerPatternDatabase cornerDB;
    string fileName;
public:
    CornerDBMaker(string _fileName);
    CornerDBMaker(string _fileName, uint8_t init_val);

    bool bfsAndStore();

};

