//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_PRIMITIVE_H
#define PHYSICS_RENDERER_PRIMITIVE_H

#include "Drawable.h"

namespace phyren {
    namespace object {
        enum class PrimitiveType {
            LINE
        };
        /**
         * Class representing an abstract, primitive data type
         */
        template<int n = 3, typename T=float>
        class Primitive : public Drawable<n, T> {};
    }
}


#endif //PHYSICS_RENDERER_PRIMITIVE_H
