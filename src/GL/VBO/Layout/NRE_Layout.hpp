
    /**
     * @file NRE_Layout.hpp
     * @brief Declaration of Engine's GL's Object : Layout
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../../NRE_GL.hpp"

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
             * @class Layout
             * @brief Static function for layout handling
             */
            class Layout {
                public:    // Static
                    //## Methods ##//
                        /**
                         * Enable a vertex attribute
                         * @param index  the attribute's index
                         * @param size   the attribute's number of component
                         * @param type   the attribute's type
                         * @param stride the attributes stride in the buffer
                         * @param offset the attribute's offset in the buffer
                         */
                        static void enableAttribute(int index, int size, GLenum type, int stride = 0, void* offset = 0) {
                            glEnableVertexAttribArray(index);
                            glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
                        }
                        /**
                         * Divide a vertex attribute
                         * @param index the attribute's index
                         * @param count the attribute's division count
                         */
                        static void divideAttribute(int index, int count) {
                            glVertexAttribDivisor(index, count);
                        }

            };
        }
    }
