
    /**
     * @file NRE_TerrainVertex.hpp
     * @brief Declaration of Engine's GL's Object : TerrainVertex
     * @author Louis ABEL
     * @date 15/04/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../NRE_Layout.hpp"

     #include <Utility/Interfaces/Stringable/NRE_Stringable.hpp>

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
             * @class TerrainVertex
             * @brief A vertex layout : Position - Normal - Tangent - Materials
             */
            class TerrainVertex : public Utility::Stringable<TerrainVertex> {
                public:    //Fields
                    Math::Vector4D<float> positionAndMatX;  /**< Packed vertex's position and terrain x */
                    Math::Vector4D<float> normalAndMatY;    /**< Packed vertex's normal and terrain y */
                    Math::Vector4D<float> tangentAndMatZ;   /**< Packed vertex's tangent and terrain z */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        TerrainVertex() = default;
                        /**
                         * Construct a terrain vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         */
                        TerrainVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n) : positionAndMatX(pos), normalAndMatY(n) {
                        }

                    //## Deconstructor ##//
                        /**
                         * TerrainVertex Deconstructor
                         */
                        ~TerrainVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the terrain vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(TerrainVertex), 0);
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(TerrainVertex), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(5, 4, GL_FLOAT, sizeof(TerrainVertex), (void*)(2 * sizeof(Math::Vector4D<float>)));
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the terrain vertex layout into a string
                         * @return the converted terrain vertex layout
                         */
                        Utility::String toString() const {
                            return positionAndMatX.toString() + " - " + normalAndMatY.toString() + " - " + tangentAndMatZ.toString();
                        }

            };
        }
    }
