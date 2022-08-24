//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_CUBE_TPP
#define PHYSICS_RENDERER_CUBE_TPP

#include "render/object/Aggregate.tpp"
#include "render/Line.h"
#include "render/ModelLoader.h"

namespace phyren {
    namespace object {
        template<int n = 3, typename T=float>
        class Cube : public Aggregate<n, T>{
        public:
            /**
             * Generate a new cube object.
             */
            Cube() : Aggregate<n, T>{ModelLoader::getInstance().getModel(PreModelType::CUBE)}{}
            /**
             * Draw this cube to the screen
             *
             * @param shader the shader to draw with
             */
            void draw(std::shared_ptr<ShaderProgram> shader) override {
                this->model->render(shader);
            }
            /**
             * Integrate the state of this object into the next frame
             *
             * @param delta the time between the last iteratino and now
             *
             * @return the new state
             */
            PhysicsObject<n, T>& integrate(float delta) override {
                return *this;
            }
        };

    }
}

#endif //PHYSICS_RENDERER_CUBE_TPP
