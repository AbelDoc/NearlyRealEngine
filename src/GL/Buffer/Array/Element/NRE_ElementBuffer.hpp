
    /**
     * @file NRE_ElementBuffer.hpp
     * @brief Declaration of Engine's GL's Object : ElementBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <iostream>
    #include <string>

    #include "../NRE_ArrayBuffer.hpp"

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
             * @class ElementBuffer
             * @brief Manage an element buffer
             */
            class ElementBuffer : public ArrayBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ElementBuffer() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the element buffer to move
                         */
                        ElementBuffer(ElementBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * ElementBuffer Deconstructor
                         */
                        ~ElementBuffer() = default;

                    //## Getter ##//
                        /**
                         * @return the specific OpenGL buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the element buffer to move into this
                         * @return      the reference of himself
                         */
                        ElementBuffer& operator =(ElementBuffer && b) = default;

            };
        }
    }

    #include "NRE_ElementBuffer.tpp"
