#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <list>
#include <string>
#include <algorithm>

#include "hash_table.hpp"
#include "hash_function.hpp"

class HyperCube {
private:

    int k;
    int M;
    int probes;
    int N;
    int R;
    int w;

    HashTable *cube;
    std::vector<std::pair<HashFunction *, std::unordered_map<uint, char>*>> vertices;
    std::vector<Image *> *data;

public:

    HyperCube(int, int, int, int, int, std::vector<Image *> *data);
    ~HyperCube();

    std::string project(void *);

    void insert(void *);
    void query(void *);

    std::vector<double> getTrueNeighbors(void *);

};

#endif