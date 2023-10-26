#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include <netinet/in.h>

#include "image.hpp"
#include "cluster.hpp"

class Parser {
private:

public:

    Parser();
    ~Parser();

    std::vector<Image *> *readInputFile(const std::string&);
    std::vector<Image *> *readQueryFile(const std::string&);

    Cluster *readClusterConf(const std::string&);
};

#endif