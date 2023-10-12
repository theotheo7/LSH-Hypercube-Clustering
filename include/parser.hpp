#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <netinet/in.h>

#include "../include/image.hpp"

class Parser {
private:

public:

    Parser();
    ~Parser();

    void readInputFile(std::string);
};

#endif