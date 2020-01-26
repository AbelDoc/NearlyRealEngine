    
    /**
     * @file NRE_ChunkMesh.hpp
     * @brief Declaration of Engine's Model's Mesh specialization : ChunkMesh
     * @author Louis ABEL
     * @date 26/10/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once
    
    #include "../NRE_World.hpp"
    #include "../../Header/NRE_Model.hpp"

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
            class MeshFactory<World::Chunk> {
            public :    // Static
                /**
                 * Create a buffer from a given object
                 * @param o the object to create the buffer
                 * @return  the created buffer
                 */
                static GL::AbstractVBO* create(World::Chunk const& o) {
                    GL::IBO<GL::MaterialVertex>* buffer = new GL::IBO<GL::MaterialVertex>(GL_STATIC_DRAW);
                    World::ChunkPolygonizer::polygonize(o, *buffer, 0, World::ChunkPolygonizer::LEVELS[0]);
                    return buffer;
                }
            };
        
            typedef CullableMesh<World::Chunk, Math::Frustum, void*> ChunkMesh;
        
            template <>
            inline bool ChunkMesh::inBound() const {
                for (int i = 0; i < Math::FACE_NUM; i++) {
                    Math::Vector3D<float> p = target.getPosition();
                    Math::Vector3D<float> const& normal = boundObject.getPlane(i).getNormal();
                    if (normal.getX() >= 0) {
                        p.setX(p.getX() + World::Chunk::SIZE_X);
                    }
                    if (normal.getY() >= 0) {
                        p.setY(p.getY() + World::Chunk::SIZE_Y);
                    }
                    if (normal.getZ() >= 0) {
                        p.setZ(p.getZ() + World::Chunk::SIZE_Z);
                    }
                    if (boundObject.getPlane(i).distance(p) < 0) {
                        return false;
                    }
                }
                return true;
            }
        
            template <>
            inline void ChunkMesh::update(Utility::Observable*, void*) {
            }
        }
    }