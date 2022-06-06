//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_FIELD_H
#define PHYSICS_RENDERER_FIELD_H

#include "render/Aggregate.h"
#include "Line.h"

namespace phyren {
    namespace object {
        template<int n = 3, typename T=float>
        class Field : public Aggregate<n, T>{
        public:
            /**
             * Generate a new field with lines amount of lines
             *
             * @param lines  the lines of this field
             */
            Field(unsigned int lines) : line{move(generateField(lines))}{};
            /**
             * Draw this field to the screen
             *
             * @param shader the shader to draw with
             */
            void draw(std::shared_ptr<ShaderProgram> shader) override {
                this->line->draw(shader);
            }
            PhysicsObject<n, T>& integrate(float delta) override{
                return *this;
            };
        private:
            // The lines are contained in here
            std::shared_ptr<Line> line;

            /**
             * Generate field using lines
             *
             * @return the "mesh" of lines
             */
            std::shared_ptr<Line> generateField(const unsigned int lines) {
                std::vector<glm::vec3> points{};
                for (unsigned int i{0}; i <= lines; i++) {
                    points.push_back(glm::vec3{
                            static_cast<float>(i) / lines, 0.0f, 1.0f
                    });
                    points.push_back(glm::vec3{
                            static_cast<float>(i) / lines, 0.0f, 0.0f
                    });
                }
                for (unsigned int j{0}; j <= lines; j++) {
                    points.push_back(glm::vec3{
                            1.0f, 0.0f, static_cast<float>(j) / lines
                    });
                    points.push_back(glm::vec3{
                            0.0f, 0.0f, static_cast<float>(j) / lines
                    });
                }
                return Line::generate(points);
            }

        };

    }
}


#endif //PHYSICS_RENDERER_FIELD_H
