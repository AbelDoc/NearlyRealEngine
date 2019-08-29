
    /**
     * @file NRE_GLException.hpp
     * @brief Declaration of Engine's Exception's Object : GLException
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
             * @class GLException
             * @brief Exception's Object : An exception for OpenGL related operation
             */
            class GLException : public IException {
                public:
                    /**
                     * Construct a GLException with a custom log
                     * @param log the GLException's log
                     */
                    GLException(Utility::String const& log) throw() : IException("GL Exception : " + log) {
                    }
            };
        }
    }
