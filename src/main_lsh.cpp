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
    int k = 4, L = 5, N = 1, R = 1000;

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

    // Read images and queries from files
    vector<Image *> *inputImages = parser->readInputFile("resources/input.dat");
    vector<Image *> *queryImages = parser->readQueryFile("resources/query.dat");

    /*if(inputFile.empty() || queryFile.empty()) {
        cerr << "Input and Query files are mandatory!" << endl;
        return 1;
    }*/

    // Initialize LSH with the parsed parameters and input images
    LSH lsh(k, L, N, R, inputImages);

	// Process each query image
    for(auto& queryImage : *queryImages){ //may i need it const here
        vector<pair<double, Image*>> aNN = lsh.approximateNN(queryImage, N); // Fetch the k nearest neighbors for the current query image
        cout << "Query: " << queryImage->getId() << endl;
        for (unsigned int j = 0; j < aNN.size(); j++) {
                    cout << "Nearest neighbor-" << j+1 << ": " << aNN[j].second->getId() << endl;
                    cout << "distanceLSH: " << aNN[j].first << endl;
                }
        cout << endl;

        cout << "R-near neighbors:\n";
                vector<Image*> imagesInRange = lsh.range_search(queryImage, R);
                if (imagesInRange.size() != 0) {
                    for (unsigned int j = 0; j < imagesInRange.size(); j++) {
                        cout << imagesInRange[j]->getId() << endl;
                    }
                } else {
                    cout << "Not found!\n";
                }
        cout << endl;
    }

    delete parser;
    delete queryImages;

    return 0;
}