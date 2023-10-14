#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <vector>

#include "utils.hpp"

class Image {

private:

    uint id;
    std::vector<char> coords;

public:

    Image(uint, std::vector<char>);
    ~Image();

    uint getId();
    void setId(uint);

    std::vector<char> getCoords();
    void setCoords(std::vector<char>);

};

#endif
