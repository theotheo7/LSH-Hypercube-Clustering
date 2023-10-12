#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <iostream>
#include <vector>

class Image {

private:

    uint id;
    std::vector<char> coords;

public:

    Image(uint, std::vector<char>);
    ~Image();

    int getId();
    void setId(uint);

    std::vector<char> getCoords();
    void setCoords(std::vector<char>);

};

#endif
