
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
            inline void ChunkPolygonizer::polygonize(Chunk::VoxelsContainer const& target, Math::Point3D<int> const& position, GL::IBO<Layout>& ibo, float threshold, LODLevel level, Utility::UnorderedMap<Math::Point3D<float>, IndexedData>& indexed, Interpolator interpolator) {
                using namespace GL;
                using namespace Math;
                
                Point3D<float> vertices[12];
                Vector4D<float> normals[12];
                Point3D<float> points[8];
                Vector3D<float> gradients[8];
                float values[8];
        
                for (std::size_t y = 0; y < Chunk::SIZE_Y; y += level) {
                    for (std::size_t z = 0; z < Chunk::SIZE_Z; z += level) {
                        for (std::size_t x = 0; x < Chunk::SIZE_X; x += level) {
                            std::uint8_t corners = 0b00000000;
                            for (std::size_t i = 0; i < 8; i++) {
                                values[i] = target.getVoxel(x + vertexOffset[i].getX(), y + vertexOffset[i].getY(), z + vertexOffset[i].getZ()).getIsoValue();
                                Point3D<float> localPts = Point3D<float>(x, y, z) + vertexOffset[i] * level;
                                points[i] = position + localPts;
                                gradients[i] = target.getGradient(localPts);
                                if (values[i] < threshold) {
                                    corners |= static_cast <std::uint8_t> (1 << i);
                                }
                            }
                    
                            if (edgeTable[corners] != 0) {
                                for (std::size_t i = 0; i < 12; i++) {
                                    if (edgeTable[corners] & (1 << i)) {
                                        std::size_t c0 = edgeConnection[i][0];
                                        std::size_t c1 = edgeConnection[i][1];
                                        vertices[i] = interpolator(threshold, points[c0], points[c1], values[c0], values[c1]);
                                        normals[i] = interpolator(threshold, gradients[c0], gradients[c1], values[c0], values[c1]);
                                    }
                                }
                                for (int i = 0; triTable[corners][i] != 0xFF; i++) {
                                    std::size_t triIndex = triTable[corners][winding[i]];
                                    Point3D<float> vertex = vertices[triIndex];
                                    Vector4D<float> normal = normals[triIndex];
                            
                                    auto it = indexed.find(vertex);
                                    if (it != indexed.end()) {
                                        Layout& layout = ibo.getData(it->second.vIndex);
                                        layout.setNormal(normal + layout.getNormal());
                                        it->second.nbAdd++;
                                        ibo.addIndex(it->second.index);
                                    } else {
                                        std::uint32_t newIndex = ibo.getNextIndex();
                                
                                        indexed[vertex] = {ibo.getDataCount(), newIndex, 1};
                                        ibo.addData(vertex, normal);
                                        ibo.addIndex(newIndex);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            inline Math::Point3D<float> ChunkPolygonizer::interpolateLinearVertex(float threshold, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float iso1, float iso2) {
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

            inline Math::Point3D<float> ChunkPolygonizer::interpolateFlatVertex(float, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float, float) {
                return (p1 + p2) * 0.5f;
            }


        }
    }
