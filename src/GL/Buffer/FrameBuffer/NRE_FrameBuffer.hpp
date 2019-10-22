
    /**
     * @file NRE_FrameBuffer.hpp
     * @brief Declaration of Engine's GL's Object : FrameBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../Attachable/NRE_Attachable.hpp"

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
             * @class FrameBuffer
             * @brief Manage the link between GPU Frame buffer and Engine
             */
            class FrameBuffer : public Utility::Stringable<FrameBuffer> {
                protected :   // Fields
                    Id id;              /**< The frame buffer id */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        FrameBuffer();

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param b the frame buffer to copy
                         */
                        FrameBuffer(FrameBuffer const& b) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the frame buffer to move
                         */
                        FrameBuffer(FrameBuffer && b);

                    //## Deconstructor ##//
                        /**
                         * FrameBuffer Deconstructor
                         */
                        virtual ~FrameBuffer();

                    //## Getter ##//
                        /**
                         * @return the frame buffer id
                         */
                        Id getId() const;

                    //## Methods ##//
                        /**
                         * Bind the object
                         */
                        void bind() const;
                        /**
                         * Unbind the object
                         */
                        void unbind() const;
                        /**
                         * Create the object's id
                         */
                        void createId();
                        /**
                         * Delete the object's id
                         */
                        void deleteId();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const;
                        /**
                         * Attach an attachable to the framebuffer
                         * @param attachment the attachment's point
                         * @param target     the target to attach
                         */
                        void attach(AttachPoint attachment, const Attachable* target) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param b the frame buffer to copy
                         * @return  the reference of himself
                         */
                        FrameBuffer& operator =(FrameBuffer const& b) = delete;
                        /**
                         * Move assignment of b into this
                         * @param b the frame buffer to move into this
                         * @return  the reference of himself
                         */
                        FrameBuffer& operator =(FrameBuffer && b);

                    //## Stream Operator ##//
                        /**
                         * Convert the frame buffer into a string
                         * @return the converted frame buffer
                         */
                        Utility::String toString() const;

            };
        }
    }

    #include "NRE_FrameBuffer.tpp"
