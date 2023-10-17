#include <iostream>
#include <vector>

#include "../include/parser.hpp"
#include "../include/image.hpp"
#include "../include/cube.hpp"

using namespace std;

int main(int argc, char **argv) {
    int k = 14;
    int M = 10;
    int probes = 2;
    int N = 1;
    int R = 10000;

    auto parser = new Parser();

    vector<Image> *inputImages = parser->readInputFile("resources/input.dat");
    vector<Image> *queryImages = parser->readQueryFile("resources/query.dat");

    HyperCube hyperCube(k, M, probes, N, R, inputImages);

    vector<double> trueNeighbors = hyperCube.getTrueNeighbors(&queryImages->at(0));

    cout << "True neighbor: " << trueNeighbors.at(0) << endl;

    delete parser;
    delete queryImages;

    return 0;
}