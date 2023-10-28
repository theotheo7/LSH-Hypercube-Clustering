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

double averageDistanceToCluster(Image* image, std::vector<Cluster *> *clusters) {
    double totalDistance = 0.0;
    int numImagesInCluster = 0;

    for (auto cluster : *clusters) {
        vector<Image*> *imageInCluster = cluster->getImages();
        for (auto clusterImage : *imageInCluster) {
            double distance = dist(image, clusterImage, 2); 
            totalDistance += distance;
            numImagesInCluster++;
        }
    }

    if (numImagesInCluster > 0) {
        return totalDistance / numImagesInCluster;
    }

    return 0.0; // Avoid division by zero if the clusters are empty
}

double averageDistanceToNeighborCluster(Image* image, const std::vector<Cluster*>* clusters/*, unsigned int imageIndex*/) {
    unsigned int clusterIndex = image->getCluster();

    double minDistance = std::numeric_limits<double>::max(); // Initialize with a large value
    Cluster* neighborCluster = nullptr;

    for (unsigned int j = 0; j < clusters->size(); j++) {
        if (j != clusterIndex) { // Exclude the cluster the image belongs to
            double distance = dist(image, clusters->at(j)->getCentroid(), 2); 

            if (distance < minDistance) {
                minDistance = distance;
                neighborCluster = clusters->at(j);
            }
        }
    }

    if (neighborCluster) {
        double totalDistance = 0.0;
        const std::vector<Image*>* neighborClusterImages = neighborCluster->getImages();

        for (auto neighborImage : *neighborClusterImages) {
            double distance = dist(image, neighborImage, 2); // Calculate distance between the image and images in the neighbor cluster
            totalDistance += distance;
        }

        int neighborClusterSize = neighborClusterImages->size();

        if (neighborClusterSize > 0) {
            double averageDistance = totalDistance / neighborClusterSize;
            return averageDistance;
        }
    }

    return 0.0; // No images in the neighbor cluster (or only itself), return 0
}

std::vector<double> Clustering::silhouette(std::vector<Image *> *images) {
    std::vector<double> s;
    double averageClusterSilhouette = 0.0;
    for (auto cluster : *clusters) {
        const std::vector<Image*> *clusterImages = cluster->getImages();
        //std::cout << "Cluster Num: " << cluster->getId() << std::endl;

        for (auto image : *clusterImages) {
            double ai = averageDistanceToCluster(image, clusters);
            double bi = averageDistanceToNeighborCluster(image, clusters);

            if (std::max(ai, bi) == 0) {
                s.push_back(0.0);
            } else {
                double si = (bi - ai) / std::max(ai, bi);
                //std::cout << "Image ID: " << image->getId() << std::endl;
                //std::cout << "Silhouette: " << si << std::endl;
                s.push_back(si);
                averageClusterSilhouette += si;
            }
        }
    }
    cout << "Silhouette: [";
    for (unsigned int i = 0; i < clusters->size(); i++) {
        double average = 0.0;
        std::vector<Image*> *clusterPoints = clusters->at(i)->getImages();
        for (unsigned int j = 0; j < clusterPoints->size(); j++) {
                average += s[clusterPoints->at(j)->getId()];
        }
        cout << average/clusterPoints->size() << ","; // Print average Silhouette value for each cluster
    }
    averageClusterSilhouette /= images->size();
    cout << " " << averageClusterSilhouette << "]\n";     // Print average silhouette value for whole dataset
    //I should clear the s here maybe
    return s; // Returning an empty vector since all values are printed for now,I will change it
}



