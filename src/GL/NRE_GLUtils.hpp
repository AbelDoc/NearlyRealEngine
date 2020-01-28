
    /**
     * @file GL/NRE_GLUtils.hpp
     * @brief Declaration of NearlyRealEngine's GL Advanced Utilitary Functions
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "NRE_GL.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace GL
         * @brief Engine's GL module
         */
        namespace GL {

            /**
             * Bind the given texture to the given texture unit
             * @param tex   the texture to bind
             * @param index the texture unit
             */
            void bindTexture(Attachable const& tex, int index = 0);
            /**
             * Bind the given texture to the given texture unit
             * @param tex   the texture to bind
             * @param index the texture unit
             */
            void bindTexture(std::unique_ptr<Attachable> const& tex, int index = 0);
            /**
             * Unbind the given texture to the given texture unit
             * @param tex   the texture to bind
             * @param index the texture unit
             */
            void unbindTexture(Attachable const& tex, int index = 0);
            /**
             * Unbind the given texture to the given texture unit
             * @param tex   the texture to bind
             * @param index the texture unit
             */
            void unbindTexture(std::unique_ptr<Attachable> const& tex, int index = 0);

        }
    }

    #include "NRE_GLUtils.tpp"
