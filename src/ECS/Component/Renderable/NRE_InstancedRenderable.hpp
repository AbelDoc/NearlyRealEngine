
    /**
     * @file NRE_Renderable.hpp
     * @brief Declaration of Engine's ECS's Object : InstancedRenderable
     * @author Louis ABEL
     * @date 30/10/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <memory>
    
    #include "NRE_Model.hpp"

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
             * @class InstancedRenderable
             * @brief Manage an instanced drawable object
             */
            class InstancedRenderable {
                public:    //Fields
                    const Model::Model* model;   /**< The rendered instanced model */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct an instanced renderable from an instanced model
                         * @param m the instanced model to take the ownership
                         */
                        InstancedRenderable(const Model::Model* m) : model(m) {
                        }
            };
        }
    }
