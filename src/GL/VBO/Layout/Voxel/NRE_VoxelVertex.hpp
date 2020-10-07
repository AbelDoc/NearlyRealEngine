
    /**
     * @file NRE_VoxelVertex.hpp
     * @brief Declaration of Engine's GL's Object : VoxelVertex
     * @author Louis ABEL
     * @date 15/04/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../NRE_Layout.hpp"

     #include <Core/Interfaces/Stringable/NRE_Stringable.hpp>

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
             * @class VoxelVertex
             * @brief A vertex layout : Position - Normal - Color - Roughness - Metallic
             */
            class VoxelVertex : public Core::Stringable<VoxelVertex> {
                public:    //Fields
                    Math::Vector4D<float> position;  /**< Packed vertex's position */
                    Math::Vector4D<float> color;     /**< Packed vertex's color and roughness */
                    Math::Vector4D<float> normal;    /**< Packed vertex's normal and metallic */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VoxelVertex() = default;
                        /**
                         * Construct a terrain vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         * @param c   the vertex's color
                         * @param r   the vertex's roughness
                         * @param m   the vertex's metallic
                         */
                        VoxelVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n, Math::Vector3D<float> const& c, float r, float m) : position(pos), color(c, r), normal(n, m) {
                        }

                    //## Deconstructor ##//
                        /**
                         * VoxelVertex Deconstructor
                         */
                        ~VoxelVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the terrain vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(VoxelVertex), 0);
                            Layout::enableAttribute(1, 4, GL_FLOAT, sizeof(VoxelVertex), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(VoxelVertex), (void*)(2 * sizeof(Math::Vector4D<float>)));
                        }
                        void accumulate(Math::Vector3D<float> const& n, Math::Vector3D<float> const& c, float r, float m) {
                            color += Math::Vector4D<float>(c, r);
                            normal += Math::Vector4D<float>(n, m);
                        }
                        void mean(float nb) {
                            color /= nb;
                            normal /= nb;
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the terrain vertex layout into a string
                         * @return the converted terrain vertex layout
                         */
                        Core::String toString() const {
                            return position.toString() + " - " + color.toString() + " - " + normal.toString();
                        }

            };
        }
    }
