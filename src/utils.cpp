#include "../include/utils.hpp"

using namespace std;

double dist(void *a, void *b, int k) {
    auto *imageA = (Image *) a;
    auto *imageB = (Image *) b;

    if (imageA->getCoords().size() != imageB->getCoords().size()) {
        return -1;
    }

    double dist = 0.0;
    for (size_t i = 0; i < imageA->getCoords().size(); i++) {
        dist += pow((double) (imageA->getCoords().at(i) - imageB->getCoords().at(i)), k);
    }

    return pow(dist, (double) 1/k);
}