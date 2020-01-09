
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
                    Math::Point4D<float> position;     /**< The light's position */
                    Math::Vector3D<float> intensities; /**< The light's colors intensities */
                    Math::Vector3D<float> direction;   /**< The light's direction */
                    float angle;                       /**< The light's angle */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a light from all needed parameters
                         * @param coord the light's position
                         * @param color the light's colors intensities
                         * @param dir   the light's direction
                         * @param a     the light's angle
                         */
                        Light(Math::Point4D<float> const& coord, Math::Vector3D<float> const& color, Math::Vector3D<float> const& dir, float a) : position(coord), intensities(color), direction(dir), angle(a) {
                        }

            };
        }
    }
