//
// Created by malte on 8/26/2022.
//
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <concepts>

namespace phyren {
    // Make sure that the dimension can only be 2 or 3
    template<unsigned int d>
    concept between_2_and_3 = d == 3 || d == 2;

    /**
    * Simple transformation wrapper class for N Dimensions
    */
    template<unsigned int dimension> requires between_2_and_3<dimension>
    class Transform final {
    };

    /**
     * Specialize Transform for 3 Dimension
     */
    template<>
    class Transform<3> {
    public:
        explicit Transform(glm::vec3 position = glm::vec3{1.0f},
                           glm::vec3 scale = glm::vec3{1.0f},
                           glm::quat rotation = glm::quat{1.0f, 1.0f, 1.0f, 1.0f})
                : position{position}, scale{scale},
                  rotation{rotation} {}


        // Getter & Setter
        // --------------
        glm::vec3 &getPosition() {
            return this->position;
        }

        void setPosition(glm::vec<3, float> position) {
            this->position = position;
        }

        glm::vec3 &getScale() {
            return this->scale;
        }

        void setScale(glm::vec3 scale) {
            this->scale = scale;
        }

        glm::quat &getRotation() {
            return this->rotation;
        }

        void setRotation(glm::quat rotation) {
            this->rotation = rotation;
        }
        // Rule of 5
        // ---------
        explicit Transform(const Transform& trans) : position{trans.position}, scale{trans.scale}, rotation{trans.rotation}{}
        explicit Transform(Transform&& trans) : position{std::move(trans.position)}, scale{std::move(trans.scale)}, rotation{std::move(trans.rotation)}{}
        Transform& operator=(const Transform& trans) {
            if(this != &trans) {
                position = trans.position;
                scale = trans.scale;
                rotation = trans.rotation;
            }
            return *this;
        }
        Transform& operator=(Transform&& trans) {
            if(this != &trans) {
                std::swap(position, trans.position);
                std::swap(scale, trans.scale);
                std::swap(rotation, trans.rotation);
            }
            return *this;
        }

    protected:
        /* The position in world space */
        glm::vec3 position{};
        /* The scale of the entity in world space*/
        glm::vec3 scale{};
        /* The rotation in world space*/
        glm::quat rotation{};
    };

    /**
     * Specialize Transform for 2 Dimension
     */
    template<>
    class Transform<2> {
    public:
        explicit Transform(glm::vec2 position = glm::vec2{1.0f},
                           glm::vec2 scale = glm::vec2{1.0f},
                           glm::vec2 rotation = glm::vec2{1.0f})
                : position{position}, scale{scale},
                  rotation{rotation} {}

        // Getter & Setter
        // --------------
        glm::vec2 &getPosition() {
            return this->position;
        }

        void setPosition(glm::vec2 position) {
            this->position = position;
        }

        glm::vec2 &getScale() {
            return this->scale;
        }

        void setScale(glm::vec2 scale) {
            this->scale = scale;
        }

        glm::vec2 &getRotation() {
            return this->rotation;
        }

        void setRotation(glm::vec2 rotation) {
            this->rotation = rotation;
        }

    protected:
        /* The position in world space */
        glm::vec2 position{};
        /* The scale of the entity in world space*/
        glm::vec2 scale{};
        /* The rotation in world space*/
        glm::vec2 rotation{};
    };
}


