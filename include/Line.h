//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_LINE_H
#define PHYSICS_RENDERER_LINE_H

#include <memory>
#include <vector>

#include <glm/vec3.hpp>

#include "render/ShaderProgram.h"

namespace phyren {
    /**
     * Represents a line that can be drawn into the world space
     */
    class Line {
    public:
        /**
         * Generate a line and draw it to the world, starting from start and going until end
         *
         * @param points the points on the line that this object represents
         *
         * @return the object representing the line in world space
         */
        static std::shared_ptr<Line> generate(std::vector<glm::vec3> points);

        /**
         * Draw the line into world space using the shader program
         *
         * @param shader the shader to use for this line
         */
        void draw(std::shared_ptr<ShaderProgram> shader);

        Line &operator=(const Line &l) = delete;

        Line &operator=(Line &&l);

        Line(const Line &l) = delete;

        Line(Line &&l);

    private:
        // the points on this line
        std::vector<glm::vec3> points;

        // the reference values
        unsigned int VBO{0};
        unsigned int VAO{0};

        /**
         * Generate a new line object in the world space
         *
         * @param points the points on the line
         */
        Line(std::vector<glm::vec3> points);

        /**
         * Initialize this mesh object
         *
         * @param points the points on this line
         */
        void setup(std::vector<glm::vec3> points);
    };
}


#endif //PHYSICS_RENDERER_LINE_H
