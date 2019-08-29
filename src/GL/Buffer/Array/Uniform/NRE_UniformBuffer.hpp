
    /**
     * @file NRE_UniformBuffer.hpp
     * @brief Declaration of Engine's GL's Object : UniformBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

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
             * @class UniformBuffer
             * @brief Manage an uniform buffer
             */
            class UniformBuffer : public ArrayBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        UniformBuffer() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the uniform buffer to move
                         */
                        UniformBuffer(UniformBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * UniformBuffer Deconstructor
                         */
                        ~UniformBuffer() = default;

                    //## Getter ##//
                        /**
                         * @return the specific OpenGL buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Methods ##//
                        /**
                         * Bind the uniform buffer base
                         * @param index the binding point
                         */
                        void bindBase(int index);
                        /**
                         * Connect the buffer to a program
                         * @param program   the program's id
                         * @param index     the binding point
                         * @param name      the block name in the program
                         */
                        void connect(Id program, int index, Utility::String const& name);

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the uniform buffer to move into this
                         * @return      the reference of himself
                         */
                        UniformBuffer& operator =(UniformBuffer && b) = default;

            };
        }
    }

    #include "NRE_UniformBuffer.tpp"
