#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <vector>
#include <algorithm>

#include <random>
#include <iterator>

#include "../include/parser.hpp"
#include "../include/utils.hpp"
#include "../include/image.hpp"


class Cluster {
private:

    int k;
    int tables;
    int functions;
    int M;
    int dim;
    int probes;

public:
    Cluster(int, int, int, int, int, int);
    ~Cluster();

    void kpp(std::vector<Image*> *, std::vector<Image*> *);

    Image *selectRandomly(std::vector<Image *> *);
};
