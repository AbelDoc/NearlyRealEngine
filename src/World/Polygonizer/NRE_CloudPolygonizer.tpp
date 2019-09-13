
    /**
     * @file NRE_CloudPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : CloudPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            void CloudPolygonizer::polygonize(GL::VBO<GL::PrimitiveVertex>& vbo, Utility::Vector<float> const& voxels, Math::Point2D<int> const& startPosition, Math::Vector2D<unsigned int> const& size, float resolution, float threshold) {
                Math::Point2D<float> currentPosition(static_cast <float> (startPosition.getX()), static_cast <float> (startPosition.getY()));

                Math::Vector2D<unsigned int> dataSize(static_cast <unsigned int> (static_cast <float> (size.getH()) / resolution),
                                                      static_cast <unsigned int> (static_cast <float> (size.getW()) / resolution));

                for (unsigned int y = 0; y < dataSize.getH(); y++) {
                    for (unsigned int x = 0; x < dataSize.getW(); x++) {

                        std::uint8_t corners = 0b0000;
                        if (voxels[(y + 1) * (dataSize.getW() + 1) + x    ] <= threshold) {
                            corners |= 0b0001;
                        }
                        if (voxels[(y + 1) * (dataSize.getW() + 1) + x + 1] <= threshold) {
                            corners |= 0b0010;
                        }
                        if (voxels[y       * (dataSize.getW() + 1) + x + 1] <= threshold) {
                            corners |= 0b0100;
                        }
                        if (voxels[y       * (dataSize.getW() + 1) + x    ] <= threshold) {
                            corners |= 0b1000;
                        }

                        for (unsigned int index = 0; index < lookupSize[corners]; index++) {
                            Math::Vector3D<float> p1(lookupTable[corners][index * 9]        * resolution + currentPosition.getX(),
                                                     lookupTable[corners][index * 9 + 1]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][index * 9 + 2]);
                            Math::Vector3D<float> p2(lookupTable[corners][index * 9 + 3]    * resolution + currentPosition.getX(),
                                                     lookupTable[corners][index * 9 + 4]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][index * 9 + 5]);
                            Math::Vector3D<float> p3(lookupTable[corners][index * 9 + 6]    * resolution + currentPosition.getX(),
                                                     lookupTable[corners][index * 9 + 7]    * resolution + currentPosition.getY(),
                                                     lookupTable[corners][index * 9 + 8]);
                            vbo.addData(p1, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            vbo.addData(p2, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            vbo.addData(p3, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                        }
                        currentPosition.setX(currentPosition.getX() + resolution);
                    }
                    currentPosition.setY(currentPosition.getY() + resolution);
                    currentPosition.setX(static_cast <float> (startPosition.getX()));
                }
            }

        }
    }
