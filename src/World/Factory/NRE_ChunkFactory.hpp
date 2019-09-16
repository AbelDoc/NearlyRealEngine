/**
     * @file NRE_ChunkFactory.hpp
     * @brief Declaration of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../Chunk/NRE_Chunk.hpp"

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
                     * Create a cloud of voxels (which isovalue represent the distance from the center) and then store the resulting cells into a given chunk
                     * @param target     the target chunk
                     * @param resolution the generation resolution
                     * @param radius     the sphere radius
                     */
                    static void createSphere(Chunk& target, float resolution, float radius);
            };

        }
    }

    #include "NRE_ChunkFactory.tpp"
