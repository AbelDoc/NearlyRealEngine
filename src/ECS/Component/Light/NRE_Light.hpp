
    /**
     * @file NRE_Light.hpp
     * @brief Declaration of Engine's ECS's Object : Light
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once
    
     #include <Header/NRE_Math.hpp>

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
             * @class Light
             * @brief Manage a light object
             */
            class Light {
                public:     //Fields
                    Math::Point3D<float> position;     /**< The light's position */
                    Math::Vector3D<float> intensities; /**< The light's colors intensities */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a light from all needed parameters
                         * @param coord the light's position
                         * @param color the light's colors intensities
                         */
                        Light(Math::Point3D<float> const& coord, Math::Vector3D<float> const& color) : position(coord), intensities(color) {
                        }

            };
        }
    }
