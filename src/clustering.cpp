#include "../include/clustering.hpp"

using namespace std;

Clustering::Clustering(int clusterNum, int L, int kLSH, int M, int kCube, int probes) {

    this->clusterNum = clusterNum;
    this->L = L;
    this->kLSH = kLSH;
    this->M = M;
    this->kCube = kCube;
    this->probes = probes;

    this->clusters = new vector<Cluster *>;

}

Clustering::~Clustering() {
    for (auto cluster : *clusters) {
        delete cluster;
    }

    delete clusters;
}

void Clustering::initialize(vector<Image *> *images) {
    vector<double> probabilities;
    vector<double> minDist;
    double distance, prob, number;

    vector<Image *> available = *images;

    // Select first centroid randomly
    clusters->push_back(selectRandomly(&available));

    // For k clusters
    for (int i = 1; i < clusterNum; i++) {
        int numOfImages = (int) available.size();

        // Initialize min distance of each image to closest centroid
        // as a "max" distance
        for (int j = 0; j < numOfImages; j++) {
            minDist.push_back(10000000);
        }

        // For every image find minimum distance to the closest centroid
        for (int j = 0; j < numOfImages; j++) {

            for (auto cluster: *clusters) {

                distance = distCoords(cluster->getCentroid(), available.at(j)->getCoords());
                if (distance < minDist.at(j)) {
                    minDist.at(j) = distance;
                }

            }

        }

        // Find sum of all distances
        long double totalDist = 0;
        for (int j = 0; j < numOfImages; j++) {
            totalDist += minDist.at(j);
        }

        // Calculate probability of each image being picked as centroid
        for (int j = 0; j < numOfImages; j++) {
            distance = minDist.at(j);
            prob = distance / totalDist;
            probabilities.push_back(prob);
        }

        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_real_distribution<double> distr(0.0, 1.0);
        number = distr(generator);

        // Find next centroid
        double probSum = 0;
        for (int j = 0; j < numOfImages; j++) {
            probSum += probabilities.at(j);
            if (number <= probSum) {
                clusters->push_back(new Cluster(i + 1, new vector<double>(*images->at(j)->getCoords())));
                available.erase(available.begin() + j);
                break;
            }
        }

        minDist.clear();

    }
}

Cluster *Clustering::selectRandomly(vector<Image *> *images) {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a random number distribution for indices
    std::uniform_int_distribution<size_t> dist(0, images->size() - 1);

    // Generate a random index
    size_t randomIndex = dist(gen);

    Image *image = images->at(randomIndex);
    images->erase(images->begin() + randomIndex);

    // Access the random element from the vector
    return new Cluster(1, new vector<double>(*image->getCoords()));

}

void Clustering::lloyds(std::vector<Image *> *images, int maxTimes) {
    int changes;
    int numOfImages = (int) images->size();
    int acceptable = numOfImages / 100;
    double distance;

    do {
        cout << "Running.." << endl;
        changes = 0;

        Cluster *temp;
        for (auto image : *images) {
            double min = 1000000;
            for (auto cluster : *clusters) {
                distance = distCoords(image->getCoords(), cluster->getCentroid());
                if (distance < min) {
                    min = distance;
                    temp = cluster;
                }
            }

            if (image->getCluster() != temp->getId()) {
                changes++;
                if (image->getCluster() != 0) {
                    clusters->at(image->getCluster() - 1)->removeImage(image);
                    updateMacQueenRemoval(clusters->at(image->getCluster() - 1));
                }

                temp->assign(image);
                updateMacQueenInsert(temp);
            }

        }

        maxTimes--;

    } while (maxTimes > 0 && changes > acceptable);

    for (auto cluster : *clusters) {
        cout << "Size of cluster c" << cluster->getId() << " after lloyds is: " << cluster->getImages()->size() << endl;
    }

}

void Clustering::updateMacQueenInsert(Cluster *cluster) {
    int sizeOfCoords = cluster->getCentroid()->size();

    auto coords = cluster->getCentroid();
    int imageNum = cluster->getImages()->size();

    for (int i = 0; i < sizeOfCoords; i++) {
        double newImageCoord = cluster->getImages()->back()->getCoords()->at(i);
        coords->at(i) = (coords->at(i) * (imageNum - 1) + newImageCoord) / imageNum;
    }

}

void Clustering::updateMacQueenRemoval(Cluster *cluster) {
    int sizeOfCoords = cluster->getCentroid()->size();

    auto coords = cluster->getCentroid();
    int imageNum = cluster->getImages()->size();

    for (int i = 0; i < sizeOfCoords; i++) {
        double total = 0;
        for (int j = 0; j < imageNum; j++) {
            total += cluster->getImages()->at(j)->getCoords()->at(i);
        }
        coords->at(i) = total / imageNum;
    }

}

/*
uint Clustering::findNearestCentroid(Image *image) {
    double min = 10000000;
    double distance;

    uint centroid = 0;

    for (auto cluster : *clusters) {
        distance = dist(image, cluster->getCentroid(), 2);
        if (distance < min) {
            min = distance;
            centroid = cluster->getId() - 1;
        }
    }

    return centroid;
}*/
