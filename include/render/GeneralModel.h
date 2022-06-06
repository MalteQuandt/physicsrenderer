//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_GENERALMODEL_H
#define PHYSICS_RENDERER_GENERALMODEL_H


#include "render/Aggregate.h"
#include "Line.h"
#include "render/ModelLoader.h"

namespace phyren {
    namespace object {
        template<int n = 3, typename T=float>
        class GeneralModel : public Aggregate<n, T> {
        public:
            /**
             * Generate a new general model object.
             *
             * @parm path the path to the model location
             */
            GeneralModel(std::string path) : Aggregate<n, T>::model{ModelLoader::getInstance().load(path)}{}

            /**
             * Draw this general model to the screen
             *
             * @param shader the shader to draw with
             */
            void draw(std::shared_ptr<ShaderProgram> shader) override{
                this->model->render(shader);
            };

            /**
             * Integrate the state of this object into the next frame
             *
             * @param delta the time between the last iteratino and now
             *
             * @return the new state
             */
            PhysicsObject<n, T> &integrate(float delta) override {
                return *this;
            }
        };

    }
}


#endif //PHYSICS_RENDERER_GENERALMODEL_H
