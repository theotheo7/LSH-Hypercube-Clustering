#include <utility>

#include "../include/image.hpp"

using namespace std;

Image::Image(uint newId, vector<double> *coords, uint cluster) {
    this->id = newId;
    this->coords = coords;
    this->cluster = cluster;
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

vector<double> *Image::getCoords() {
    return this->coords;
}

void Image::setCoords(vector<double> *newCoords) {
    coords = newCoords;
}

uint Image::getCluster() {
    return this->cluster;
}

void Image::setCluster(uint newCluster) {
    cluster = newCluster;
}

void Image::clear() {
    this->coords->clear();
}