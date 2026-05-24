#include "NibbleArray.h"
using namespace std;
// here howw many bytes we need to store nibble is the size of the array the mega array that storess two values in arr[i]
    NibbleArray::NibbleArray(const size_t size, const uint8_t val) :
        size(size), arr(size / 2 + 1, val) {}
// get
    uint8_t NibbleArray::get(const size_t pos) const {
        size_t i = pos / 2;
        assert(pos <= this->size);
        uint8_t val = this->arr.at(i);
        // if odd then return the last 4 bits then
         if (pos % 2) {
        return val & 0x0F;
        } 
        // the first 4 bits 
        else {
        return (val >> 4);
        }
    }
//set
    void NibbleArray::set(const size_t pos, const uint8_t val) {
    size_t i = pos / 2;
    uint8_t currVal = this->arr.at(i);
    assert(pos <= this->size);
//odd
    if (pos % 2) {
        this->arr.at(i) = (currVal & 0xF0) | (val & 0x0F);

    } else {
        this->arr.at(i) = (currVal & 0x0F) | (val << 4);
    }
}
// data() is inbuilt stl that returns pointer to the first element of the vector and since we are storing two values in one byte so we can return the pointer to the data and then we can access the values using the get and set functions
    uint8_t *NibbleArray::data() {
        return this->arr.data();
    }
//readonly 
    const uint8_t *NibbleArray::data() const {
    return this->arr.data();
}
// returns the size 
size_t NibbleArray::storageSize() const {
    return this->arr.size();
}
//dont allocate jus reserve the space thats what this reserve does
void NibbleArray::inflate(vector<uint8_t> &dest) const {
    dest.reserve(this->size);

    for (unsigned i = 0; i < this->size; ++i)
        dest.push_back(this->get(i));
}
void NibbleArray::reset(const uint8_t val) {
    fill(this->arr.begin(), this->arr.end(), val);
}