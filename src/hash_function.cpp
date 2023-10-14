#include "../include/hash_function.hpp"

using namespace std;

HashFunction::HashFunction(int w): generator{(r())}, uniDistribution(0.0, (double) w) {
    this->w = w;
    this->t = uniDistribution(generator);
}

int HashFunction::h(void *pointer) {
    auto *image = (Image *) pointer;

    double dot = 0.0;
    double rand;

    for (size_t i = 0; i < image->getCoords().size(); i++) {
        rand = normalDistribution(generator);
        v.push_back(rand * rand);
    }

    vector<char> p = image->getCoords();

    for (size_t i = 0; i < v.size(); i++) {
        dot += p[i] * v[i];
    }

    return floor((dot + t) / w);
}