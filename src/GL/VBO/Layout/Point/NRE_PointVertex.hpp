    
    /**
     * @file NRE_PointVertex.hpp
     * @brief Declaration of Engine's GL's Object : PointVertex
     * @author Louis ABEL
     * @date 20/12/2019
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
             * @class PointVertex
             * @brief A vertex layout : Position - Color
             */
            class PointVertex : public Core::Stringable<PointVertex> {
            public:    //Fields
                Math::Vector4D<float> position;    /**< Vertex's position */
            
            public:    // Methods
                //## Constructor ##//
                    /**
                     * Default constructor
                     */
                    PointVertex() = default;
                    /**
                     * Construct the vertex from it's 3D position
                     * @param p the vertex position
                     */
                    PointVertex(Math::Vector3D<float> const& p) : position(p, 1.0) {
                    }
                    /**
                     * Construct the vertex from 2 positions
                     * @param p  the vertex position
                     * @param uv the vertex uv coordinates
                     */
                    PointVertex(Math::Vector2D<float> const& p, Math::Vector2D<float> const& uv) : position(p.getX(), p.getY(), uv.getX(), uv.getY()) {
                    }
                
                //## Methods ##//
                /**
                 * Access the material vertex for VAO's command's storing
                 */
                static void access() {
                    Layout::enableAttribute(0, 4, GL_FLOAT, sizeof(PointVertex), 0);
                }
                
                //## Stream Operator ##//
                /**
                 * Convert the primitive vertex layout into a string
                 * @return the converted primitive vertex layout
                 */
                Core::String toString() const {
                    return position.toString();
                }
                
            };
        }
    }
