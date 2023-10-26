#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <vector>

#include "utils.hpp"

class Image {

private:

    uint id;
    std::vector<unsigned char> *coords;
    uint cluster;

public:

    Image(uint, std::vector<unsigned char> *);
    ~Image();

    uint getId();
    void setId(uint);

    std::vector<unsigned char> *getCoords();
    void setCoords(std::vector<unsigned char> *);

    uint getCluster();
    void setCluster(uint);

};

#endif
