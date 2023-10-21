#include "../include/lsh.hpp"

#include <algorithm>
#include <unordered_set> 
#include <iostream>

using namespace std;

// Constructor for the LSH (Locality Sensitive Hashing) class
LSH::LSH(int k, int L,int N, int R, vector<Image *> *data) {
    
    // Initialize the given parameters
    this->k = k;
    this->L = L;
    this->N = N;
    this->R = R;
    this->data = data;
    this->w = 10;

    // Dynamically allocate memory for hash tables
    this->hashTables = new HashTable*[L];
    for (int i = 0; i < L; i++) {
        // Get the dimension of the images, default to 0 if no images present
        int dimension = (data->size() > 0) ? static_cast<int>(data->at(0)->getCoords().size()) : 0;
        this->hashTables[i] = new HashTable((int)(pow(2,k) + 0.5));
    }

    // Populate hash tables with images
    for (auto& image : *data) {
        for (int i = 0; i < L; i++) {
            uint imageID = image->getId();
            this->hashTables[i]->insert(imageID, &image);
        } 
    }
}

// Function to get approximately nearest neighbors of a given image 'q' using LSH
vector<pair<double, Image*>> LSH::approximateNN(Image* q, unsigned int k) {
    vector<pair<double, Image*>> neighbors;
    unordered_set<uint> iterator;

    for (int i = 0; i < L; i++) {
        // Retrieve the list of images in the same bucket as the query image 'q'
        list<pair<uint,void*>> bucket = this->hashTables[i]->findBucket(q->getId());

        // Iterate over each image in the bucket
        for (const auto& entry : bucket){
            Image* currImage = static_cast<Image*>(entry.second);
            uint imageID = currImage->getId();

            // Check if the image has already been considered
            if (iterator.find(imageID) == iterator.end()){
                iterator.insert(imageID);
                double distance = dist(q,currImage,k);
                neighbors.push_back(make_pair(distance,currImage));
            }
        }
    }

    // Sort the neighbors based on distance
    sort(neighbors.begin(), neighbors.end());

    // Resize the neighbors list if it's larger than k
    if (neighbors.size() > k){
        neighbors.resize(k);
    }

    return neighbors;
}

// Function to find all images within a certain distance 'R' of a given image 'q'
vector<Image*> LSH::range_search(Image* q, double R) {
    vector<Image*> finalImages;
    unordered_set<uint> iterator;

    for (int i = 0; i < L; i++) {
        // Retrieve the list of images in the same bucket as the query image 'q'
        list<pair<uint,void*>> bucket = this->hashTables[i]->findBucket(q->getId());

        // Iterate over each image in the bucket
        for (const auto& entry : bucket){
            Image* currImage = static_cast<Image*>(entry.second);
            uint imageID = currImage->getId();

            // Check if the image has already been considered
            if (iterator.find(imageID) == iterator.end()){
                iterator.insert(imageID);
                double distance = dist(q,currImage,k);
                
                // Add the image if its distance is less than or equal to 'R'
                if (distance <= R){
                    finalImages.push_back(currImage);
                }
            }
        }
    }

    return finalImages;
}

// Destructor for the LSH class
LSH::~LSH() {
    // Delete each hash table
    for (int i = 0; i < L; i++) {
        delete hashTables[i];
    }

    // Delete the array holding pointers to hash tables
    delete[] hashTables;
}
