#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <list>
#include <random>

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
    std::vector<std::pair<HashFunction *, std::map<uint, char>*>> vertices;
    std::list<Image> *data;

public:

    HyperCube(int, int, int, int, int, std::list<Image> *data);
    ~HyperCube();

    void insert(void *);
    void query(void *);

};

#endif