
    /**
     * @file NRE_PrimitiveVertex.hpp
     * @brief Declaration of Engine's GL's Object : PrimitiveVertex
     * @author Louis ABEL
     * @date 29/08/2019
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
             * @class PrimitiveVertex
             * @brief A vertex layout : Position - Normal
             */
            class PrimitiveVertex : public Utility::Stringable<PrimitiveVertex> {
                private:    //Fields
                    Math::Vector4D<float> position;    /**< Vertex's position */
                    Math::Vector4D<float> normal;      /**< Vertex's normal */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        PrimitiveVertex() = delete;
                        /**
                         * Construct a 2D primitive vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         */
                        PrimitiveVertex(Math::Point2D<float> const& pos, Math::Vector4D<float> const& n)
                            : position(pos.getX(), pos.getY(), 0, 1), normal(n) {
                        }
                        /**
                         * Construct a 3D primitive vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         */
                        PrimitiveVertex(Math::Point3D<float> const& pos, Math::Vector4D<float> const& n)
                            : position(pos, 1), normal(n) {
                        }

                    //## Getter ##//
                        /**
                         * @return the vertex normal
                         */
                        Math::Vector4D<float> const& getNormal() const {
                            return normal;
                        }

                    //## Setter ##//
                        /**
                         * Set the vertex normal
                         * @param n the new normal
                         */
                        void setNormal(Math::Vector4D<float> const& n) {
                            normal = n;
                        }

                    //## Methods ##//
                        /**
                         * Access the material vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(PrimitiveVertex), 0);
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(PrimitiveVertex), (void*)sizeof(Math::Vector4D<float>));
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the primitive vertex layout into a string
                         * @return the converted primitive vertex layout
                         */
                        Utility::String toString() const {
                            return position.toString() + " - " + normal.toString();
                        }

            };
        }
    }
