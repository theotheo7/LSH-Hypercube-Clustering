#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <utility>

class HashTable {
private:

    uint size;

    unsigned long k, w, M, d;

    double **s;

    std::vector<std::list<std::pair<uint, void *>>*> table;

    uint hash(uint);

public:

    HashTable(uint);
    HashTable(int,int,int,int);

    ~HashTable();

    void insert(uint, void *);

    std::list<std::pair<uint, void *>> findBucket(uint);
    std::list<std::pair<uint, void *>> findSameID(uint);
};

#endif