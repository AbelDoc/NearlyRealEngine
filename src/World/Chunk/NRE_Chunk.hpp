/**
     * @file NRE_Chunk.hpp
     * @brief Declaration of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "Cell/NRE_Cell.hpp"
    #include <Header/NRE_Math.hpp>

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
             * @class Chunk
             * @brief Manage a collection of voxels
             */
            class Chunk {
                public :    // Static
                    static constexpr std::size_t SIZE_X     = 16;
                    static constexpr std::size_t SIZE_Y     = 16;
                    static constexpr std::size_t SIZE_Z     = 16;
                    static constexpr std::size_t VOLUME     = SIZE_X * SIZE_Y * SIZE_Z;

                    static constexpr std::size_t VOXELS_LAYER_WIDTH = SIZE_X + 1;
                    static constexpr std::size_t VOXELS_LAYER_AREA  = VOXELS_LAYER_WIDTH * (SIZE_Z + 1);
                    static constexpr std::size_t VOXELS_VOLUME      = VOXELS_LAYER_AREA  * (SIZE_Y + 1);
                    
                public :    // Iterator
                    typedef Utility::Array<float, VOXELS_VOLUME> VoxelsContainer;
                    /**< Shortcut to hide Iterator implementation */
                    typedef VoxelsContainer::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef VoxelsContainer::ConstIterator    ConstIterator;


                private :   // Fields
                    VoxelsContainer voxels;         /**< The chunk's cells */
                    Math::Point3D<int> position;    /**< The chunk's position */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the chunk from its position
                         * @param pos the chunk's position
                         */
                        Chunk(Math::Point3D<int> const& pos = {0, 0, 0});

                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the chunk to copy
                         */
                         Chunk(Chunk const& c) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the chunk to move
                         */
                        Chunk(Chunk && c) = default;

                    //## Getter ##//
                        /**
                         * @return the chunk's position
                         */
                        Math::Point3D<int> const& getPosition() const;

                    //## Setter ##//
                        /**
                         * Set the chunk's position
                         * @param p the new position
                         */
                        void setPosition(Math::Point3D<int> const& p);

                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        Iterator begin();
                        /**
                         * @return a const iterator on the first element
                         */
                        ConstIterator begin() const;
                        /**
                         * @return a const iterator on the first element
                         */
                        ConstIterator cbegin() const;
                        /**
                         * @return an iterator on the end of the container
                         */
                        Iterator end();
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator end() const;
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator cend() const;

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
                        Chunk& operator =(Chunk const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the chunk to move into this
                         * @return  the reference of himself
                         */
                        Chunk& operator =(Chunk && c) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the chunk into a string
                         * @return the converted chunk
                         */
                        Utility::String toString() const;
            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, Chunk const& o);

        }
    }

    #include "NRE_Chunk.tpp"
