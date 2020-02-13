    
    /**
     * @file NRE_Chunk.hpp
     * @brief Declaration of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 13/02/2020
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "NRE_Chunk.hpp"

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World module
         */
        namespace World {

            /**
             * @class WaterChunk
             * @brief Manage a collection of liquid voxels
             */
            class WaterChunk : public Utility::Stringable<WaterChunk> {
                private :   // Fields
                    Chunk::VoxelsContainer voxels;      /**< The chunk's cells */
                    Chunk* parent;                      /**< The parent */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the chunk from its parent
                         * @param p the chunk's parent
                         */
                        WaterChunk(Chunk* p = nullptr);

                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the chunk to copy
                         */
                        WaterChunk(WaterChunk const& c) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the chunk to move
                         */
                        WaterChunk(WaterChunk && c) = default;
    
                    //## Getter ##//
                        /**
                         * @return the parent
                         */
                        Chunk const& getParent() const;
                        /**
                         * @return the parent
                         */
                        Chunk& getParent();
    
                    //## Setter ##//
                        /**
                         * Set the chunk's parent
                         * @param p the new parent
                         */
                        void setParent(Chunk* p);

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        Chunk::Iterator begin();
                        /**
                         * @return a const iterator on the first element
                         */
                        Chunk::ConstIterator begin() const;
                        /**
                         * @return a const iterator on the first element
                         */
                        Chunk::ConstIterator cbegin() const;
                        /**
                         * @return an iterator on the end of the container
                         */
                        Chunk::Iterator end();
                        /**
                         * @return a const iterator on the end of the container
                         */
                        Chunk::ConstIterator end() const;
                        /**
                         * @return a const iterator on the end of the container
                         */
                        Chunk::ConstIterator cend() const;

                    //## Access Operator ##//
                        /**
                         * Return a reference on a chunk's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        float& operator [](std::size_t index);
                        /**
                         * Return a const reference on a chunk's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                         float const& operator [](std::size_t index) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the chunk to copy
                         * @return  the reference of himself
                         */
                        WaterChunk& operator =(WaterChunk const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the chunk to move into this
                         * @return  the reference of himself
                         */
                        WaterChunk& operator =(WaterChunk && c) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the chunk into a string
                         * @return the converted chunk
                         */
                        Utility::String toString() const;
            };

        }
    }

    #include "NRE_WaterChunk.tpp"
