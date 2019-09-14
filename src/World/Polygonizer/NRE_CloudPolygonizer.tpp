
    /**
     * @file NRE_CloudPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : CloudPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            void CloudPolygonizer::polygonize(GL::VBO<GL::PrimitiveVertex>& ibo, Math::Point3D<int> const& startPosition, Math::Vector3D<unsigned int> const& size, float resolution, float threshold) {
                Math::Point3D<float> currentPosition(static_cast <float> (startPosition.getX()), static_cast <float> (startPosition.getY()), static_cast <float> (startPosition.getZ()));

                std::size_t lineWidth = static_cast <unsigned int> (static_cast <float> (size.getX()) / resolution) + 1;
                std::size_t lineDepth = static_cast <unsigned int> (static_cast <float> (size.getZ()) / resolution) + 1;
                std::size_t layerSize = lineWidth * lineDepth;
                std::size_t cacheSize = layerSize * 2;

                Utility::Vector<float> voxels(cacheSize);

                std::size_t index = 0;

                for (float y = 0; y < 2; y++) {     // Generate two layer to fill the cache
                    for (float z = 0; z <= static_cast <float> (size.getZ()); z += resolution) {
                        for (float x = 0; x <= static_cast <float> (size.getX()); x += resolution) {
                            voxels[index++] = Math::Vector3D<float>(x - static_cast <float> (size.getX() / 2), (y * resolution) - static_cast <float> (size.getY() / 2), z - static_cast <float> (size.getZ() / 2)).normSquared();
                        }
                    }
                }

                std::cout << voxels << std::endl;

                Math::Point3D<float> vertices[12];

                bool evenCacheLine = true;
                std::size_t tmp;
                for (float y = 2 * resolution; y <= static_cast <float> (size.getY()); y += resolution) {
                    index = (evenCacheLine) ? (0) : (layerSize);
                    for (float z = 0; z <= static_cast <float> (size.getZ()) - resolution; z += resolution) {
                        for (float x = 0; x <= static_cast <float> (size.getX()) - resolution; x += resolution) {
                            std::uint8_t corners = 0b00000000;
                            tmp = (evenCacheLine) ? (index + layerSize) : (index - layerSize);
                            std::cout << index << " " << tmp << std::endl;
                            if (voxels[index] < threshold) {
                                corners |= 0b00000001;
                            }
                            if (voxels[index + lineWidth] < threshold) {
                                corners |= 0b00000010;
                            }
                            if (voxels[index + lineWidth + 1] < threshold) {
                                corners |= 0b00000100;
                            }
                            if (voxels[index + 1] < threshold) {
                                corners |= 0b00001000;
                            }
                            if (voxels[tmp] < threshold) {
                                corners |= 0b00010000;
                            }
                            if (voxels[tmp + lineWidth] < threshold) {
                                corners |= 0b00100000;
                            }
                            if (voxels[tmp + lineWidth + 1] < threshold) {
                                corners |= 0b01000000;
                            }
                            if (voxels[tmp + 1] < threshold) {
                                corners |= 0b10000000;
                            }

                            Utility::String res;
                            res << ((corners & 0b10000000) ? ('1') : ('0'));
                            res << ((corners & 0b01000000) ? ('1') : ('0'));
                            res << ((corners & 0b00100000) ? ('1') : ('0'));
                            res << ((corners & 0b00010000) ? ('1') : ('0'));
                            res << ((corners & 0b00001000) ? ('1') : ('0'));
                            res << ((corners & 0b00000100) ? ('1') : ('0'));
                            res << ((corners & 0b00000010) ? ('1') : ('0'));
                            res << ((corners & 0b00000001) ? ('1') : ('0'));

                            std::cout << res << std::endl;

                            voxels[index++] = Math::Vector3D<float>(x - static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2), z - static_cast <float> (size.getZ() / 2)).normSquared();
                            if (edgeTable[corners] == 0) {
                                continue;
                            }

                            if (edgeTable[corners] & 1) {
                                vertices[0] = Math::Vector3D<float>(0.0f, 0.0f, 0.5f) + currentPosition;
                            }
                            if (edgeTable[corners] & 2) {
                                vertices[1] = Math::Vector3D<float>(0.5f, 0.0f, 1.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 4) {
                                vertices[2] = Math::Vector3D<float>(1.0f, 0.0f, 0.5f) + currentPosition;
                            }
                            if (edgeTable[corners] & 8) {
                                vertices[3] = Math::Vector3D<float>(0.5f, 0.0f, 0.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 16) {
                                vertices[4] = Math::Vector3D<float>(0.0f, 1.0f, 0.5f) + currentPosition;
                            }
                            if (edgeTable[corners] & 32) {
                                vertices[5] = Math::Vector3D<float>(0.5f, 1.0f, 1.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 64) {
                                vertices[6] = Math::Vector3D<float>(1.0f, 1.0f, 0.5f) + currentPosition;
                            }
                            if (edgeTable[corners] & 128) {
                                vertices[7] = Math::Vector3D<float>(0.5f, 1.0f, 0.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 256) {
                                vertices[8] = Math::Vector3D<float>(0.0f, 0.5f, 0.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 512) {
                                vertices[9] = Math::Vector3D<float>(0.0f, 0.5f, 1.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 1024) {
                                vertices[10] = Math::Vector3D<float>(1.0f, 0.5f, 1.0f) + currentPosition;
                            }
                            if (edgeTable[corners] & 2048) {
                                vertices[11] = Math::Vector3D<float>(1.0f, 0.5f, 0.0f) + currentPosition;
                            }

                            for (int i = 0; triTable[corners][i] != 0xFF; i += 3) {
                                ibo.addData(vertices[triTable[corners][i    ]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                                ibo.addData(vertices[triTable[corners][i + 1]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                                ibo.addData(vertices[triTable[corners][i + 2]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            }
                            currentPosition.setX(currentPosition.getX() + resolution);
                        }
                        currentPosition.setZ(currentPosition.getZ() + resolution);
                        currentPosition.setX(static_cast <float> (startPosition.getX()));
                        voxels[index++] = Math::Vector3D<float>(static_cast <float> (size.getX()) - static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2), z - static_cast <float> (size.getZ() / 2)).normSquared();
                    }
                    currentPosition.setY(currentPosition.getY() + resolution);
                    currentPosition.setZ(static_cast <float> (startPosition.getZ()));
                    for (float x = 0; x <= static_cast <float> (size.getX()); x += resolution) {
                        voxels[index++] = Math::Vector3D<float>(x - static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2), static_cast <float> (size.getZ()) - static_cast <float> (size.getZ() / 2)).normSquared();
                    }
                    std::cout << voxels << std::endl;
                    evenCacheLine = !evenCacheLine;
                }

                index = (evenCacheLine) ? (0) : (layerSize);
                for (float z = 0; z <= static_cast <float> (size.getZ()) - resolution; z += resolution) {
                    for (float x = 0; x <= static_cast <float> (size.getX()) - resolution; x += resolution) {
                        std::uint8_t corners = 0b00000000;
                        tmp = (evenCacheLine) ? (index + layerSize) : (index - layerSize);
                        if (voxels[index] < threshold) {
                            corners |= 0b00000001;
                        }
                        if (voxels[index + lineWidth] < threshold) {
                            corners |= 0b00000010;
                        }
                        if (voxels[index + lineWidth + 1] < threshold) {
                            corners |= 0b00000100;
                        }
                        if (voxels[index + 1] < threshold) {
                            corners |= 0b00001000;
                        }
                        if (voxels[tmp] < threshold) {
                            corners |= 0b00010000;
                        }
                        if (voxels[tmp + lineWidth] < threshold) {
                            corners |= 0b00100000;
                        }
                        if (voxels[tmp + lineWidth + 1] < threshold) {
                            corners |= 0b01000000;
                        }
                        if (voxels[tmp + 1] < threshold) {
                            corners |= 0b10000000;
                        }

                        Utility::String res;
                        res << ((corners & 0b10000000) ? ('1') : ('0'));
                        res << ((corners & 0b01000000) ? ('1') : ('0'));
                        res << ((corners & 0b00100000) ? ('1') : ('0'));
                        res << ((corners & 0b00010000) ? ('1') : ('0'));
                        res << ((corners & 0b00001000) ? ('1') : ('0'));
                        res << ((corners & 0b00000100) ? ('1') : ('0'));
                        res << ((corners & 0b00000010) ? ('1') : ('0'));
                        res << ((corners & 0b00000001) ? ('1') : ('0'));

                        std::cout << res << std::endl;

                        index++;
                        if (edgeTable[corners] == 0) {
                            continue;
                        }

                        if (edgeTable[corners] & 1) {
                            vertices[0] = Math::Vector3D<float>(0.0f, 0.0f, 0.5f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 2) {
                            vertices[1] = Math::Vector3D<float>(0.5f, 0.0f, 1.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 4) {
                            vertices[2] = Math::Vector3D<float>(1.0f, 0.0f, 0.5f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 8) {
                            vertices[3] = Math::Vector3D<float>(0.5f, 0.0f, 0.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 16) {
                            vertices[4] = Math::Vector3D<float>(0.0f, 1.0f, 0.5f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 32) {
                            vertices[5] = Math::Vector3D<float>(0.5f, 1.0f, 1.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 64) {
                            vertices[6] = Math::Vector3D<float>(1.0f, 1.0f, 0.5f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 128) {
                            vertices[7] = Math::Vector3D<float>(0.5f, 1.0f, 0.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 256) {
                            vertices[8] = Math::Vector3D<float>(0.0f, 0.5f, 0.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 512) {
                            vertices[9] = Math::Vector3D<float>(0.0f, 0.5f, 1.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 1024) {
                            vertices[10] = Math::Vector3D<float>(1.0f, 0.5f, 1.0f) * resolution + currentPosition;
                        }
                        if (edgeTable[corners] & 2048) {
                            vertices[11] = Math::Vector3D<float>(1.0f, 0.5f, 0.0f) * resolution + currentPosition;
                        }

                        for (int i = 0; triTable[corners][i] != 0xFF; i += 3) {
                            ibo.addData(vertices[triTable[corners][i    ]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            ibo.addData(vertices[triTable[corners][i + 1]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            ibo.addData(vertices[triTable[corners][i + 2]], Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                        }
                        currentPosition.setX(currentPosition.getX() + resolution);
                    }
                    index++;
                    currentPosition.setZ(currentPosition.getZ() + resolution);
                    currentPosition.setX(static_cast <float> (startPosition.getX()));
                }

                /*for (float y = resolution; y <= static_cast <float> (size.getH()); y += resolution) {
                    voxels[index++] = Math::Vector2D<float>(-static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2)).normSquared();
                    for (float x = resolution; x <= static_cast <float> (size.getW()); x += resolution) {
                        voxels[index] = Math::Vector2D<float>(x - static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2)).normSquared();

                        std::uint8_t corners = 0b0000;
                        if (voxels[index - 1] <= threshold) {
                            corners |= 0b0001;
                        }
                        if (voxels[index] <= threshold) {
                            corners |= 0b0010;
                        }
                        if (voxels[(index < static_cast <int> (layerSize)) ? (index + layerSize) : (index - layerSize)] <= threshold) {
                            corners |= 0b0100;
                        }
                        if (voxels[(index < static_cast <int> (layerSize)) ? (index + layerSize - 1) : (index - layerSize - 1)] <= threshold) {
                            corners |= 0b1000;
                        }

                        for (unsigned int triIndex = 0; triIndex < lookupSize[corners]; triIndex++) {
                            Math::Vector3D<float> p1(lookupTable[corners][triIndex * 9]        * resolution + currentPosition.getX(),
                                                     lookupTable[corners][triIndex * 9 + 1]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][triIndex * 9 + 2]);
                            Math::Vector3D<float> p2(lookupTable[corners][triIndex * 9 + 3]    * resolution + currentPosition.getX(),
                                                     lookupTable[corners][triIndex * 9 + 4]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][triIndex * 9 + 5]);
                            Math::Vector3D<float> p3(lookupTable[corners][triIndex * 9 + 6]    * resolution + currentPosition.getX(),
                                                     lookupTable[corners][triIndex * 9 + 7]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][triIndex * 9 + 8]);
                            ibo.addData(p1, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            ibo.addData(p2, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            ibo.addData(p3, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                        }
                        currentPosition.setX(currentPosition.getX() + resolution);

                        index++;
                    }
                    currentPosition.setY(currentPosition.getY() + resolution);
                    currentPosition.setX(static_cast <float> (startPosition.getX()));
                    index = static_cast <int> (static_cast <std::size_t> (index) % cacheSize);
                }*/
            }

        }
    }
