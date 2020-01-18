
    /**
     * @file NRE_MaterialVertex.hpp
     * @brief Declaration of Engine's GL's Object : MaterialVertex
     * @author Louis ABEL
     * @date 09/01/2020
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
             * @class MaterialVertex
             * @brief A vertex layout : Position + Material - Normal+UVx - Tangent + Uvy
             */
            class MaterialVertex : public Utility::Stringable<MaterialVertex> {
                public:    //Fields
                    Math::Vector4D<float> positionAndMaterial; /**< Packed vertex's position and material's id */
                    Math::Vector4D<float> normalAndU;          /**< Packed vertex's normal and u coord */
                    Math::Vector4D<float> tangentAndV;         /**< Packed vertex's tangent and v coord */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        MaterialVertex() = default;
                        /**
                         * Construct a material vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         * @param m   the vertex's material's id
                         */
                        MaterialVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n, unsigned char m): positionAndMaterial(pos, m), normalAndU(n) {
                        }
                        /**
                         * Construct a material vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         * @param t   the vertex's tangent
                         * @param tex the vertex's uv
                         * @param m   the vertex's material's id
                         */
                        MaterialVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n, Math::Vector3D<float> const& t, Math::Vector2D<float> const& tex, unsigned char m)
                            : positionAndMaterial(pos, m), normalAndU(n, tex.getX()), tangentAndV(t, tex.getY()) {
                        }

                    //## Deconstructor ##//
                        /**
                         * MaterialVertex Deconstructor
                         */
                        ~MaterialVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the material vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(MaterialVertex), 0);
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(MaterialVertex), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(5, 4, GL_FLOAT, sizeof(MaterialVertex), (void*)(2 * sizeof(Math::Vector4D<float>)));
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the material vertex layout into a string
                         * @return the converted material vertex layout
                         */
                        Utility::String toString() const {
                            return positionAndMaterial.toString() + " - " + normalAndU.toString() + " - " + tangentAndV.toString();
                        }

            };
        }
    }
