#include "../include/parser.hpp"

using namespace std;

Parser::Parser() {}

Parser::~Parser() {}

void Parser::readInputFile(std::string fileName) {
    ifstream ifs(fileName, ios::binary);

    if (!ifs.is_open()) {
        cerr << "Failed to open the input file!" << endl;
        return;
    }

    cout << "Successfully opened the file!" << endl;

    ifs.close();
    return;
}