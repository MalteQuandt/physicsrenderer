//
// Created by malte on 5/10/2022.
//

#ifndef PHYSICS_RENDERER_FILEHANDLER_H
#define PHYSICS_RENDERER_FILEHANDLER_H

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
        std::string loadFileString(const std::string& fileName);
    };
}



#endif //PHYSICS_RENDERER_FILEHANDLER_H
