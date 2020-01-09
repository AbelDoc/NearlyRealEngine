
    /**
     * @file NRE_Renderable.hpp
     * @brief Declaration of Engine's ECS's Object : Renderable
     * @author Louis ABEL
     * @date 08/01/2020
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
             * @class Renderable
             * @brief Manage a single drawable object
             */
            class Renderable {
                public:    //Fields
                    const Model::Model* model;    /**< The rendered model */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a renderable from a model
                         * @param m the model to take the ownership
                         */
                        Renderable(const Model::Model* m) : model(m) {
                        }
            };
        }
    }
