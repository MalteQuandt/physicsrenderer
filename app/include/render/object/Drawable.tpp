//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_DRAWABLE_TPP
#define PHYSICS_RENDERER_DRAWABLE_TPP

#include <memory>

#include "render/ShaderProgram.h"
#include "PhysicsObject.tpp"

namespace phyren {
    namespace object {
        /**
         * An Interface Class representing all physical objects that can be drawn onto the screen
         */
        template<int n = 3, typename T=float>
        class Drawable : public PhysicsObject<n, T> {
        public:
            /**
             * Render this object to the screen
             * @param shader the shaderprogram to user for rendering
             */
            virtual void draw(std::shared_ptr<ShaderProgram> shader) = 0;
        };
    }
}


#endif //PHYSICS_RENDERER_DRAWABLE_TPP
