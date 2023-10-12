#include "../include/image.hpp"

using namespace std;

Image::Image(uint newId, vector<char> newCoords) {
    this->id = newId;
    this->coords = newCoords;
}

Image::~Image() {}

int Image::getId(void) {
    return this->id;
}

void Image::setId(uint newId) {
    id = newId;
}

vector<char> Image::getCoords(void) {
    return this->coords;
}

void Image::setCoords(vector<char> newCoords) {
    coords = newCoords;
}

