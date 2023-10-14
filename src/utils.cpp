#include "../include/utils.hpp"

using namespace std;

double dist_l2(void *a, void *b) {
    auto *imageA = (Image *) a;
    auto *imageB = (Image *) b;

    if (imageA->getCoords().size() != imageB->getCoords().size()) {
        return -1;
    }

    double dist = 0.0;
    for (size_t i = 0; i < imageA->getCoords().size(); i++) {
        dist += pow((double) (imageA->getCoords().at(i) - imageB->getCoords().at(i)), 2);
    }

    return sqrt(dist);
}