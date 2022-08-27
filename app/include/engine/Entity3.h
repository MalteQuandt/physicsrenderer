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
    /**
     * Simple entity wrapper for 3-Dimensional objects/entities
     */
    class Entity3 {
    public:
        Entity3() {}

    protected:
        //
        // ---------------------
        /* The Transformation data for this entity. */
        Transform<3> transform{};
        /* Model of this entity. */
        std::shared_ptr<Model> model{nullptr};

        // Scene Graph References
        // ----------------------
        /* Reference to the parent. */
        std::weak_ptr<Entity3> parent{};
        /* List of children entities. */
        std::list<std::unique_ptr<Entity3>> children{};
    };
}


