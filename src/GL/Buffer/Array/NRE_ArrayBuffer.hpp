
    /**
     * @file NRE_ArrayBuffer.hpp
     * @brief Declaration of Engine's GL's Object : ArrayBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Utility.hpp>

     #include "../../../Header/NRE_GL.hpp"

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
             * @class ArrayBuffer
             * @brief Manage an array buffer for VBO communication with OpenGL
             */
            class ArrayBuffer {
                private :   // Fields
                    Id id;              /**< The buffer id */
                    bool allocated;     /**< Tell if the buffer is allocated */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ArrayBuffer();

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param b the array buffer to copy
                         */
                        ArrayBuffer(ArrayBuffer const& b) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the array buffer to move
                         */
                        ArrayBuffer(ArrayBuffer && b);

                    //## Deconstructor ##//
                        /**
                         * ArrayBuffer Deconstructor
                         */
                        virtual ~ArrayBuffer();

                    //## Getter ##//
                        /**
                         * @return the specific OpenGL buffer's target
                         */
                        virtual BufferTarget getTarget() const = 0;
                        /**
                         * @return if the buffer is allocated
                         */
                        bool isAllocated() const;
                        /**
                         * @return the buffer id
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
                         * Allocate the object
                         */
                        void allocate();
                        /**
                         * Deallocate the object
                         */
                        void deallocate();
                        /**
                         * Allocate the buffer storage
                         * @param size  the buffer's size
                         * @param usage the buffer's usage
                         */
                        void allocate(std::size_t size, StreamUsage usage);
                        /**
                         * Update the buffer's data
                         * @param offset the data's offset in the buffer
                         * @param size   the data's updated size
                         * @param data   the data to send
                         */
                        void update(GLintptr offset, std::size_t size, const void* data);
                        /**
                         * Allocate the buffer storage and send data
                         * @param size  the buffer's size
                         * @param data  the buffer's data
                         * @param usage the buffer's usage
                         */
                        void allocateAndFill(std::size_t size, const void* data, StreamUsage usage);
                        /**
                         * Orphan the buffer
                         * @param size  the buffer's size, need to be same as the allocated size
                         * @param usage the buffer's usage, need to be same as the allocated usage
                         */
                        void orphan(std::size_t size, StreamUsage usage);

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param b the array buffer to move into this
                         * @return  the reference of himself
                         */
                        ArrayBuffer& operator =(ArrayBuffer const& b) = delete;
                        /**
                         * Move assignment of b into this
                         * @param b the array buffer to move into this
                         * @return  the reference of himself
                         */
                        ArrayBuffer& operator =(ArrayBuffer && b);

            };
        }
    }

    #include "NRE_ArrayBuffer.tpp"