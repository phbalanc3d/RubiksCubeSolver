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
using namespace std;
class NibbleArray{
    private:
    // the no of ele in the array
    size_t size;
    vector<uint8_t> arr;

    public:
    // all intialised to 15 by defalut
    // all the 8bits are 1 by default
    NibbleArray(const size_t size,const uint8_t val= 0xFF);

    uint8_t get(const size_t pos) const;

    void set(const size_t pos, const uint8_t val);
    //retur pointer to the data
    unsigned char *data();
    //const version too
    const unsigned char* data() const;
    // Actual storage size in bytes
    size_t storageSize() const;
    //compressed nibble array to dest vector in their original form
    void inflate(vector<uint8_t>& dest) const;
    // reset nibble array to specific val , by default all 1s
    void reset(const uint8_t val = 0xFF);
};
