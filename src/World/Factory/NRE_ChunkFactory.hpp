
    /**
     * @file NRE_ChunkFactory.hpp
     * @brief Declaration of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../NRE_World.hpp"

    #include "../Polygonizer/NRE_ChunkPolygonizer.hpp"

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    #pragma GCC diagnostic ignored "-Wconversion"
    #pragma GCC diagnostic ignored "-Wfloat-conversion"
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    #pragma GCC diagnostic ignored "-Wstrict-aliasing"

    #include "../../lib/FastNoise/FastNoise.h"

    #pragma GCC diagnostic pop

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World module
         */
        namespace World {

            /**
             * @class ChunkFactory
             * @brief Manage the creation of chunk
             */
            class ChunkFactory {
                public :    // Static
                    /**
                     * Create a cloud of voxels (which isovalue represent the terrain height) and then store the resulting cells into a given chunk
                     * @param target the target chunk
                     */
                    static void createTerrain(Chunk& target);
            };

        }
        
        
    }

    #include "NRE_ChunkFactory.tpp"
