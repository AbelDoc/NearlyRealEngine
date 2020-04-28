    
    /**
     * @file NRE_Water.hpp
     * @brief Declaration of Engine's ECS's Object : Water
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
             * @class Water
             * @brief Manage a single water chunk to render
             */
            class Water {
                public:    // Fields
                    Model::Mesh const& mesh;    /**< The rendered mesh */
                
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a renderable from a mesh
                         * @param m the mesh
                         */
                        Water(Model::Mesh const& m) : mesh(m) {
                        }
            };
        }
    }
    