//
// Created by malte on 5/10/2022.
//

#include <algorithm>

#include "InputParser.h"

namespace phyren {
    using namespace std;
    InputParser::InputParser(const int argc, char **argv) : arguments(make_unique<deque<string>>(argv+1, argc+argv)){}
    // Parse argv into token stream
    void InputParser::parse(const int argc, char**& argv){
        arguments = make_unique<deque<string>>(argv, argv+argc);
    }
    bool InputParser::exists(const string &argName) const {
        return find(arguments->begin(), arguments->end(), argName) != arguments->end();
    }
    string InputParser::pop() {
        string temp{std::move(arguments->front())};
        arguments->pop_front();
        return temp;
    }
    bool InputParser::hasElements() const {
        return !arguments->empty();
    }

    const std::string &InputParser::front() {
        return this->arguments->front();
    }
}