#pragma once

#include "../models/cube.h"
#include "nibbleArray.h"
#include "bits/stdc++.h"
using namespace std;

class PatternDatabase{
    NibbleArray database;
    size_t size;
    size_t numItems;
    //default constructor is private cuz this would create unintialised size and invalid nibble array
    PatternDatabase();
    public:
    //not intialised to any value
    // this forces to set the object of this class with a size
    PatternDatabase(const size_t size);

    PatternDatabase(const size_t size,const uint8_t val);

    virtual size_t getSize() const;

    virtual size_t getNumItems() const;

    virtual bool isFull() const;

    virtual void toFile(const string &filePath) const;

    virtual bool fromFile(const string &filePath);

    virtual vector<uint8_t> inflate() const;

    virtual void reset();

    virtual uint32_t getDatabaseIndex(const RubiksCube &cube) const = 0;

    //actual cube is given then calculate the database index then store value
    virtual bool setNumMoves(const RubiksCube &cube, const uint8_t numMoves);
//index know directly stores there then
    virtual bool setNumMoves(const uint32_t ind, const uint8_t numMoves);

    //cube given calulate its database index then return the value stores at that
    virtual uint8_t getNumMoves(const RubiksCube &cube) const;
//index already given
    virtual uint8_t getNumMoves(const uint32_t ind) const;

};