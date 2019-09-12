
    /**
     * @file NRE_ShapeFactory.tpp
     * @brief Implementation of Engine's World's Object : ShapeFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            Utility::Vector<Cell> ShapeFactory::createCircle(float radius, Math::Point2D<float> const& center, Math::Vector2D<unsigned int> const& gridSize) {
                Utility::Vector<Cell> cells;
                Utility::Vector<bool> ins;
                ins.reserve((gridSize.getW() + 1) * (gridSize.getH() + 1));
                cells.reserve(gridSize.getW() * gridSize.getH());

                int hX = gridSize.getW() / 2;
                int hY = gridSize.getH() / 2;

                for (int y = -hY; y <= hY; y++) {
                    for (int x = -hX; x <= hX; x++) {
                        float distance = Math::Vector2D<float>(static_cast <float> (x) - center.getX(), static_cast <float> (y) - center.getY()).normSquared();
                        ins.emplaceBack(distance <= (radius * radius));
                    }
                }

                for (unsigned int y = 0; y < gridSize.getH(); y++) {
                    for (unsigned int x = 0; x < gridSize.getW(); x++) {
                        CellCorners corners = 0b0000;
                        if (ins[(y + 1) * (gridSize.getW() + 1) + x    ]) {
                            corners |= 0b0001;
                        }
                        if (ins[(y + 1) * (gridSize.getW() + 1) + x + 1]) {
                            corners |= 0b0010;
                        }
                        if (ins[y       * (gridSize.getW() + 1) + x + 1]) {
                            corners |= 0b0100;
                        }
                        if (ins[y       * (gridSize.getW() + 1) + x    ]) {
                            corners |= 0b1000;
                        }
                        cells.emplaceBack(corners);
                    }
                }

                return cells;
            }

        }
    }
