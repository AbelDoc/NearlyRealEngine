
    /**
     * @file NRE_TextureBuffer.hpp
     * @brief Declaration of Engine's GL's Object : TextureBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../NRE_Attachable.hpp"

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
             * @pure TextureBuffer
             * @brief Describe a base texture buffer for 2D & 3D texture specialization
             */
            class TextureBuffer : public Attachable,
                                  public Utility::Identifiable<TextureBuffer> {
                private:    //Fields
                    TextureType type;    /**< The texture's pixel data type */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        TextureBuffer();
                        /**
                         * Construct a Texture buffer with his given data type
                         * @param t the texture's data type
                         */
                        TextureBuffer(TextureType t);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the texture buffer to move
                         */
                        TextureBuffer(TextureBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * TextureBuffer Deconstructor
                         */
                        virtual ~TextureBuffer() = default;

                    //## Getter ##//
                        /**
                         * @return the texture's type
                         */
                        TextureType getType() const;
                        /**
                         * @return the texture buffer's target
                         */
                        virtual BufferTarget getTarget() const = 0;

                    //## Methods ##//
                        /**
                         * Bind the object
                         */
                        void bind() const override;
                        /**
                         * Unbind the object
                         */
                        void unbind() const override;
                        /**
                         * Create the object's id
                         */
                        void createIdImpl();
                        /**
                         * Delete the object's id
                         */
                        void deleteIdImpl();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool existImpl() const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the texture buffer to move into this
                         * @return      the reference of himself
                         */
                        TextureBuffer& operator =(TextureBuffer && b) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the texture buffer into a string
                         * @return the converted texture buffer
                         */
                        Utility::String toString() const override;
    
                    using Attachable::allocate;
            };
        }
    }

    #include "NRE_TextureBuffer.tpp"
