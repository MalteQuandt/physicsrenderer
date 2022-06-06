//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_PRINTVECTOR_H
#define PHYSICS_RENDERER_PRINTVECTOR_H

#include <vector>
#include <string>

namespace phyren {
/**
 * Vector with the special property of being able to be printed and converted to a string
 */
 template<typename T>
    class PrintVector : public std::vector<T> {
    public:
        /**
         * Print this vector to the console
         */
        void print();

        /**
         * Convert this vector to a string representation
         *
         * @return the string representation of this vector
         */
        std::string toString();
    };
}

#endif //PHYSICS_RENDERER_PRINTVECTOR_H
