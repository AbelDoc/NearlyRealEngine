
    /**
     * @file NRE_STBException.hpp
     * @brief Declaration of Engine's Exception's Object : STBException
     * @author Louis ABEL
     * @date 16/08/2019
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
             * @class STBException
             * @brief Exception's Object : An exception for STB related operation
             */
            class STBException : public IException {
                public:
                    /**
                     * Construct a STBException with a custom log
                     * @param log the STBException's log
                     */
                    STBException(Core::String const& log) throw() : IException("STB Exception : " + log) {
                    }
            };
        }
    }
