
    /**
     * @file NRE_AttributeBuffer.hpp
     * @brief Declaration of Engine's GL's Object : AttributeBuffer
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
             * @class AttributeBuffer
             * @brief Manage an attribute buffer
             */
            class AttributeBuffer : public ArrayBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        AttributeBuffer() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the attribute buffer to move
                         */
                        AttributeBuffer(AttributeBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * AttributeBuffer Deconstructor
                         */
                        ~AttributeBuffer() = default;

                    //## Getter ##//
                        /**
                         * @return the specific OpenGL buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the attribute buffer to move into this
                         * @return      the reference of himself
                         */
                        AttributeBuffer& operator =(AttributeBuffer && b) = default;

            };
        }
    }

    #include "NRE_AttributeBuffer.tpp"
