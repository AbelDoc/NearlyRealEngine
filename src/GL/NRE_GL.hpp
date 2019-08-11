
    /**
     * @file GL/NRE_GL.hpp
     * @brief Declaration of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 11/08/2019
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
         * @namespace GL
         * @brief Engine's GL module
         */
        namespace GL {

            /**
             * Clear the context screen and fill it with the given color
             * @param r the clear color red value
             * @param g the clear color green value
             * @param b the clear color blue value
             * @param a the clear color alpha value
             */
            void clearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

            /**
             * Clear the context screen and fill it with the given color
             * @param color the clear color
             */
            void clearColor(Math::Vector4D<float> const& color);

            /**
             * Clear the context screen and fill it with the given color
             * @param color the clear color rgb values
             * @param a     the clear color alpha value
             */
            void clearColor(Math::Vector3D<float> const& color, float a = 1.0f);

        }
    }

    #include "NRE_GL.tpp"
