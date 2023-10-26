#include "../include/cluster.hpp"

using namespace std;

Cluster::Cluster(int k, int tables, int functions, int M, int dim, int probes) {
    this->k = k;
    this->tables = tables;
    this->functions = functions;
    this->M = M;
    this->dim = dim;
    this->probes = probes;
}

Cluster::~Cluster() = default;

// K-Means++ initialization algorithm
void Cluster::kpp(vector<Image*> *images, vector<Image*> *centroids) {
    uint cluster;
    int index;
    vector<double> minDist;
    vector<double> probabilities;
    int i, j;
    double distance;
    double sum;
    double num;
    double prob;

    int numOfImages = (int) images->size();

    // Select first centroid randomly
    centroids->push_back(selectRandomly(images));

    for (i = 0; i < numOfImages; i++) {
        minDist.emplace_back(1000000000.0);
    }

    //For k centroids
    for (auto centroid : *centroids) {

        //Find the distance of each point to its nearest centroid
        for (auto image: *images) {
            distance = dist(image, centroid, 2);

            if (distance < minDist.at(j)) {
                minDist.at(j) = distance;
            }
        }

        sum = 0.0;
        for (j = 0; j < numOfImages; j++) {
            sum += minDist.at(j);
        }

        for (j = 0; j < numOfImages; j++) {
            prob = (minDist.at(j) * minDist.at(j)) / (sum * sum);
            probabilities.emplace_back(prob);
        }

        //Select an image to be the next centroid based on the probability specified
        random_device rand_dev;
        mt19937 generator(rand_dev());
        uniform_int_distribution<> distr(0, 1);
        num = distr(generator);
        long double probSum = 0.0;

        for (j = 0; j < numOfImages; j++) {
            probSum += probabilities.at(j);
            if (num <= probSum) {
                centroids->emplace_back(images->at(j));
                break;
            }
        }

    }

    // Assign each image to the closest centroid (cluster)
    for (j = 0; j < numOfImages; j++) {
        images->at(j)->setCluster(nearestCentroid(images->at(j),centroids, k));
    }

}

Image *Cluster::selectRandomly(vector<Image *> *images) {

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create a random number distribution for indices
    std::uniform_int_distribution<size_t> dist(0, images->size() - 1);

    // Generate a random index
    size_t randomIndex = dist(gen);

    Image *image = images->at(randomIndex);
    auto it = find(images->begin(), images->end(), image);
    if (it != images->end()) {
        images->erase(it);
    }

    // Access the random element from the vector
    return image;

}

int nearestCentroid(Image* image, vector<Image*> *centroids, int k) {
    int i, index = 1;
    double distance, minDist;

    minDist = 1000000000000.0;
    for (i = 0; i < k; i++) {
        distance = dist(image, centroids->at(i),2);
        if (distance < minDist) {
            minDist = distance;
            index = i;
        }
    }
    return index;
}

vector<Image*> *lloyd(vector<Image*> *images, int numOfImages, int k, int maxTimes) {

    int i, j, index;
    int changes;
    int acceptable = numOfImages / 500;

    auto centroids = new vector<Image *>;

    vector<int> newCoords;

    for (i = 0; i < numOfImages; i++)
        newCoords.push_back(0);

    //kpp(images, numOfImages, centroids, k);

    int sizeOfCoords = images->at(1)->getCoords().size();

    do {

        for (i = 0; i < k; i++) {
            centroids->at(i)->setCluster(0);
            centroids->at(i)->getCoords().clear();
        }

    for (i = 0; i < numOfImages; i++) {
        index = images->at(i)->getCluster();
        centroids->at(index).cluster++; //maybe a function ( + 1 )
        for (j = 0; j < sizeOfCoords; j++) {
            newCoords.at(j) += images->at(i)->getCoords().at(j);
        }
    }

    for (i = 0; i < k; i++) {
        for (j = 0; j < sizeOfCoords; j++) {
            if (centroids->at(i)->getCluster() == 0)
                centroids->at(i).cluster++;
            centroids->at(i)->getCoords().at(j) /= centroids->at(i)->getCluster();
        }
    }

    changes = 0;
    for (i = 0; i < numOfImages; i++) {
        index = nearestCentroid(images->at(i), centroids, k);
        if (index != images->at(i)->getCluster()) {
            images->at(i)->setCluster(index);
            changes++;
        }
    }

    maxTimes--;

    } while ((changes > acceptable) && maxTimes > 0);

    for (i = 0; i < k; i++) {
        centroids->at(i)->setCluster(i);
    }

  return centroids;

}