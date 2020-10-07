
    /**
     * @file NRE_ChunkPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : ChunkPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {
    
            template <class Layout>
            inline void ChunkPolygonizer::polygonize(Chunk const& target, GL::IBO<Layout>& ibo, float threshold, LODLevel level, Core::UnorderedMap<Math::Point3D<float>, IndexedData>& indexed, VectorInterpolator vecInterpolator, FloatInterpolator fInterpolator) {
                using namespace GL;
                using namespace Math;
                
                Point3D<float> interpolatedVertices[12];
                Vector4D<float> interpolatedNormals[12];
                Vector3D<float> interpolatedColors[12];
                float interpolatedRoughness[12];
                float interpolatedMetallics[12];
                
                Point3D<float> vertices[8];
                Vector3D<float> normals[8];
                Vector3D<float> colors[8];
                float roughness[8];
                float metallics[8];
                float values[8];
        
                for (std::size_t y = 0; y < Chunk::SIZE_Y; y += level) {
                    for (std::size_t z = 0; z < Chunk::SIZE_Z; z += level) {
                        for (std::size_t x = 0; x < Chunk::SIZE_X; x += level) {
                            std::uint8_t corners = 0b00000000;
                            for (std::size_t i = 0; i < 8; i++) {
                                Voxel const& v = target.getVoxel(x + vertexOffset[i].getX(), y + vertexOffset[i].getY(), z + vertexOffset[i].getZ());
                                values[i] = v.getIsoValue();
                                colors[i] = VoxelTypes::VOXEL_COLORS[v.getType()];
                                roughness[i] = VoxelTypes::VOXEL_ROUGHNESS[v.getType()];
                                metallics[i] = VoxelTypes::VOXEL_METALLICS[v.getType()];
                                
                                Point3D<float> localPts = Point3D<float>(x, y, z) + vertexOffset[i] * level;
                                vertices[i] = target.getPosition() + localPts;
                                normals[i] = target.getGradient(localPts);
                                if (values[i] < threshold) {
                                    corners |= static_cast <std::uint8_t> (1 << i);
                                }
                            }
                    
                            if (edgeTable[corners] != 0) {
                                for (std::size_t i = 0; i < 12; i++) {
                                    if (edgeTable[corners] & (1 << i)) {
                                        std::size_t c0 = edgeConnection[i][0];
                                        std::size_t c1 = edgeConnection[i][1];
                                        interpolatedVertices[i] = vecInterpolator(threshold, vertices[c0], vertices[c1], values[c0], values[c1]);
                                        interpolatedNormals[i] = vecInterpolator(threshold, normals[c0], normals[c1], values[c0], values[c1]);
                                        interpolatedColors[i] = vecInterpolator(threshold, colors[c0], colors[c1], values[c0], values[c1]);
                                        interpolatedRoughness[i] = fInterpolator(threshold, roughness[c0], roughness[c1], values[c0], values[c1]);
                                        interpolatedMetallics[i] = fInterpolator(threshold, metallics[c0], metallics[c1], values[c0], values[c1]);
                                    }
                                }
                                for (int i = 0; triTable[corners][i] != 0xFF; i++) {
                                    std::size_t triIndex = triTable[corners][winding[i]];
                                    Point3D<float> vertex = interpolatedVertices[triIndex];
                                    Vector4D<float> normal = interpolatedNormals[triIndex];
                                    Vector3D<float> color = interpolatedColors[triIndex];
                                    float r = interpolatedRoughness[triIndex];
                                    float m = interpolatedMetallics[triIndex];
                            
                                    auto it = indexed.find(vertex);
                                    if (it != indexed.end()) {
                                        Layout& layout = ibo.getData(it->second.vIndex);
                                        layout.accumulate(normal, color, r, m);
                                        it->second.nbAdd++;
                                        ibo.addIndex(it->second.index);
                                    } else {
                                        std::uint32_t newIndex = ibo.getNextIndex();
                                
                                        indexed[vertex] = {ibo.getDataCount(), newIndex, 1};
                                        ibo.addData(vertex, normal, color, r, m);
                                        ibo.addIndex(newIndex);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            template <class T>
            inline T ChunkPolygonizer::linearInterpolator(float threshold, T const& p1, T const& p2, float iso1, float iso2) {
                if (Math::almostEqual(threshold, iso1)) {
                    return(p1);
                }
                if (Math::almostEqual(threshold, iso2)) {
                    return(p2);
                }
                if (Math::almostEqual(iso1, iso2)) {
                    return(p1);
                }
                float mu = (threshold - iso1) / (iso2 - iso1);
                return p1 + (p2 - p1) * mu;
            }
    
            template <class T>
            inline T ChunkPolygonizer::flatInterpolator(float, T const& p1, T const& p2, float, float) {
                return (p1 + p2) * 0.5f;
            }


        }
    }
