#include <iostream>
#include <vector>

#include "../include/parser.hpp"
#include "../include/image.hpp"

using namespace std;

int main(int argc, char **argv) {

    auto parser = new Parser();

    vector<Image *> queryImages = parser->readQueryFile("resources/query.dat");

    delete parser;

    return 0;
}