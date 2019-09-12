
    /**
     * @file NRE_CellPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : CellPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            void CellPolygonizer::polygonize(GL::VBO<GL::PrimitiveVertex>& vbo, Utility::Vector<Cell> const& cells, Math::Vector2D<unsigned int> const& size, Math::Point2D<int> const& startPosition) {
                Math::Point2D<float> currentPosition(static_cast <float> (startPosition.getX()), static_cast <float> (startPosition.getY()));
                for (unsigned int y = 0; y < size.getH(); y++) {
                    for (unsigned int x = 0; x < size.getW(); x++) {
                        Cell const& current = cells[y * size.getH() + x];
                        for (unsigned int index = 0; index < lookupSize[current.getWeight()]; index++) {
                            Math::Vector3D<float> p1(lookupTable[current.getWeight()][index * 9]        + currentPosition.getX(),
                                                     lookupTable[current.getWeight()][index * 9 + 1]    + currentPosition.getY(),
                                                     lookupTable[current.getWeight()][index * 9 + 2]);
                            Math::Vector3D<float> p2(lookupTable[current.getWeight()][index * 9 + 3]    + currentPosition.getX(),
                                                     lookupTable[current.getWeight()][index * 9 + 4]    + currentPosition.getY(),
                                                     lookupTable[current.getWeight()][index * 9 + 5]);
                            Math::Vector3D<float> p3(lookupTable[current.getWeight()][index * 9 + 6]    + currentPosition.getX(),
                                                     lookupTable[current.getWeight()][index * 9 + 7]    + currentPosition.getY(),
                                                     lookupTable[current.getWeight()][index * 9 + 8]);
                            vbo.addData(p1, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            vbo.addData(p2, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                            vbo.addData(p3, Math::Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                        }
                        currentPosition.setX(currentPosition.getX() + 1);
                    }
                    currentPosition.setY(currentPosition.getY() + 1);
                    currentPosition.setX(static_cast <float> (startPosition.getX()));
                }
            }

        }
    }
