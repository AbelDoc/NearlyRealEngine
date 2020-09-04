    
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
    
            typedef CullableMesh<World::Chunk, Math::Frustum, void*> ChunkMesh;
            
            /**
             * @class ModelFactory
             * @brief Manage the creation of models's mesh
             */
            template <>
            class ModelFactory<World::Chunk> {
                public :    // Static
                    /**
                     * Create a buffer from a given object
                     * @param o the object to create the buffer
                     * @return  the created buffer
                     */
                    static Utility::Vector<std::unique_ptr<Mesh>> create(World::Chunk const& o) {
                        using namespace GL;
                        using namespace Math;
                        using namespace World;
                        using namespace Utility;
                        
                        Vector<std::unique_ptr<Mesh>> meshes;
                        IBO<VoxelVertex>* voxelBuffer = new IBO<VoxelVertex>(GL_STATIC_DRAW);
    
                        UnorderedMap<Point3D<float>, ChunkPolygonizer::IndexedData> voxelIndexed;
                        voxelIndexed.reserve(3000);   // Average index per chunk
                        
                        ChunkPolygonizer::polygonize(o, *voxelBuffer, 0.6f, ChunkPolygonizer::LEVELS[0], voxelIndexed);
    
                        for (auto& it : voxelIndexed) {
                            VoxelVertex& layout = voxelBuffer->getData(it.second.vIndex);
                            layout.mean(it.second.nbAdd);
                        }
                        
                        auto* voxels = new ChunkMesh(voxelBuffer);
    
                        voxels->setTarget(&o);
                        
                        meshes.emplaceBack(voxels);
                        return meshes;
                    }
            };
        
            template <>
            inline bool ChunkMesh::inBound() const {
                for (int i = 0; i < Math::FACE_NUM; i++) {
                    Math::Vector3D<float> p = getTarget()->getPosition();
                    Math::Vector3D<float> const& normal = boundObject->getPlane(i).getNormal();
                    if (normal.getX() >= 0) {
                        p.setX(p.getX() + World::Chunk::SIZE_X);
                    }
                    if (normal.getY() >= 0) {
                        p.setY(p.getY() + World::Chunk::SIZE_Y);
                    }
                    if (normal.getZ() >= 0) {
                        p.setZ(p.getZ() + World::Chunk::SIZE_Z);
                    }
                    if (boundObject->getPlane(i).distance(p) < 0) {
                        return false;
                    }
                }
                return true;
            }
            
            typedef TypedModel<World::Chunk> ChunkModel;
        }
    }