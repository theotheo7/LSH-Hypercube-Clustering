#include <iostream>
#include <vector>

#include "../include/parser.hpp"
#include "../include/image.hpp"
#include "../include/cube.hpp"

using namespace std;

int main(int argc, char **argv) {
    int k = 14;
    int M = 1000;
    int probes = 3;
    int N = 2;
    int R = 10000;

    auto parser = new Parser();

    vector<Image *> *inputImages = parser->readInputFile("resources/input.dat");
    vector<Image *> *queryImages = parser->readQueryFile("resources/query.dat");

    cout << "Creating hypercube!" << endl;
    HyperCube hyperCube(k, M, probes, N, R, inputImages);
    cout << "Created hypercube!" << endl;

    for (auto queryImage : *queryImages) {
        hyperCube.query(queryImage);
    }

    delete parser;
    delete queryImages;

    return 0;
}