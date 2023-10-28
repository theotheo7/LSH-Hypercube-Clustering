#ifndef CLUSTER_HPP
#define CLUSTER_HPP

#include <iostream>
#include <vector>

#include "./image.hpp"

class Image;

class Cluster {
private:

    uint id;

    Image *centroid;

    std::vector<Image *> *images;

public:
    Cluster(uint, std::vector<double> *);
    ~Cluster();

    uint getId();
    void setId(uint);

    Image *getCentroid();
    void setCentroid(Image *);

    std::vector<Image *> *getImages();
    void setImages(std::vector<Image *> *);

    void assign(void *);
    void clear();

};

#endif