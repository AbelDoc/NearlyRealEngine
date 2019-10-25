
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
            
            typedef CullableMesh<World::Chunk, Math::Frustum, Utility::Array<Math::Point3D<int>, 8>> ChunkMesh;
    
            template <>
            inline bool ChunkMesh::inBound(Math::Frustum const& bound) const {
                int in, out;
                
                for (int i = 0; i < Math::FACE_NUM; i++) {
                    in = 0;
                    out = 0;
                    for (int j = 0; j < 8; j = j + 1) {
                        if (bound.getPlane(i).distance(cacheData[j]) <= 0) {
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
                cacheData[0] = target.getPosition();
                cacheData[1] = target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X, 0, 0);
                cacheData[2] = target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X, 0, World::Chunk::SIZE_Z);
                cacheData[3] = target.getPosition() + Math::Vector3D<int>(0, 0, World::Chunk::SIZE_Z);
                cacheData[4] = target.getPosition() + Math::Vector3D<int>(0, World::Chunk::SIZE_Y, 0);
                cacheData[5] = target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X, World::Chunk::SIZE_Y, 0);
                cacheData[6] = target.getPosition() + Math::Vector3D<int>(World::Chunk::SIZE_X, World::Chunk::SIZE_Y, World::Chunk::SIZE_Z);
                cacheData[7] = target.getPosition() + Math::Vector3D<int>(0, World::Chunk::SIZE_Y, World::Chunk::SIZE_Z);
            }
        }
    }

    #include "NRE_ChunkFactory.tpp"
