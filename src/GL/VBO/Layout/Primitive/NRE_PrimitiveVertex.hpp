
    /**
     * @file NRE_PrimitiveVertex.hpp
     * @brief Declaration of Engine's GL's Object : PrimitiveVertex
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../NRE_Layout.hpp"

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
             * @brief A vertex layout : Position - Color
             */
            class PrimitiveVertex {
                private:    //Fields
                    Math::Vector4D<float> position;    /**< Vertex's position */
                    Math::Vector4D<float> color;       /**< Vertex's color */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        PrimitiveVertex() = delete;
                        /**
                         * Construct a 2D primitive vertex
                         * @param pos the vertex's position
                         * @param c   the vertex's color
                         */
                        PrimitiveVertex(Math::Point2D<float> const& pos, Math::Vector4D<float> const& c)
                            : position(pos.getX(), pos.getY(), 0, 1), color(c) {
                        }
                        /**
                         * Construct a 3D primitive vertex
                         * @param pos the vertex's position
                         * @param c   the vertex's color
                         */
                        PrimitiveVertex(Math::Point3D<float> const& pos, Math::Vector4D<float> const& c)
                            : position(pos.getX(), pos.getY(), pos.getZ(), 1), color(c) {
                        }

                    //## Copy-Constructor ##//
                        /**
                         * Copy l into this
                         * @param l the primitive vertex layout to copy the content
                         */
                        PrimitiveVertex(PrimitiveVertex const& l) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move l into this
                         * @param l the primitive vertex layout to move
                         */
                        PrimitiveVertex(PrimitiveVertex && l) = default;

                    //## Deconstructor ##//
                        /**
                         * PrimitiveVertex Deconstructor
                         */
                        ~PrimitiveVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the material vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(PrimitiveVertex), 0);
                            Layout::enableAttribute(1, 4, GL_FLOAT, sizeof(PrimitiveVertex), (void*)sizeof(Math::Vector4D<float>));
                        }

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of l into this
                         * @param l the primitive vertex layout to copy into this
                         * @return      the reference of himself
                         */
                        PrimitiveVertex& operator =(PrimitiveVertex const& l) = default;
                        /**
                         * Move assignment of l into this
                         * @param l the primitive vertex layout to move into this
                         * @return      the reference of himself
                         */
                        PrimitiveVertex& operator =(PrimitiveVertex && l) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the primitive vertex layout into a string
                         * @return the converted primitive vertex layout
                         */
                        Utility::String toString() const {
                            return position.toString() + " - " + color.toString();
                        }

            };
        }
    }
