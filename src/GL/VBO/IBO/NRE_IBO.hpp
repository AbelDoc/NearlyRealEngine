
    /**
     * @file NRE_IBO.hpp
     * @brief Declaration of Engine's GL's Object : IBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <cstdint>

     #include "../../Buffer/Array/Element/NRE_ElementBuffer.hpp"
     #include "../NRE_VBO.hpp"

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
             * @class IBO
             * @brief Manage streaming of data to the GPU with indexed manners
             */
            template <class Layout, class Index = uint32_t>
            class IBO : public VBO<Layout> {
                static_assert (sizeof(Index) != 1 || sizeof(Index) != 2 || sizeof(Index) != 4, "Index type size must be one of : 1, 2, 4 bytes per index");

                private:    //Fields
                    ElementBuffer element;          /**< The element buffer */
                    Utility::Vector<Index> index;   /**< The index's data */
                    std::size_t indexCount;         /**< The number of index */
                    std::size_t indexSize;          /**< The index's data size in bytes */
                    IndexType type;                 /**< The IBO type */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        IBO() = delete;
                        /**
                         * Construct an IBO from the buffer's streaming usage
                         * @param stream the buffer's streaming usage
                         */
                        IBO(StreamUsage stream);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the ibo to move
                         */
                        IBO(IBO && b);

                    //## Deconstructor ##//
                        /**
                         * IBO Deconstructor
                         */
                        ~IBO() = default;

                    //## Methods ##//
                        /**
                         * Add an index to the stored data
                         * @param idx the index to add
                         */
                        void addIndex(Index idx);
                        /**
                         * Add an arary of index to the stored data
                         * @param idxs    the index's array to add
                         * @param nbIndex the number of index to add
                         */
                        void addIndex(Index* idxs, std::size_t nbIndex);
                        /**
                         * Allocate the IBO
                         * @param nb      the number of vertex
                         * @param nbIndex the number of index
                         */
                        void allocate(std::size_t nb, std::size_t nbIndex);
                        /**
                         * Update the index buffer
                         * @param offset the data's offset
                         */
                        void updateIndex(GLintptr offset = 0);
                        /**
                         * Update the index buffer from an external data's source
                         * @param data   the external data's source
                         * @param nb     the number of index to update
                         * @param offset the data's offset
                         */
                        void updateIndex(const void* data, std::size_t nb, GLintptr offset = 0);
                        /**
                         * Allocate and fill the IBO
                         */
                        void allocateAndFill() override;
                        /**
                         * Clear the index data's storage
                         */
                        void clearIndex();
                        /**
                         * Reserve the index data's storage
                         * @param capacity the capacity to get
                         */
                        void reserveIndex(std::size_t capacity);
                        /**
                         * Orphan the index buffer
                         */
                        void orphanIndex();
                        /**
                         * Check if the buffer has to be orphaned or reallocated
                         * @return the test's result
                         */
                        bool checkReallocation() override;
                        /**
                         * Access the buffer to save command in a VAO
                         */
                        void access() const override;
                        /**
                         * Draw the IBO
                         * @param mode the drawing mode
                         */
                        void draw(DrawMode mode = GL_TRIANGLES) const override;
                        /**
                         * Draw the IBO as it's an instanced one
                         * @param instance the number of instance
                         * @param mode     the drawing mode
                         */
                        void drawInstanced(int instance, DrawMode mode = GL_TRIANGLES) const override;
                        /**
                         * Perform a multi rendering
                         * @param indexes   an array of index count
                         * @param offset    an array of index offset
                         * @param drawCount the number of rendering to perform
                         * @param mode      the drawing mode
                         */
                        void drawMulti(int* indexes, int** offset, int drawCount, DrawMode mode = GL_TRIANGLES) const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the ibo to move into this
                         * @return  the reference of himself
                         */
                        IBO& operator =(IBO && b);

                    //## Stream Operator ##//
                        /**
                         * Convert the ibo into a string
                         * @return the converted ibo
                         */
                        Utility::String toString() const override;

                private:   // Methods
                    /**
                     * @return the number of stored index
                     */
                    std::size_t getIndexCount() const;
                    /**
                     * @return the size of stored index in bytes
                     */
                    std::size_t getIndexSize() const;
                    /**
                     * @return the pointer to index's data
                     */
                    const void* getIndexPointer() const;
                    /**
                     * Allocate and fill the index buffer
                     */
                    void allocateAndFillIndex();
                    /**
                     * @return the index type
                     */
                    IndexType getIndexType() const;

            };
        }
    }

    #include "NRE_IBO.tpp"
