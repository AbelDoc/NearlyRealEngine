
    /**
     * @file NRE_ShapeFactory.hpp
     * @brief Declaration of Engine's World's Object : ShapeFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../Cell/NRE_Cell.hpp"

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
             * @class ShapeFactory
             * @brief Manage the creation of shape, used to create surfaces with cells
             */
            class ShapeFactory {
                public :    // Static
                    /**
                     * Create an array of cells to describe a circle shape
                     * @param  radius   the circle radius
                     * @param  center   the circle center
                     * @param  gridSize the cells grid resolution
                     * @return the cells array
                     */
                    static Utility::Vector<Cell> createCircle(float radius, Math::Point2D<float> const& center = {0, 0}, Math::Vector2D<unsigned int> const& gridSize = {6, 6});
            };

        }
    }

    #include "NRE_ShapeFactory.tpp"
