#include <iostream>
#include <vector>
#include <unistd.h>
#include <cstring>

#include "../include/parser.hpp"
#include "../include/cube.hpp"

using namespace std;

int main(int argc, char **argv) {
    int opt;
    int k = 14;
    int M = 10;
    int probes = 2;
    int N = 1;
    int R = 10000;

    string inputFile, queryFile, outputFile;

    while((opt = getopt(argc, argv, "d:q:k:L:o:N:R:")) != -1) {
        switch (opt) {
            case 'd':
                inputFile = optarg;
                break;
            case 'q':
                queryFile = optarg;
                break;
            case 'k':
                k = stoi(optarg);
                break;
            case 'M':
                M = stoi(optarg);
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'N':
                N = stoi(optarg);
                break;
            case 'R':
                R = stoi(optarg);
                break;
            default:
                abort();
        }
    }

    for (int i = 0; i < argc; i++) {
        if (!strcmp("-probes", argv[i])) {
            probes = stoi(argv[i+1]);
        }
    }

    auto parser = new Parser();

    vector<Image *> *inputImages = parser->readInputFile(inputFile);
    vector<Image *> *queryImages = parser->readQueryFile(queryFile);

    cout << "Creating hypercube!" << endl;
    HyperCube hyperCube(k, M, probes, N, R, inputImages, outputFile);
    cout << "Created hypercube!" << endl;

    for (auto queryImage : *queryImages) {
        hyperCube.query(queryImage);
    }

    delete parser;
    delete queryImages;

    return 0;
}