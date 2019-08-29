
    /**
     * @file NRE_AbstractVBO.hpp
     * @brief Declaration of Engine's GL's Object : AbstractVBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <cassert>

     #include "../Buffer/Array/Attribute/NRE_AttributeBuffer.hpp"

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
             * @class AbstractVBO
             * @brief Manage a layout of data, abstract base for specialized layout
             */
            class AbstractVBO {
                private:    //Fields
                    AttributeBuffer buffer; /**< The attribute buffer */
                    GLsizei count;          /**< The number of vertex */
                    std::size_t size;       /**< The data's size in bytes */
                    StreamUsage usage;      /**< The buffer's streaming usage */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        AbstractVBO() = delete;
                        /**
                         * Construct an abstract VBO from the buffer's streaming usage
                         * @param stream the buffer's streaming usage
                         */
                        AbstractVBO(StreamUsage stream);

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param b the vbo to copy
                         */
                        AbstractVBO(AbstractVBO const& b) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the vbo to move
                         */
                        AbstractVBO(AbstractVBO && b);

                    //## Deconstructor ##//
                        /**
                         * AbstractVBO Deconstructor
                         */
                        virtual ~AbstractVBO() = default;

                    //## Getter ##//
                        /**
                         * Data count getter
                         * @return the number of vertex
                         */
                        virtual std::size_t getDataCount() const = 0;

                    //## Methods ##//
                        /**
                         * Store calls for VAO managing
                         */
                        virtual void access() const = 0;
                        /**
                         * Allocate the VBO
                         * @param nb the number of vertex
                         */
                        void allocate(int nb);
                        /**
                         * Update the attribute buffer
                         * @param offset the data's offset
                         */
                        void update(GLintptr offset = 0);
                        /**
                         * Update the attribute buffer from an external data's source
                         * @param data   the external data's source
                         * @param nb     the number of vertex to update
                         * @param offset the data's offset
                         */
                        void update(const void* data, std::size_t nb, GLintptr offset = 0);
                        /**
                         * Allocate and fill the VBO
                         */
                        virtual void allocateAndFill();
                        /**
                         * Orphan the attribute buffer
                         */
                        void orphan();
                        /**
                         * Reallocate the VBO
                         * @return tell if an reallocation has happened
                         */
                        bool reallocate();
                        /**
                         * Check if the buffer has to be orphaned or reallocated
                         * @return the test's result
                         */
                        virtual bool checkReallocation();
                        /**
                         * Reserve the attribute data's storage
                         * @param capacity the capacity to get
                         */
                        virtual void reserve(std::size_t capacity) = 0;
                        /**
                         * Draw the VBO
                         * @param mode the drawing mode
                         */
                        virtual void draw(DrawMode mode = GL_TRIANGLES) const;
                        /**
                         * Draw the VBO as it's an instanced one
                         * @param instance the number of instance
                         * @param mode     the drawing mode
                         */
                        virtual void drawInstanced(int instance, DrawMode mode = GL_TRIANGLES) const;
                        /**
                         * Perform a multi rendering
                         * @param firsts    an array of first vertex
                         * @param counts    an array of vertex count
                         * @param drawCount the number of rendering to perform
                         * @param mode      the drawing mode
                         */
                        void drawMulti(const int* firsts, const int* counts, int drawCount, DrawMode mode = GL_TRIANGLES) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param b the vbo to copy
                         * @return  the reference of himself
                         */
                        AbstractVBO& operator =(AbstractVBO const& b) = delete;
                        /**
                         * Move assignment of b into this
                         * @param b the vbo to move into this
                         * @return  the reference of himself
                         */
                        AbstractVBO& operator =(AbstractVBO && b);

                    //## Stream Operator ##//
                        /**
                         * Convert the vbo into a string
                         * @return the converted vbo
                         */
                        virtual Utility::String toString() const = 0;

                protected: // Methods
                    /**
                     * @return the buffer's streaming usage
                     */
                    StreamUsage getUsage() const;
                    /**
                     * Attribute buffer getter
                     * @return the attribute buffer
                     */
                    AttributeBuffer const& getAttributeBuffer() const;

                private:   // Methods
                    /**
                     * Clear the attribute data's storage
                     */
                    virtual void clear() = 0;
                    /**
                     * Layout type's size getter
                     * @return the layout type's size in bytes
                     */
                    virtual std::size_t getLayoutSize() const = 0;
                    /**
                     * Data size getter
                     * @return the size of stored data in bytes
                     */
                    std::size_t getDataSize() const;
                    /**
                     * Data's pointer getter
                     * @return the pointer to data
                     */
                    virtual const void* getDataPointer() const = 0;

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, AbstractVBO const& o);
        }
    }

    #include "NRE_AbstractVBO.tpp"
