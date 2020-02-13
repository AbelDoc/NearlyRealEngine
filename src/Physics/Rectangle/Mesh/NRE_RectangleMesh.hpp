    
    /**
     * @file NRE_RectangleMesh.hpp
     * @brief Declaration of Engine's Model's Mesh specialization : RectangleMesh
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include "Rectangle/NRE_Rectangle.hpp"
    #include "../../../Header/NRE_Model.hpp"
    #include "../../../Header/NRE_Buffer.hpp"
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Model
         * @brief Engine's Model module
         */
        namespace Model {
            /**
             * @class MeshFactory
             * @brief Manage the creation of mesh's buffer
             */
            template <>
            class MeshFactory<Physics::Rectangle> {
                public :    // Static
                    /**
                     * Create a buffer from a given object
                     * @param o the object to create the buffer
                     * @return  the created buffer
                     */
                    static GL::AbstractVBO* create(Physics::Rectangle const& o) {
                        using namespace NRE::Math;
                        
                        GL::VBO<GL::PointVertex>* buffer = new GL::VBO<GL::PointVertex>(GL_STATIC_DRAW);
                        buffer->addData(Vector2D<float>(o.getCoord().getX(),                      o.getCoord().getY()),                      Vector2D<float>(0, 0));
                        buffer->addData(Vector2D<float>(o.getCoord().getX() + o.getSize().getW(), o.getCoord().getY()),                      Vector2D<float>(1, 0));
                        buffer->addData(Vector2D<float>(o.getCoord().getX() + o.getSize().getW(), o.getCoord().getY() + o.getSize().getH()), Vector2D<float>(1, 1));
                        buffer->addData(Vector2D<float>(o.getCoord().getX() + o.getSize().getW(), o.getCoord().getY() + o.getSize().getH()), Vector2D<float>(1, 1));
                        buffer->addData(Vector2D<float>(o.getCoord().getX(),                      o.getCoord().getY() + o.getSize().getH()), Vector2D<float>(0, 1));
                        buffer->addData(Vector2D<float>(o.getCoord().getX(),                      o.getCoord().getY()),                      Vector2D<float>(0, 0));
                        
                        return buffer;
                    }
            };
            
            typedef TypedMesh<Physics::Rectangle> RectangleMesh;
        }
    }