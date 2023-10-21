#include "../include/hash_function.hpp"

using namespace std;

HashFunction::HashFunction(int w): generator((rd())), uniDistribution(0.0, (double) w) {
    this->w = w;
    this->t = uniDistribution(generator);
}

int HashFunction::h(void *pointer) {
    auto image = (Image *) pointer;

    double dot = 0.0;
    double rand;

    vector<double> v;

    for (size_t i = 0; i < image->getCoords().size(); i++) {
        rand = normalDistribution(generator);
        v.push_back(rand * rand);
    }

    vector<unsigned char> p = image->getCoords();

    for (size_t i = 0; i < v.size(); i++) {
        dot += p.at(i) * v.at(i);
    }

    return floor((dot + t) / w);
}

int HashFunction::coinFlip() {
    std::uniform_int_distribution<int> distribution(0, 1);

    return distribution(generator);
}