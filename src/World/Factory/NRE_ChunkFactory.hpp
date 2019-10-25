
    /**
     * @file NRE_ChunkFactory.hpp
     * @brief Declaration of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../NRE_World.hpp"
    #include "../../Header/NRE_Model.hpp"

    #include "../Polygonizer/NRE_ChunkPolygonizer.hpp"

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    #pragma GCC diagnostic ignored "-Wconversion"
    #pragma GCC diagnostic ignored "-Wfloat-conversion"
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    #pragma GCC diagnostic ignored "-Wstrict-aliasing"

    #include "../../lib/FastNoise/FastNoise.h"

    #pragma GCC diagnostic pop


    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World module
         */
        namespace World {

            /**
             * @class ChunkFactory
             * @brief Manage the creation of chunk
             */
            class ChunkFactory {
                public :    // Static
                    /**
                     * Create a cloud of voxels (which isovalue represent the distance from the center) and then store the resulting cells into a given chunk
                     * @param target     the target chunk
                     * @param resolution the generation resolution
                     * @param radius     the sphere radius
                     */
                    static void createSphere(Chunk& target);
                    /**
                     * Create a cloud of voxels (which isovalue represent the terrain height) and then store the resulting cells into a given chunk
                     * @param target     the target chunk
                     * @param resolution the generation resolution
                     */
                    static void createTerrain(Chunk& target);
            };

        }
        
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
                        GL::IBO<GL::PrimitiveVertex>* buffer = new GL::IBO<GL::PrimitiveVertex>(GL_STATIC_DRAW);
                        World::ChunkPolygonizer::polygonize(o, *buffer, 0, World::ChunkPolygonizer::LEVELS[0]);
                        return buffer;
                    }
            };
            
            typedef CullableMesh<World::Chunk, Math::Frustum, Utility::Array<Math::Plane<int>, 6>> ChunkMesh;
    
            template <>
            inline bool ChunkMesh::inBound(Math::Frustum const& bound) const {
                int in, out;
                
                for (int i = 0; i < Math::FACE_NUM; i++) {
                    in = 0;
                    out = 0;
                    for (int j = 0; j < Math::FACE_NUM; j = j + 1) {
                        if (bound.getPlane(i).distance(cacheData[j].getPoint()) <= 0) {
                            out++;
                        } else {
                            in++;
                        }
                    }
                    if (!in) {
                        return false;
                    } else if (out) {
                        return true;
                    }
                }
                return true;
            }
            
            template <>
            inline void ChunkMesh::update(Utility::Observable*, void*) {
                cacheData[Math::TOP].setPoint(target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X / 2, World::Chunk::SIZE_Y, World::Chunk::SIZE_Z / 2));
                cacheData[Math::TOP].setNormal(Math::Vector3D<int>(0, 1, 0));
                
                cacheData[Math::BOTTOM].setPoint(target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X / 2, 0, World::Chunk::SIZE_Z / 2));
                cacheData[Math::BOTTOM].setNormal(Math::Vector3D<int>(0, -1, 0));

                cacheData[Math::LEFT].setPoint(target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X, World::Chunk::SIZE_Y / 2, World::Chunk::SIZE_Z / 2));
                cacheData[Math::LEFT].setNormal(Math::Vector3D<int>(1, 0, 0));

                cacheData[Math::RIGHT].setPoint(target.getPosition() + Math::Vector3D<int>(0, World::Chunk::SIZE_Y / 2, World::Chunk::SIZE_Z / 2));
                cacheData[Math::RIGHT].setNormal(Math::Vector3D<int>(-1, 0, 0));
                
                cacheData[5].setPoint(target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X / 2, World::Chunk::SIZE_Y / 2, 0));
                cacheData[5].setNormal(Math::Vector3D<int>(0, 0, 1));

                cacheData[6].setPoint(target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X / 2, World::Chunk::SIZE_Y / 2, World::Chunk::SIZE_Z));
                cacheData[6].setNormal(Math::Vector3D<int>(0, 0, -1));
            }
        }
    }

    #include "NRE_ChunkFactory.tpp"
