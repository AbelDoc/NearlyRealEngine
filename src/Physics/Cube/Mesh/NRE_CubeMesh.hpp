    
    /**
     * @file NRE_CubeMesh.hpp
     * @brief Declaration of Engine's Model's Mesh specialization : CubeMesh
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include "Cube/NRE_Cube.hpp"
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
            class MeshFactory<Physics::Cube> {
                public :    // Static
                    /**
                     * Create a buffer from a given object
                     * @param o the object to create the buffer
                     * @return  the created buffer
                     */
                    static GL::AbstractVBO* create(Physics::Cube const& o) {
                        using namespace NRE::Math;
        
                        GL::IBO<GL::PointVertex, uint8_t>* buffer = new GL::IBO<GL::PointVertex, uint8_t>(GL_STATIC_DRAW);
                        buffer->addData(o.getCenter() + Vector3D<float>(-1, -1, -1));
                        buffer->addData(o.getCenter() + Vector3D<float>(-1, -1,  1));
                        buffer->addData(o.getCenter() + Vector3D<float>(-1,  1, -1));
                        buffer->addData(o.getCenter() + Vector3D<float>(-1,  1,  1));
                        buffer->addData(o.getCenter() + Vector3D<float>( 1,  1,  1));
                        buffer->addData(o.getCenter() + Vector3D<float>( 1,  1, -1));
                        buffer->addData(o.getCenter() + Vector3D<float>( 1, -1,  1));
                        buffer->addData(o.getCenter() + Vector3D<float>( 1, -1, -1));
        
                        uint8_t index[] = {
                            2, 0, 7, 7, 5, 2,
                            1, 0, 2, 2, 3, 1,
                            7, 6, 4, 4, 5, 7,
                            1, 3, 4, 4, 6, 1,
                            2, 5, 4, 4, 3, 2,
                            0, 1, 7, 7, 1, 6,
                        };
        
                        buffer->addIndex(index, 36);
                        
                        return buffer;
                    }
            };
            
            typedef TypedMesh<Physics::Cube> CubeMesh;
        }
    }