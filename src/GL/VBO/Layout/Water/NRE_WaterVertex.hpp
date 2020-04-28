
    /**
     * @file NRE_WaterVertex.hpp
     * @brief Declaration of Engine's GL's Object : WaterVertex
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
             * @class WaterVertex
             * @brief A vertex layout : Position - Normal
             */
            class WaterVertex : public Utility::Stringable<WaterVertex> {
                public:    //Fields
                    Math::Vector4D<float> position;     /**< Packed vertex's position */
                    Math::Vector4D<float> normal;       /**< Packed vertex's normal */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        WaterVertex() = default;
                        /**
                         * Construct a water vertex
                         * @param pos the vertex's position
                         * @param n   the vertex's normal
                         */
                        WaterVertex(Math::Point3D<float> const& pos, Math::Vector3D<float> const& n): position(pos), normal(n) {
                        }
    
                    //## Getter ##//
                        /**
                         * @return the vertex's normal
                         */
                        Math::Vector4D<float> const& getNormal() const {
                            return normal;
                        }
        
                    //## Setter ##//
                        /**
                         * Set the vertex's normal
                         * @param n the new normal
                         */
                        void setNormal(Math::Vector4D<float> const& n) {
                            normal = n;
                        }

                    //## Deconstructor ##//
                        /**
                         * WaterVertex Deconstructor
                         */
                        ~WaterVertex() = default;

                    //## Methods ##//
                        /**
                         * Access the water vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(WaterVertex), 0);
                            Layout::enableAttribute(2, 4, GL_FLOAT, sizeof(WaterVertex), (void*)(1 * sizeof(Math::Vector4D<float>)));
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the water vertex layout into a string
                         * @return the converted water vertex layout
                         */
                        Utility::String toString() const {
                            return position.toString() + " - " + normal.toString();
                        }

            };
        }
    }
