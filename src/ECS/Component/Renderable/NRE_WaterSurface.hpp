
    /**
     * @file NRE_WaterSurface.hpp
     * @brief Declaration of Engine's ECS's Object : WaterSurface
     * @author Louis ABEL
     * @date 13/02/2020
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
             * @class WaterSurface
             * @brief Manage a single drawable liquid object
             */
            class WaterSurface {
                public:    //Fields
                    const Model::Model* model;    /**< The rendered model */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a renderable from a model
                         * @param m the model to take the ownership
                         */
                        WaterSurface(const Model::Model* m) : model(m) {
                        }
            };
        }
    }
