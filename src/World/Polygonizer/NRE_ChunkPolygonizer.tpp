
    /**
     * @file NRE_ChunkPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : ChunkPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            void ChunkPolygonizer::polygonize(Chunk const& target, GL::IBO<GL::PrimitiveVertex>& ibo, float threshold, Chunk::LODLevel level, bool linear) {
                Math::Point3D<float> vertices[12];
                std::uint32_t indexes[12];

                std::size_t width = Chunk::VOXELS_LAYER_WIDTH * level;
                std::size_t area  = Chunk::VOXELS_LAYER_AREA  * level;

                std::size_t index = 0;
                std::size_t topLayerIndex;

                std::function<Math::Point3D<float>(float, Math::Point3D<float>, Math::Point3D<float>, float, float)> interpolator;
                if (linear) {
                    interpolator = interpolateLinearVertex;
                } else {
                    interpolator = interpolateFlatVertex;
                }

                for (std::size_t y = 0; y < Chunk::SIZE_Y; y += level) {
                    for (std::size_t z = 0; z < Chunk::SIZE_Z; z += level) {
                        for (std::size_t x = 0; x < Chunk::SIZE_X; x += level) {
                            index = y * Chunk::VOXELS_LAYER_AREA + z * Chunk::VOXELS_LAYER_WIDTH + x;
                            std::uint8_t corners = 0b00000000;
                            topLayerIndex = index + area;
                            float v0 = target[index];
                            float v1 = target[index + width];
                            float v2 = target[index + width + level];
                            float v3 = target[index + level];
                            float v4 = target[topLayerIndex];
                            float v5 = target[topLayerIndex + width];
                            float v6 = target[topLayerIndex + width + level];
                            float v7 = target[topLayerIndex + level];

                            float xF = static_cast <float> (x);
                            float yF = static_cast <float> (y);
                            float zF = static_cast <float> (z);
                            float levelF = static_cast <float> (level);

                            if (v0 < threshold) {
                                corners |= 0b00000001;
                            }
                            if (v1 < threshold) {
                                corners |= 0b00000010;
                            }
                            if (v2 < threshold) {
                                corners |= 0b00000100;
                            }
                            if (v3 < threshold) {
                                corners |= 0b00001000;
                            }
                            if (v4 < threshold) {
                                corners |= 0b00010000;
                            }
                            if (v5 < threshold) {
                                corners |= 0b00100000;
                            }
                            if (v6 < threshold) {
                                corners |= 0b01000000;
                            }
                            if (v7 < threshold) {
                                corners |= 0b10000000;
                            }
                            if (edgeTable[corners] != 0) {
                                std::memset(indexes, -1, 12 * sizeof(std::uint32_t));
                                Math::Point3D<float> p0 = Math::Point3D<float>(xF         , yF         , zF         ) + target.getPosition();
                                Math::Point3D<float> p1 = Math::Point3D<float>(xF         , yF         , zF + levelF) + target.getPosition();
                                Math::Point3D<float> p2 = Math::Point3D<float>(xF + levelF, yF         , zF + levelF) + target.getPosition();
                                Math::Point3D<float> p3 = Math::Point3D<float>(xF + levelF, yF         , zF         ) + target.getPosition();
                                Math::Point3D<float> p4 = Math::Point3D<float>(xF         , yF + levelF, zF         ) + target.getPosition();
                                Math::Point3D<float> p5 = Math::Point3D<float>(xF         , yF + levelF, zF + levelF) + target.getPosition();
                                Math::Point3D<float> p6 = Math::Point3D<float>(xF + levelF, yF + levelF, zF + levelF) + target.getPosition();
                                Math::Point3D<float> p7 = Math::Point3D<float>(xF + levelF, yF + levelF, zF         ) + target.getPosition();

                                if (edgeTable[corners] & 1) {
                                    vertices[0] = interpolator(threshold, p0, p1, v0, v1);
                                }
                                if (edgeTable[corners] & 2) {
                                    vertices[1] = interpolator(threshold, p1, p2, v1, v2);
                                }
                                if (edgeTable[corners] & 4) {
                                    vertices[2] = interpolator(threshold, p2, p3, v2, v3);
                                }
                                if (edgeTable[corners] & 8) {
                                    vertices[3] = interpolator(threshold, p3, p0, v3, v0);
                                }
                                if (edgeTable[corners] & 16) {
                                    vertices[4] = interpolator(threshold, p4, p5, v4, v5);
                                }
                                if (edgeTable[corners] & 32) {
                                    vertices[5] = interpolator(threshold, p5, p6, v5, v6);
                                }
                                if (edgeTable[corners] & 64) {
                                    vertices[6] = interpolator(threshold, p6, p7, v6, v7);
                                }
                                if (edgeTable[corners] & 128) {
                                    vertices[7] = interpolator(threshold, p7, p4, v7, v4);
                                }
                                if (edgeTable[corners] & 256) {
                                    vertices[8] = interpolator(threshold, p0, p4, v0, v4);
                                }
                                if (edgeTable[corners] & 512) {
                                    vertices[9] = interpolator(threshold, p1, p5, v1, v5);
                                }
                                if (edgeTable[corners] & 1024) {
                                    vertices[10] = interpolator(threshold, p2, p6, v2, v6);
                                }
                                if (edgeTable[corners] & 2048) {
                                    vertices[11] = interpolator(threshold, p3, p7, v3, v7);
                                }
                                for (int i = 0; triTable[corners][i] != 0xFF; i += 3) {
                                    for (int c = 0; c < 3; c++) {
                                        std::uint8_t triIndex = triTable[corners][i + windingTable[c]];
                                        if (indexes[triIndex] != static_cast <std::uint32_t> (-1)) {
                                            ibo.addIndex(indexes[triIndex]);
                                        } else {
                                            Math::Vector4D<float> color(vertices[triIndex], 0.0);
                                            color.normalize();
                                            color.setY(vertices[triIndex].getY() / (Chunk::SIZE_Y * 4));

                                            indexes[triIndex] = ibo.getNextIndex();

                                            ibo.addData(vertices[triIndex], color);
                                            ibo.addIndex(indexes[triIndex]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            Math::Point3D<float> ChunkPolygonizer::interpolateLinearVertex(float threshold, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float iso1, float iso2) {
                float mu;
                if (std::abs(threshold - iso1) < Math::F_EPSILON) {
                    return(p1);
                }
                if (std::abs(threshold - iso2) < Math::F_EPSILON) {
                    return(p2);
                }
                if (std::abs(iso1 - iso2) < Math::F_EPSILON) {
                    return(p1);
                }
                mu = (threshold - iso1) / (iso2 - iso1);
                return p1 + (p2 - p1) * mu;
            }

            Math::Point3D<float> ChunkPolygonizer::interpolateFlatVertex(float, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float, float) {
                return (p1 + p2) * 0.5f;
            }


        }
    }
