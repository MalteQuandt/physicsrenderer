//
// Created by malte on 8/26/2022.
//

#pragma once

#include <cmake/Configuration.hpp>
#include <render/Model.h>
#include <engine/Transform.tpp>

#include <memory>
#include <list>

namespace phyren {
    namespace engine {

        /**
         * Simple entity wrapper for 3-Dimensional objects/entities
         */
        class Entity3 {
        public:
            /**
             * Create a new 3-Dimensional Entity
             *
             * @param transform
             * @param model
             * @param parent
             */
            Entity3(Transform<3> transform=Transform<3>{},
                    std::shared_ptr<Model> model=nullptr);

            // Getter & Setter
            // ---------------
            Transform<3> &getTransform();
            void setTransform(const Transform<3> transform);

            std::shared_ptr<Model> getModel();
            void setModel(const std::shared_ptr<Model> model);

        protected:
            // Components
            // ----------
            /* The Transformation data for this entity. */
            Transform<3> transform;
            /* Model of this entity. */
            std::shared_ptr<Model> model;
        };
    }
}


