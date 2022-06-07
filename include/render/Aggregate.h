//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_AGGREGATE_H
#define PHYSICS_RENDERER_AGGREGATE_H

#include <memory>

#include "Drawable.h"

#include "render/Model.h"

namespace phyren {
    namespace object {

        /**
         * Object representing a simple aggregate data type, meaning a type with a model
         * @tparam n
         * @tparam T
         */
        template<int n = 3, typename T=float>
        class Aggregate : public Drawable<n, T> {
        public:
            Aggregate() {};

            /**
             * Fetch the model of the aggreagate type
             * @return the model of this type
             */
            std::shared_ptr<Model> getModel() {
                return this->model;
            }

            void draw(std::shared_ptr<ShaderProgram> shader) override {
                this->model->render(shader);
            }

        protected:
            /**
             * Generate the Aggregate object
             * @param model the model for this aggreagate
             */
            Aggregate(std::shared_ptr<Model> model) : model{model} {}

        protected:
            std::shared_ptr<Model> model{};
        };
    }
}


#endif //PHYSICS_RENDERER_AGGREGATE_H
