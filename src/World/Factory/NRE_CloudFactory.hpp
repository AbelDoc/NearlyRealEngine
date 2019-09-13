
    /**
     * @file NRE_CloudFactory.hpp
     * @brief Declaration of Engine's World's Object : CloudFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <Header/NRE_Utility.hpp>

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World module
         */
        namespace World {

            /**
             * @class CloudFactory
             * @brief Manage the creation of points cloud
             */
            class CloudFactory {
                public :    // Static
                    /**
                     * Create a points cloud where each point as a value corresponding its square distance from the cloud center
                     * @param size       the dataset size
                     * @param resolution the resolution
                     * @return the points cloud
                     */
                    static Utility::Vector<float> createCircle(Math::Vector2D<unsigned int> const& size, float resolution);
            };

        }
    }

    #include "NRE_CloudFactory.tpp"
