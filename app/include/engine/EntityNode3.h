//
// Created by malte on 8/27/2022.
//

#pragma once

#include <engine/Entity3.h>

namespace phyren::engine {
    /**
    * Scene Graph Node component for the
    */
    class EntityNode3 {
    public:
        /**
         * @brief   Create a new entity node for a 3-Dimensional entity
         *
         * @param   entity the entity entry data for this node
         * @param   parent the parent of the current entity, or 'nullptr' for root
         * @param   nodes the child entities, or an empty list for a leaf node
         */
        EntityNode3(Entity3 entity, std::shared_ptr<EntityNode3> parent = std::shared_ptr<EntityNode3>{nullptr},
                    std::list<std::unique_ptr<EntityNode3>> nodes = std::list<std::unique_ptr<EntityNode3>>{});
        /**
         * @brief   Add a child to the list.
         *
         * @tparam  Ts parameter for EntityNode3.
         * @param   childArgs the arguments needed to construct a new child.
         */
        template<typename... Ts>
        void addChild(Ts... childArgs) {
            this->children.emplace_back(std::make_unique<EntityNode3>(childArgs...));
            this->children.back()->parent = this;
        }
    private:
        // Stored Entity
        // -------------
        Entity3 entity;
        // Scene Graph References
        // ----------------------
        /* Reference to the parent.*/
        EntityNode3 *parent;
        /* List of children entities.*/
        std::list<std::unique_ptr<EntityNode3>> children;
    };
}



