
    /**
     * @file NRE_Model.hpp
     * @brief Declaration of Engine's ECS's Object : Model
     * @author Louis ABEL
     * @date 15/04/2020
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <memory>
    
    #include "../../../Model/Model/NRE_Model.hpp"


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
             * @class Model
             * @brief Manage a single drawable object
             */
            class Model {
                public:    //Fields
                    const NRE::Model::Model* mesh;    /**< The rendered model */
                    Math::Matrix4x4<float> model;     /**< The model matrix */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a renderable from a model
                         * @param m the model
                         */
                        Model(const NRE::Model::Model* m) : mesh(m), model(Math::Matrix4x4<float>::IDENTITY) {
                        }
            };
        }
    }
