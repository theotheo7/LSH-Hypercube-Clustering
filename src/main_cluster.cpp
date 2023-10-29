#include <iostream>
#include <string>
#include <unistd.h>
#include <cstring>

#include <random>

#include "../include/parser.hpp"

using namespace std;

int main(int argc, char **argv) {
    int opt;
    bool complete = false;
    string method;

    string inputFile, confFile, outputFile;

    while ((opt = getopt(argc, argv, "i:c:o:m:complete")) != -1) {
        switch(opt) {
            case 'i':
                inputFile = optarg;
                break;
            case 'c':
                if (strcmp(optarg, "omplete")== 0) {
                    complete = true;
                } else {
                    confFile = optarg;
                }
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'm':
                method = optarg;
                break;
            case '?':
                complete = true;
                break;
            default:
                abort();
        }
    }

    auto parser = new Parser();
    vector<Image *> *inputImages = parser->readInputFile(inputFile);
    //parser for cluster conf
    Clustering *clustering = parser->readClusterConf(confFile); //DIMITRIS: just to test the Silhouette,
                                                                                //          you can delete it
    cout << "Complete is: " << complete << endl;

    //kpp first
    clustering->initialize(inputImages);

    /*if (method == "LSH") {
        clustering->reverseLSH(inputImages);
    } else if (method == "Hypercube") {
        clustering->reverseCube(inputImages);
    } else {
        clustering->lloyds(inputImages, 20);
    }


    clustering->silhouette(inputImages); //silhouette*/

    delete parser;
    delete clustering;

    for (auto image : *inputImages) {
        delete image;
    }

    delete inputImages;

    return 0;
}