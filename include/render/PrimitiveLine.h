//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_PRIMITIVELINE_H
#define PHYSICS_RENDERER_PRIMITIVELINE_H

#include <vector>

#include "Primitive.h"
#include "Line.h"

#include "glm/vec3.hpp"

namespace phyren {
    namespace object {

        /**
         * Class representing a line primitive that can be drawn into the world
         */
        template<int n = 3, typename T=float>
        class PrimitiveLine : public Primitive<n, T> {
        public:
            /**
             * Generate a new line primitive
             * @param points the points that this line is made out of
             *
             */
            std::shared_ptr<PrimitiveLine> generate(std::vector<glm::vec<n, T>> points) {
                return std::make_shared<glm::vec<n, T>>(std::move(PrimitiveLine(points)));
            }

            /**
             * Draw this primitive into world space
             *
             * @param shader the shader program to use for drawing
             */
            void draw(std::shared_ptr<ShaderProgram> shader) override {
                this->line->draw(shader);
            }

            /**
             * Integrate the state of this object by the new delta time of the past frame.
             *
             * @param delta the delta time of the last frame
             *
             * @return the next state of this object
             */
            PhysicsObject<n, T> &integrate(float delta) override {
                return *this;
            };

            PrimitiveLine(PrimitiveLine &&p) {
                swap(this->line, p.line);
                swap(this->position, p.position);
            }

            PrimitiveLine(const PrimitiveLine &p) = delete;

            PrimitiveLine &operator=(PrimitiveLine &&p) {

                if (this != &p) {
                    swap(this->line, p.line);
                    swap(this->position, p.position);
                }
                return *this;
            }

            PrimitiveLine &operator=(const PrimitiveLine &p) = delete;

        private:
            // The line storage
            std::shared_ptr<Line> line;

            /**
             * Generate a new line primitive
             *
             * @param points the points that this line is made out of
             */
        };
    }
}


#endif //PHYSICS_RENDERER_PRIMITIVELINE_H
