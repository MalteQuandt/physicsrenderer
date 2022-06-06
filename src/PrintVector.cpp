//
// Created by malte on 6/6/2022.
//

#include "PrintVector.h"

#include <iostream>

using namespace std;
using namespace phyren;

template<typename T> void PrintVector<T>::print() {
    std::cout << toString() << std::endl;
}
template<typename T> string PrintVector<T>::toString() {
    string buffer{};
    for(const string a : this) {
        buffer += a;
    }
    return buffer;
}