#include <utility>

#include "../include/image.hpp"

using namespace std;

Image::Image(uint newId, vector<unsigned char> *coords) {
    this->id = newId;
    this->coords = coords;
}

Image::~Image() {
    delete coords;
}

uint Image::getId() {
    return this->id;
}

void Image::setId(uint newId) {
    id = newId;
}

vector<unsigned char> *Image::getCoords() {
    return this->coords;
}

void Image::setCoords(vector<unsigned char> *newCoords) {
    coords = newCoords;
}

uint Image::getCluster() {
    return this->cluster;
}

void Image::setCluster(uint newCluster) {
    cluster = newCluster;
}

