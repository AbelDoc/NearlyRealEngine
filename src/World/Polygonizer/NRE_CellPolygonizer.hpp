
    /**
     * @file NRE_CellPolygonizer.hpp
     * @brief Declaration of Engine's World's Object : CellPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../../Header/NRE_GL.hpp"
    #include "../../Header/NRE_Buffer.hpp"
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
             * @class CellPolygonizer
             * @brief Manage the transformation of cells into a rendering mesh
             */
            class CellPolygonizer {
                private :   // Static
                    static constexpr float lookupTable[16][27] = {
                        {
                        },
                        {
                            0.0f, 1.0f, 0.0f,       0.5f, 1.0f, 0.0f,       0.0f, 0.5f, 0.0f
                        },
                        {
                            1.0f, 0.5f, 0.0f,       0.5f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        },
                        {
                            1.0f, 0.5f, 0.0f,       0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,
                            1.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        },
                        {
                            1.0f, 0.0f, 0.0f,       0.5f, 0.0f, 0.0f,       1.0f, 0.5f, 0.0f
                        },
                        {
                            0.5f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,
                            1.0f, 0.5f, 0.0f,       0.5f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        },
                        {
                            1.0f, 0.0f, 0.0f,       0.5f, 0.0f, 0.0f,       0.5f, 1.0f, 0.0f,
                            1.0f, 0.0f, 0.0f,       0.5f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        },
                        {
                            1.0f, 1.0f, 0.0f,       1.0f, 0.0f, 0.0f,       0.5f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,       0.5f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,
                            1.0f, 1.0f, 0.0f,       0.0f, 0.5f, 0.0f,       0.0f, 1.0f, 0.0f
                        },
                        {
                            0.0f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,       0.5f, 0.0f, 0.0f
                        },
                        {
                            0.0f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f,       0.5f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f,       0.5f, 1.0f, 0.0f,       0.5f, 0.0f, 0.0f
                        },
                        {
                            1.0f, 0.0f, 0.0f,       0.5f, 0.0f, 0.0f,       1.0f, 0.5f, 0.0f,
                            0.0f, 1.0f, 0.0f,       0.5f, 1.0f, 0.0f,       0.0f, 0.5f, 0.0f
                        },
                        {
                            0.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f,       1.0f, 0.5f, 0.0f,
                            0.0f, 1.0f, 0.0f,       1.0f, 0.5f, 0.0f,       0.5f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f,       0.5f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f
                        },
                        {
                            0.0f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,       1.0f, 0.5f, 0.0f,
                            0.0f, 0.0f, 0.0f,       1.0f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f
                        },
                        {
                            0.0f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f,       0.5f, 1.0f, 0.0f,
                            0.0f, 0.0f, 0.0f,       0.5f, 1.0f, 0.0f,       1.0f, 0.5f, 0.0f,
                            0.0f, 0.0f, 0.0f,       1.0f, 0.5f, 0.0f,       1.0f, 0.0f, 0.0f
                        },
                        {
                            1.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,
                            1.0f, 0.0f, 0.0f,       0.0f, 0.5f, 0.0f,       0.5f, 1.0f, 0.0f,
                            1.0f, 0.0f, 0.0f,       0.5f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        },
                        {
                            1.0f, 0.0f, 0.0f,       0.0f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f,
                            1.0f, 0.0f, 0.0f,       0.0f, 1.0f, 0.0f,       1.0f, 1.0f, 0.0f
                        }
                    };

                    static constexpr unsigned int lookupSize[16] = {
                        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 2
                    };

                public :    // Static
                    /**
                     * Polygonize a set of cells into a rendering mesh
                     * @param vbo           the vertex buffer to fill
                     * @param cells         the cells data
                     * @param size          the data size
                     * @param startPosition the data start coordinates
                     */
                    static void polygonize(GL::VBO<GL::PrimitiveVertex>& vbo, Utility::Vector<Cell> const& cells, Math::Vector2D<unsigned int> const& size, Math::Point2D<int> const& startPosition);
            };

        }
    }

    #include "NRE_CellPolygonizer.tpp"
