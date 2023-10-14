#include "../include/cube.hpp"

using namespace std;

HyperCube::HyperCube(int k, int M, int probes, int N, int R, std::list<Image> *data) {

    this->k = k;
    this->M = M;
    this->probes = probes;
    this->N = N;
    this->R = R;
    this->data = data;

    this->w = 10;

    this->vertices.reserve(k);
    this->cube = new HashTable(5);

    for (int i = 0; i < k; i++) {
        pair<HashFunction *, map<uint, char>*> temp = make_pair(new HashFunction(w), new map<uint, char>());
        this->vertices.push_back(temp);
    }

    for (auto &it : *data) {
        insert(&it);
    }
}

HyperCube::~HyperCube() {
    delete cube;

    for (auto &it : vertices) {
        delete it.first;
        delete it.second;
    }

    delete data;
}

void HyperCube::insert(void *pointer) {
    auto image = (Image *) pointer;
    string binary = "";

    for (auto &it : vertices) {
        pair<HashFunction *, map<uint, char>*> p = *it;
        uint h = p.first->h(image);

        char bit;
        auto f = p.second->find(h);
        if (f == p.second->end()) {
            int random = rand() % 2;
            (random == 0) ? bit = '0' : bit = '1';
            p.second->insert(make_pair(h, bit));
        } else {
            bit = f->second;
        }
        binary += bit;
    }

    cube->insert(binaryToUint(binary), image);

}