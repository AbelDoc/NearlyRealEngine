
    /**
     * @file NRE_Terrain.hpp
     * @brief Declaration of Engine's ECS's Object : Terrain
     * @author Louis ABEL
     * @date 15/04/2020
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <memory>
    
    #include "../../../World/Model/NRE_ChunkModel.hpp"

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace ECS
         * @brief Engine's ECS module
         */
        namespace ECS {

            /**
             * @class Terrain
             * @brief Manage a single chunk to render
             */
            class Terrain {
                public:    // Fields
                    Model::Mesh const& mesh;    /**< The rendered mesh */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a renderable from a mesh
                         * @param m the mesh
                         */
                        Terrain(Model::Mesh const& m) : mesh(m) {
                        }
            };
        }
    }
