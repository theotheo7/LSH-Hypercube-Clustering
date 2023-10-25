#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <unistd.h>
#include <cstring>
#include <time.h>

#include <random>
#include <iterator>

#include "../include/parser.hpp"
#include "../include/utils.hpp"
#include "../include/image.hpp"
#include "../include/cluster.hpp"

using namespace std;

int main(int argc, char **argv) {
  srand(time(NULL));

  int opt, m, flag = 0;

  int k =3;

  m = 0;
  char *ifile = nullptr;
  char *conffile = nullptr;
  char *ofile = nullptr;

  //ifstream ifs;
  //string s;

  Cluster cluster;

  while ((opt = getopt(argc, argv, "i:c:o:m:complete")) != -1) {
    switch(opt) {
      case 'i':
        ifile = optarg;
        break;
      case 'c':
        if (strcmp(optarg, "omplete")== 0) {
          flag = 1;
        } else {
          conffile = optarg;
        }
        break;
      case 'o':
        ofile = optarg;
        break;
      case 'm':
        m = stoi(optarg);
        break;
      case '?':
        flag = 1;
        break;
      default:
        abort();
    }
  }

    Parser *parser = new Parser();
    vector<Image *> *inputImages = parser->readInputFile("resources/input.dat");
    //parser for cluster conf


    int numOfPoints = points->size();

    //kpp first
    

    vector<Point> *centroids = lloyd(points, numOfPoints, k, 10);

    //FINISH LSH 
    //FINISH CUBE 
    //FINISH SILHOUETTE

    printResults(points, centroids, ofile, 3);

    delete centroids;
    delete points;

    return 0;
}