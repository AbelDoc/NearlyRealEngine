
    /**
     * @file NRE_CloudFactory.tpp
     * @brief Implementation of Engine's World's Object : CloudFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            Utility::Vector<float> CloudFactory::createCircle(Math::Vector2D<unsigned int> const& size, float resolution) {
                Utility::Vector<float> voxels;

                voxels.reserve((static_cast <unsigned int> (static_cast <float> (size.getW()) / resolution) + 1) * (static_cast <unsigned int> (static_cast <float> (size.getH()) / resolution) + 1));

                for (float y = 0; y <= static_cast <float> (size.getH()); y += resolution) {
                    for (float x = 0; x <= static_cast <float> (size.getW()); x += resolution) {
                        voxels.emplaceBack(Math::Vector2D<float>(x - static_cast <float> (size.getX() / 2), y - static_cast <float> (size.getY() / 2)).normSquared());
                    }
                }

                return voxels;
            }

        }
    }
