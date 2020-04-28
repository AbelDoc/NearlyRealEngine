    
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
                        IBO<TerrainVertex>* terrainBuffer = new IBO<TerrainVertex>(GL_STATIC_DRAW);
                        IBO<WaterVertex>*   waterBuffer   = new IBO<WaterVertex>(GL_STATIC_DRAW);
    
                        UnorderedMap<Point3D<float>, ChunkPolygonizer::IndexedData> terrainIndexed;
                        UnorderedMap<Point3D<float>, ChunkPolygonizer::IndexedData> waterIndexed;
                        terrainIndexed.reserve(3000);   // Average index per chunk
                        waterIndexed.reserve(3000);
                        
                        ChunkPolygonizer::polygonize(o.getTerrainVoxels(), o.getPosition(), *terrainBuffer, 0, ChunkPolygonizer::LEVELS[0], terrainIndexed);
                        ChunkPolygonizer::polygonize(o.getWaterVoxels(),   o.getPosition(), *waterBuffer,   0, ChunkPolygonizer::LEVELS[0], waterIndexed);
    
                        for (auto& it : terrainIndexed) {
                            TerrainVertex& layout = terrainBuffer->getData(it.second.vIndex);
                            layout.normalAndMatY /= it.second.nbAdd;
                            layout.normalAndMatY.normalize();
        
                            auto n = Vector3D<float>(layout.normalAndMatY);
                            auto t = Vector3D<float>(0, 1, 0) ^ n;
        
                            layout.positionAndMatX.setW(2);
                            layout.normalAndMatY.setW(1);
                            layout.tangentAndMatZ = Vector4D<float>(t, 2);
                        }
    
                        for (auto& it : waterIndexed) {
                            WaterVertex& layout = waterBuffer->getData(it.second.vIndex);
                            layout.normal /= it.second.nbAdd;
                            layout.normal.normalize();
                            layout.position.setY(5);
                        }
                        
                        meshes.emplaceBack(new Mesh(terrainBuffer));
                        meshes.emplaceBack(new Mesh(waterBuffer));
                        return meshes;
                    }
            };
    
            typedef CullableModel<World::Chunk, Math::Frustum, void*> ChunkModel;
        
            template <>
            inline bool ChunkModel::inBound() const {
                for (int i = 0; i < Math::FACE_NUM; i++) {
                    Math::Vector3D<float> p = target.getPosition();
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
        }
    }