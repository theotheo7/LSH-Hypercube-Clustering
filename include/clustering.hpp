#ifndef CLUSTERING_HPP
#define CLUSTERING_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

#include "cluster.hpp"
#include "image.hpp"
#include "utils.hpp"
#include "lsh.hpp"
#include "cube.hpp"

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
    static Cluster *selectRandomly(std::vector<Image *> *);

    void lloyds(std::vector<Image *> *, int);
    void reverseLSH(std::vector<Image *> *);
    void reverseCube(std::vector<Image *> *);

    static void updateMacQueenInsert(Cluster *);
    static void updateMacQueen(Cluster *);
    double minDistanceOfCentroids();
    Cluster *getClosestCentroid(Image *);

    std::vector<double> silhouette(std::vector<Image *> *);

};

#endif