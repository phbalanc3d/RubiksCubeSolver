#include "PatternDatabase.h"
using namespace std;

PatternDatabase::PatternDatabase(const size_t size) :
        database(size, 0xFF), size(size), numItems(0) {
}
PatternDatabase::PatternDatabase(const size_t size, uint8_t init_val) :
        database(size, init_val), size(size), numItems(0) {
}

bool PatternDatabase::setNumMoves(const uint32_t ind, const uint8_t numMoves) {
    uint8_t oldMoves = this->getNumMoves(ind);

//    New item is getting added
    if(oldMoves == 0xF){
        ++this->numItems;
    }
//write if its better
    if(oldMoves > numMoves){
        this->database.set(ind, numMoves);
        return true;
    }
    return false;

}
bool PatternDatabase::setNumMoves(const RubiksCube &cube, const uint8_t numMoves) {
    return this->setNumMoves(this->getDatabaseIndex(cube), numMoves);
}


uint8_t PatternDatabase::getNumMoves(const uint32_t ind) const {
    return this->database.get(ind);
}
uint8_t PatternDatabase::getNumMoves(const RubiksCube &cube) const {
    return this->getNumMoves(this->getDatabaseIndex(cube));
}

size_t PatternDatabase::getSize() const {
    return this->size;
}
size_t PatternDatabase::getNumItems() const {
    return this->numItems;
}

bool PatternDatabase::isFull() const {
    return this->numItems == this->size;
}

vector<uint8_t> PatternDatabase::inflate() const {
    vector<uint8_t> inflated;
    this->database.inflate(inflated);
    return inflated;
}

void PatternDatabase::reset() {
    if(this->numItems != 0){
        this->database.reset(0xFF);
        this->numItems = 0;
    }
}
//save database to disk
void PatternDatabase::toFile(const string &filePath) const {

    ofstream writer(filePath, ios::out | ios::binary | ios::trunc);

    if(!writer.is_open())
        throw "Failed to open the file to write";

    writer.write(
        //treat the unsigned bytes as raw char bytes
            reinterpret_cast<const char*>(this->database.data()),
            this->database.storageSize()
            );

    writer.close();
}

bool PatternDatabase::fromFile(const string &filePath) {
    //open for reading then open file at the end to get the size
    ifstream reader(filePath, ios::in | ios::ate);

    if(!reader.is_open())
        return false;
//total size
    size_t fileSize = reader.tellg();

    if(fileSize != this->database.storageSize()){
        reader.close();
        throw "Database corrupt! Failed to open Reader";
    }
//move file cursor to start and reading
    reader.seekg(0, ios::beg);
    //copies bytes from file to memory its syntax(pointer to data, number of bytes)
    reader.read(
            reinterpret_cast<char*> (this->database.data()),
            this->database.storageSize()
            );
    reader.close();
    this->numItems = this->size;
    return true;
}

