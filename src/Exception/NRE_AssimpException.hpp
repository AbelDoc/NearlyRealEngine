
    /**
     * @file NRE_AssimpException.hpp
     * @brief Declaration of Engine's Exception's Object : AssimpException
     * @author Louis ABEL
     * @date 13/04/2020
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <Header/NRE_Core.hpp>

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Exception
         * @brief Core's API
         */
        namespace Exception {

            /**
             * @class AssimpException
             * @brief Exception's Object : An exception for Assimp related operation
             */
            class AssimpException : public IException {
                public:
                    /**
                     * Construct a AssimpException with a custom log
                     * @param log the AssimpException's log
                     */
                    AssimpException(Core::String const& log) throw() : IException("Assimp Exception : " + log) {
                    }
            };
        }
    }
