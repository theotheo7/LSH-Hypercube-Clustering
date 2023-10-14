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

uint binaryToUint(string binary) {
    uint decimal = 0;
    int base = 1;

    for (int i = 0; i < (int) binary.length(); i++) {

        if (binary[i] == '1') {
            decimal += base;
        }

        base *= 2;
    }

    return decimal;
}