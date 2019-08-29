
    /**
     * @file NRE_RenderBuffer.hpp
     * @brief Declaration of Engine's GL's Object : RenderBuffer
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
             * @class RenderBuffer
             * @brief Manage a render buffer
             */
            class RenderBuffer : public Attachable  {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        RenderBuffer() = delete;
                        /**
                         * Construct the render buffer from passed format and size
                         * @param internalFormat the buffer's internal format
                         * @param w              the buffer's width
                         * @param h              the buffer's height
                         */
                        RenderBuffer(RenderInternalFormat internalFormat, GLsizei w, GLsizei h);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the render buffer to move
                         */
                        RenderBuffer(RenderBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * RenderBuffer Deconstructor
                         */
                        ~RenderBuffer() = default;

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
                        void createId() override;
                        /**
                         * Delete the object's id
                         */
                        void deleteId() override;
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const;
                        /**
                         * Allocate the buffer's storage
                         * @param internalFormat the buffer's internal format
                         * @param w              the buffer's width
                         * @param h              the buffer's height
                         */
                        void allocate(RenderInternalFormat internalFormat, GLsizei w, GLsizei h) const;
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         */
                        void attach(AttachPoint target) const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this, leaving b empty
                         * @param b the render buffer to move into this
                         * @return      the reference of himself
                         */
                        RenderBuffer& operator =(RenderBuffer && b) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the render buffer into a string
                         * @return the converted render buffer
                         */
                        Utility::String toString() const override;

            };
        }
    }

    #include "NRE_RenderBuffer.tpp"
