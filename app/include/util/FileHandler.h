#pragma once

#include <string>

namespace phyren {
    /**
     * All the file specific functions in this application
     */
    namespace filehandling {
        /**
         * Load all the file content as a string
         * @param fileName the name of the file
         * @return buffer containing the file information
         */
        std::string loadFileString(const std::string &fileName);
    };
}