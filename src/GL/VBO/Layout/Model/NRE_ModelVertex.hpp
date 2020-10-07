
    /**
     * @file NRE_ModelVertex.hpp
     * @brief Declaration of Engine's GL's Object : ModelVertex
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
             * @class ModelVertex
             * @brief A vertex layout : Position - Normal - Tangent - UV - Material
             */
            class ModelVertex : public Core::Stringable<ModelVertex> {
                public:    //Fields
                    Math::Vector4D<float> position;         /**< Packed vertex's position */
                    Math::Vector4D<float> normalAndMat;     /**< Packed vertex's normal */

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
                         * @param m   the vertex's material id
                         */
                        ModelVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n, int m) : position(pos), normalAndMat(n, m) {
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
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the model vertex layout into a string
                         * @return the converted model vertex layout
                         */
                        Core::String toString() const {
                            return position.toString() + " - " + normalAndMat.toString();
                        }

            };
        }
    }
