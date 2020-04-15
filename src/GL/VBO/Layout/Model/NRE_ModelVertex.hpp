
    /**
     * @file NRE_ModelVertex.hpp
     * @brief Declaration of Engine's GL's Object : ModelVertex
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
             * @class ModelVertex
             * @brief A vertex layout : Position - Normal - Tangent - UV - Material
             */
            class ModelVertex : public Utility::Stringable<ModelVertex> {
                public:    //Fields
                    Math::Vector4D<float> positionAndU;     /**< Packed vertex's position and u coord */
                    Math::Vector4D<float> normalAndV;       /**< Packed vertex's normal and v coord */
                    Math::Vector4D<float> tangentAndMat;    /**< Packed vertex's tangent and model */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ModelVertex() = default;
                        /**
                         * Construct a model vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         * @param t   the vertex's tangent
                         * @param uv  the vertex's uv
                         * @param m   the vertex's material id
                         */
                        ModelVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n, Math::Vector3D<float> const& t, Math::Vector2D<float> const& uv, int m) : positionAndU(pos, uv.getX()), normalAndV(n, uv.getY()), tangentAndMat(t, m) {
                        }

                    //## Deconstructor ##//
                        /**
                         * ModelVertex Deconstructor
                         */
                        ~ModelVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the model vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(ModelVertex), 0);
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(ModelVertex), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(5, 4, GL_FLOAT, sizeof(ModelVertex), (void*)(2 * sizeof(Math::Vector4D<float>)));
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the model vertex layout into a string
                         * @return the converted model vertex layout
                         */
                        Utility::String toString() const {
                            return positionAndU.toString() + " - " + normalAndV.toString() + " - " + tangentAndMat.toString();
                        }

            };
        }
    }
