#include "../include/cube.hpp"

using namespace std;

HyperCube::HyperCube(int k, int M, int probes, int N, int R, std::vector<Image *> *data) {

    this->k = k;
    this->M = M;
    this->probes = probes;
    this->N = N;
    this->R = R;
    this->data = data;

    this->w = 100;

    this->vertices.reserve(k);
    this->cube = new HashTable((int)pow(2,k));

    for (int i = 0; i < k; i++) {
        pair<HashFunction *, unordered_map<uint, char> *> temp = make_pair(new HashFunction(w), new unordered_map<uint, char>());
        this->vertices.push_back(temp);
    }

    for (auto image : *data) {
        insert(image);
    }
}

HyperCube::~HyperCube() {
    delete cube;

    for (auto it : vertices) {
        delete it.first;
        delete it.second;
    }

    delete data;
}

string HyperCube::project(void *pointer) {
    auto image = (Image *) pointer;
    string binary;

    for (auto vertex : vertices) {
        uint h = vertex.first->h(image);

        char bit;
        auto f = vertex.second->find(h);
        if (f == vertex.second->end()) {
            auto random = vertex.first->coinFlip();
            (random == 0) ? bit = '0' : bit = '1';
            vertex.second->insert(make_pair(h, bit));
        } else {
            bit = f->second;
        }
        binary += bit;
    }

    return binary;
}

void HyperCube::insert(void *pointer) {
    auto image = (Image *) pointer;
    string binary = project(image);

    cube->insert(binaryToUint(binary), image);

}

void HyperCube::query(void *pointer) {
    auto image = (Image *) pointer;

    int probesChecked = 0;
    int pointsChecked;

    list<pair<uint, void *>> neighborsID, neighborsBucket;
    vector<pair<uint, double>> neighborsCube;
    list<uint> neighborsRNear;
    vector<int> *neighborVertices;

    chrono::duration<double> tCube{}, tTrue{};

    auto startTrue = chrono::high_resolution_clock::now();
    vector<double> neighborsTrue = getTrueNeighbors(image);
    auto endTrue = chrono::high_resolution_clock::now();

    tTrue = endTrue - startTrue;

    auto startCube = chrono::high_resolution_clock::now();
    string binary = project(image);
    neighborsID = cube->findBucket(binaryToUint(binary));

    probesChecked++;
    pointsChecked = (int)neighborsID.size();

    int hammingDist = 1;
    while (probesChecked < probes && pointsChecked < M) {
        neighborVertices = hammingDistance(binary, hammingDist++);
        for (auto i : *neighborVertices) {
            cout << "Checking vertex: " << i << endl;
            neighborsID.splice(neighborsID.begin(), cube->findBucket(i));
            pointsChecked = (int) neighborsID.size();
            probesChecked++;
            if (probesChecked == probes || pointsChecked > M) {
                break;
            }
        }
        delete neighborVertices;
    }

    for (auto neighbor : neighborsID) {
        auto neighborImage = (Image *) neighbor.second;
        double distance = dist(neighborImage, image, 2);

        neighborsCube.emplace_back(neighborImage->getId(), distance);
        if (distance < R) {
            neighborsRNear.push_back(neighborImage->getId());
        }
    }

    sort(neighborsCube.begin(), neighborsCube.end(), sortPairBySecond);

    auto endCube = chrono::high_resolution_clock::now();

    tCube = endCube - startCube;

    for (int i = 0; i < N; i++) {
        cout << "Nearest neighbor-" << i << ": " << neighborsCube[i].first << endl;
        cout << "distanceCube: " << neighborsCube[i].second << endl;
        cout << "distanceTrue: " << neighborsTrue[i] << endl;
    }

    cout << "tCube: " << tCube.count() << endl;
    cout << "tTrue: " << tTrue.count() << endl;
    cout << "R-near neighbors:" << endl;

    for (auto r : neighborsRNear) {
        cout << r << endl;
    }
}

vector<double> HyperCube::getTrueNeighbors(void *pointer) {
    auto image = (Image *) pointer;
    vector<double> neighborsTrue;

    for (auto it : *this->data) {
        neighborsTrue.push_back(dist(image, it, 2));
    }
    sort(neighborsTrue.begin(), neighborsTrue.end());
    return neighborsTrue;
}