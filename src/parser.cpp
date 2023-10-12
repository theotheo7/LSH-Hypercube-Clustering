#include "../include/parser.hpp"

using namespace std;

Parser::Parser() {}

Parser::~Parser() {}

void Parser::readInputFile(const std::string fileName) {
    uint32_t magicNumber, imageNumber, rowNumber, columnNumber;
    ifstream ifs(fileName, ios::binary);

    if (!ifs.is_open()) {
        cerr << "Failed to open the input file!" << endl;
        return;
    }

    cout << "Successfully opened the file!" << endl;

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

    for (int i = 1; i <= imageNumber; i++) {
        vector<char> inputVector(imageSize);
        ifs.read(inputVector.data(), imageSize);

        auto image = new Image(i, inputVector);

        delete image;
    }

    ifs.close();
}