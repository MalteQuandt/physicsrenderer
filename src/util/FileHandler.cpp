//
// Created by malte on 5/10/2022.
//

#include "util/FileHandler.h"

#include <fstream>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace phyren::filehandling;
using namespace std;

// Return the file contents as a string by value
string phyren::filehandling::loadFileString(const std::string &fileName) {
    string buffer{};
    ifstream file{};
    stringstream filestream{};
    // If the bit get set, throw a failure exception
    file.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        file.open(fileName);
        filestream << file.rdbuf();
        buffer = filestream.str();
        file.close();
    } catch (ifstream::failure &e) {
        cerr <<
             "[ERROR] The file " + fileName + " could not be read!\n" + e.what()
             << endl;
    }
    return buffer;
}


