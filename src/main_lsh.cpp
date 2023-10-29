#include <iostream>
#include <unistd.h>
#include <vector>

#include "../include/parser.hpp"
#include "../include/image.hpp"
#include "../include/lsh.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    int opt;
    string inputFile, queryFile, outputFile;
    int k = 4, L = 5, N = 1, R = 10000;

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

    

    auto parser = new Parser();

    // Read images and queries from files
    vector<Image *> *inputImages = parser->readInputFile(inputFile);
    vector<Image *> *queryImages = parser->readQueryFile(queryFile);

    /*if(inputFile.empty() || queryFile.empty()) {
        cerr << "Input and Query files are mandatory!" << endl;
        return 1;
    }*/

    // Initialize LSH with the parsed parameters and input images
    LSH lsh(k, L, N, R, inputImages, outputFile);

	// Process each query image
    for(auto queryImage : *queryImages){ //may i need it const here
        lsh.query(queryImage);
    }

    delete parser;

    for (auto image : *inputImages) {
        delete image;
    }
    delete inputImages;

    for (auto image : *queryImages) {
        delete image;
    }
    delete queryImages;

    return 0;
}