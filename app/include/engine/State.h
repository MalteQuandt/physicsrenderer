#pragma once

#include <render/Shader.h>

#include <memory>


namespace phyren::engine {
    /**
     * @brief State of the engine
     * @date 28.8.2022
     * @author malte quandt
     */
    class State {
    public:
        /**
         * @brief   Integrate the current world state
         *
         * @param   delta the time to integrate the world state by
         *
         * @return  the new world state
         */
        State integrate(float delta);

        void render(std::shared_ptr<Shader>);

        // Delete the rule of 5
        State(const State&) = delete;
        State(State&&) = delete;

        State& operator=(const State&) = delete;
        State& operator=(State&&) = delete;
    private:

    };
}