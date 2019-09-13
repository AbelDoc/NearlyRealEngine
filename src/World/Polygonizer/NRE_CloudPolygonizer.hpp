
    /**
     * @file NRE_CloudPolygonizer.hpp
     * @brief Declaration of Engine's World's Object : CloudPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../../Header/NRE_GL.hpp"
    #include "../../Header/NRE_Buffer.hpp"

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
             * @class CloudPolygonizer
             * @brief Manage the transformation of points cloud into a rendering mesh
             */
            class CloudPolygonizer {
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
                     * Polygonize a set of voxels into a rendering mesh using marching squares algorithm
                     * @param vbo           the vertex buffer to fill
                     * @param voxels        the voxels data
                     * @param startPosition the data start coordinates
                     * @param size          the data size
                     * @param resolution    the resolution
                     * @param threshold     the isovalue threshold
                     */
                    static void polygonize(GL::VBO<GL::PrimitiveVertex>& vbo, Utility::Vector<float> const& voxels, Math::Point2D<int> const& startPosition, Math::Vector2D<unsigned int> const& size, float resolution, float threshold);
            };

        }
    }

    #include "NRE_CloudPolygonizer.tpp"
