#include <iostream>
#include <unistd.h>

#include "../include/parser.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int opt;
    string inputFile, queryFile, outputFile;
    int k, L, N, R;

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
            case 'L':
                L = stoi(optarg);
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

    auto *parser = new Parser();

    vector<Image *> images = parser->readInputFile(inputFile);

    delete parser;

    return 0;
}