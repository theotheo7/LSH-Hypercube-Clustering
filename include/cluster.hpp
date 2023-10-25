#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unistd.h>
#include <cstring>
#include <time.h>
#include <vector>

#include <random>
#include <iterator>

#include "../include/parser.hpp"
#include "../include/utils.hpp"
#include "../include/image.hpp"


class Cluster{
private:


    int k = 0;

    int numofhtables = 0;
    int numofhfuncs = 0;
    int M = 0;
    int dim = 0;
    int numofprobes = 0;

public:
    void kpp(std::vector<Image*> *image,int num,std::vector<Image*> *centroids,int k);

};
