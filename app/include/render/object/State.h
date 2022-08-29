//
// Created by malte on 6/6/2022.
//

#ifndef PHYSICS_RENDERER_STATE_H
#define PHYSICS_RENDERER_STATE_H

#include <memory>
#include <vector>
#include "render/object/Drawable.tpp"
namespace phyren {
/**
 * Class representing the state of the physics eninge, being the relevant forces and the object in it at any current
 * point in time.
 */
template<int n=3, typename T=float>
class State {
public:
    /**
     * Generate a new state handler that carries the objects in the argument.
     *
     * @param objects the objects that the handler should start with
     */
    State(std::vector<std::shared_ptr<object::Drawable<n,T>>> objects) : objects{objects}{};
    State() {}
    /**
     * Add a new object to the state handler
     *
     * @param object the object to add to the state handler
     */
    void addObject(std::shared_ptr<object::Drawable<n, T>> object) {
        this->objects.push_back(object);
    };
    /**
     * Fetch the object at that position
     *
     * @param position the position to fetch from
     */
    void getObject(const unsigned int position) {
        return this->objects.at(position);
    }

    /**
     * Get the list of objects that currently reside in this state handler,
     * though as a const object.
     *
     * @return the list of objects this state handler handles
     */
     std::vector<std::shared_ptr<object::Drawable<n,T>>>& getObjects() {
         return this->objects;
     }


private:
    // The objects that currently reside in the physics engine
    std::vector<std::shared_ptr<object::Drawable<n,T>>> objects{};
};}


#endif //PHYSICS_RENDERER_STATE_H
