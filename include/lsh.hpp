#ifndef LSH_HPP
#define LSH_HPP

#include <vector>
#include <list>
#include <utility>
#include "image.hpp"
#include "hash_table.hpp"

class LSH
{
private:
    int k, L, N, R, w;
    std::vector<Image *> *data;
    HashTable **hashTables;

public:
    // Constructor
    LSH(int k, int L, int N, int R, std::vector<Image *> *data);
    
    // Approximate k-Nearest Neighbors method
    std::vector<std::pair<double, Image*>> approximateNN(Image* q, unsigned int k);
    
    // Range search method
    std::vector<Image*> range_search(Image *q, double R);
    
    // Destructor
    ~LSH();
};

#endif // LSH_HPP
