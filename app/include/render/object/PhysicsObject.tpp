//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_PHYSICSOBJECT_TPP
#define PHYSICS_RENDERER_PHYSICSOBJECT_TPP

#include "glm/vec3.hpp"

namespace phyren {
    namespace object {
        /**
         * Class representing a simple physical object that can be integrated over a span of time
         */
        template <int n = 3, typename T=float>
        class PhysicsObject {
        public:
            /**
             * Integrate the position in world space of this object
             *
             * @param delta the delta time that happened in this frame
             */
            virtual PhysicsObject& integrate(float delta) {
                return *this;
            };
            /**
             * Set the position in world space of this object.
             *
             * @param position the new position as a vector
             */
            virtual void setPosition(glm::vec<n, T> position) {
                this->position = position;
            }

            /**
             * Get the position in world space of this object
             *
             * @return the position in world space of this object
             */
            virtual glm::vec<n, T> getPosition() {
                return this->position;
            }

            /**
             * Set the scale of this object in world space
             *
             * @param scale the size of the object
             */
            virtual void setScale(glm::vec<n, T> scale) {
                this->scale = scale;
            }

            /**
             * Get the scale of this object in world space
             *
             * @return the scale of this object
             */
            virtual glm::vec<n, T> getScale() {
                return this->scale;
            }
        protected:
            // The current position in world space
            glm::vec<n, T> position{};
            // The scale of this object
            glm::vec<n, T> scale{};
        };
    }
}


#endif //PHYSICS_RENDERER_PHYSICSOBJECT_TPP
