#include "../include/utils.hpp"

using namespace std;

double dist(void *a, void *b, int k) {
    auto *imageA = (Image *) a;
    auto *imageB = (Image *) b;

    if (imageA->getCoords().size() != imageB->getCoords().size()) {
        return -1;
    }

    double dist = 0.0;
    for (size_t i = 0; i < imageA->getCoords().size(); i++) {
        dist += pow((double) (imageA->getCoords().at(i) - imageB->getCoords().at(i)), k);
    }

    return pow(dist, (double) 1/k);
}

uint binaryToUint(string binary) {
    uint decimal = 0;
    int base = 1;

    int len = (int) binary.length();
    for (int i = len - 1; i >= 0; i--) {

        if (binary[i] == '1') {
            decimal += base;
        }

        base *= 2;
    }

    return decimal;
}

vector<int> *hammingDistance(const string& vertex, int distance) {
    vector<string> uniq;
    set<string> working;
    working.insert(vertex);
    uniq.push_back(vertex);
    char newC;

    for (int i = 1; i <= distance; i++) {
        vector<string> temp;
        for (auto &s: uniq) {
            int j = 0;
            for (auto &c: s) {
                string tempVert = s;
                (c == '0') ? (newC = '1') : (newC = '0');
                tempVert[j++] = newC;
                if (working.find(tempVert) == working.end()) {
                    temp.push_back(tempVert);
                    working.insert(tempVert);
                }
            }
        }
        uniq = temp;
    }

    auto* hamming = new vector<int>;
    for (string &ch: uniq) {
        hamming->push_back((int)binaryToUint(ch));
    }
    return hamming;
}

bool sortPairBySecond(const pair<uint, double> &a, const pair<uint, double> &b) {
    return a.second < b.second;
}