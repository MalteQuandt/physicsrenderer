//
// Created by malte on 5/10/2022.
//

#ifndef PHYSICS_RENDERER_INPUTPARSER_H
#define PHYSICS_RENDERER_INPUTPARSER_H

#include <deque>
#include <memory>
#include <string>

namespace phyren {
    // Class that encapsulates an console input parser and it's methods.
    // Used to set the initial engine state after startup
    class InputParser final {
    public:
        /**
         * Use the RAII paradigm to parse the input into string token vector,without the file name string
         *
         * @param argc length of input field
         * @param argv input array of c-strings
         */
        explicit InputParser(const int argc, char ** argv);
        /** Take the console inputs and store them as a token list
         *
         * @param argc, argc are the console inputs and the length of that array, respectively
         */
        void parse(const int argc, char**& argv);
        /** check, if the argument of this given name exists
         * Does not change the parser's internal state
         *
         * @param argName the name of the option
         * @return if the parameter exists in the queue
         */
        bool exists(const std::string &argName) const;
        /**
         * Return the front element of the list and remove it from the deque
         * @return the first element
         */
        std::string pop();
        /**
         * Get the first element in the queue
         *
         * @return the first element
         */
        const std::string& front();
        /**
         * Check, if there are elements in the list
         *
         * @return if there are elements
         */
        bool hasElements() const;
    private:
        // Store the parsed console arguments here
        std::unique_ptr<std::deque<std::string>> arguments{};

        /**
         * TODO
         * Handle a given arguments in the console input that
         * has parameters by itself
         *
         * @param the name of the argument
         */
        void handleArgument(const std::string &argName);
    };
}


#endif //PHYSICS_RENDERER_INPUTPARSER_H
