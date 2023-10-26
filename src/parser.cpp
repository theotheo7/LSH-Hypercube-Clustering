#include "../include/parser.hpp"

using namespace std;

Parser::Parser() = default;

Parser::~Parser() = default;

vector<Image *> *Parser::readInputFile(const string &fileName) {
    uint32_t magicNumber, imageNumber, rowNumber, columnNumber;
    ifstream ifs(fileName, ios::binary);

    auto imageVector = new vector<Image *>;

    if (!ifs.is_open()) {
        cerr << "Failed to open the input file!" << endl;
        return imageVector;
    }

    cout << "Successfully opened the input file!" << endl;

    ifs.read(reinterpret_cast<char *>(&magicNumber), sizeof(int));
    magicNumber = ntohl(magicNumber);

    ifs.read(reinterpret_cast<char *>(&imageNumber), sizeof(int));
    imageNumber = ntohl(imageNumber);

    ifs.read(reinterpret_cast<char *>(&rowNumber), sizeof(int));
    rowNumber = ntohl(rowNumber);

    ifs.read(reinterpret_cast<char *>(&columnNumber), sizeof(int));
    columnNumber = ntohl(columnNumber);

    cout << "Magic number is: " << magicNumber << endl;
    cout << "Image number is: " << imageNumber << endl;
    cout << "Row number is: " << rowNumber << endl;
    cout << "Column number is: " << columnNumber << endl;

    const uint32_t imageSize = rowNumber * columnNumber;
    vector<unsigned char> inputVector(imageSize);

    for (uint i = 0; i < imageNumber; i++) {

        ifs.read(reinterpret_cast<char *>(inputVector.data()), imageSize);

        auto coords = new vector<unsigned char>(inputVector);
        imageVector->push_back(new Image(i+1, coords));
    }

    cout << "Finished reading images!" << endl;

    ifs.close();
    return imageVector;
}

vector<Image *> *Parser::readQueryFile(const std::string &fileName) {
    uint32_t magicNumber, imageNumber, rowNumber, columnNumber;
    ifstream ifs(fileName, ios::binary);

    auto queryImages = new vector<Image *>;

    if (!ifs.is_open()) {
        cerr << "Failed to open the query file!" << endl;
        return queryImages;
    }

    ifs.read(reinterpret_cast<char *>(&magicNumber), sizeof(int));
    magicNumber = ntohl(magicNumber);

    ifs.read(reinterpret_cast<char *>(&imageNumber), sizeof(int));
    imageNumber = ntohl(imageNumber);

    ifs.read(reinterpret_cast<char *>(&rowNumber), sizeof(int));
    rowNumber = ntohl(rowNumber);

    ifs.read(reinterpret_cast<char *>(&columnNumber), sizeof(int));
    columnNumber = ntohl(columnNumber);

    const uint32_t imageSize = rowNumber * columnNumber;
    vector<unsigned char> inputVector(imageSize);

    for (int i = 0; i < 10; i++) {
        ifs.read(reinterpret_cast<char *>(inputVector.data()), imageSize);

        auto coords = new vector<unsigned char>(inputVector);
        queryImages->push_back(new Image(i+1, coords));
    }

    ifs.close();
    return queryImages;
}