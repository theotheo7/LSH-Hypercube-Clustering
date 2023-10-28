#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

#include "cluster.hpp"
#include "image.hpp"
#include "utils.hpp"

class Cluster;

class Clustering {
private:

    int clusterNum;
    int L;
    int kLSH;
    int M;
    int kCube;
    int probes;

    std::vector<Cluster *> *clusters;

public:

    Clustering(int, int, int, int, int, int);
    ~Clustering();

    void initialize(std::vector<Image *> *);
    Cluster *selectRandomly(std::vector<Image *> *);

};

#endif