
    /**
     * @file NRE_ShaderException.hpp
     * @brief Declaration of Engine's Exception's Object : ShaderException
     * @author Louis ABEL
     * @date 16/08/2019
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
         * @namespace Exception
         * @brief Utility's API
         */
        namespace Exception {

            /**
             * @class ShaderException
             * @brief Exception's Object : An exception for Shader related operation
             */
            class ShaderException : public IException {
                public:
                    /**
                     * Construct a ShaderException with a custom log
                     * @param log the ShaderException's log
                     */
                    ShaderException(Utility::String const& log) throw() : IException("Shader Exception : " + log) {
                    }
            };
        }
    }
