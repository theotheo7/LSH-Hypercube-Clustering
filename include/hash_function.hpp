#ifndef HASH_FUNCTION_HPP
#define HASH_FUNCTION_HPP

#include <iostream>
#include <vector>
#include <random>
#include <string>

#include "image.hpp"

class HashFunction {
private:
    std::vector<double> v;
    double t;
    int w;

    std::random_device r;
    std::default_random_engine generator;
    std::normal_distribution<double> normalDistribution;
    std::uniform_real_distribution<double> uniDistribution;

public:
    HashFunction(int);

    int h(void *);

};

#endif