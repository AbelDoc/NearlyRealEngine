    
    /**
     * @file NRE_Chunk.hpp
     * @brief Declaration of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../Voxel/NRE_Voxel.hpp"

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
            class Chunk : public Core::Stringable<Chunk> {
                public :    // Static
                    static constexpr std::size_t SIZE_X     = 16;
                    static constexpr std::size_t SIZE_Y     = 16;
                    static constexpr std::size_t SIZE_Z     = 16;
                    static constexpr std::size_t VOLUME     = SIZE_X * SIZE_Y * SIZE_Z;
        
                    static constexpr std::size_t VOXELS_LAYER_WIDTH = SIZE_X + 1;
                    static constexpr std::size_t VOXELS_LAYER_AREA  = VOXELS_LAYER_WIDTH * (SIZE_Z + 1);
                    static constexpr std::size_t VOXELS_VOLUME      = VOXELS_LAYER_AREA  * (SIZE_Y + 1);
        
                    enum NeighborSide {
                        RIGHT,
                        LEFT,
                        TOP,
                        BOTTOM,
                        FRONT,
                        BACK,
            
                        NEIGHBOR_SIDE_NUM
                    };

                public :    // Iterator
                    typedef Core::Array<Voxel, VOXELS_VOLUME> VoxelsContainer;
                    typedef Core::Array<const Chunk*, NEIGHBOR_SIDE_NUM> NeighborsContainer;
                    /**< Shortcut to hide Iterator implementation */
                    typedef typename VoxelsContainer::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef typename VoxelsContainer::ConstIterator    ConstIterator;

                private :   // Fields
                    VoxelsContainer voxels;        /**< The voxels collection */
                    NeighborsContainer neighbors;  /**< The collection's neighbors */
                    Math::Point3D<int> position;   /**< The chunk's position */

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
                        /**
                         * Query a specific voxel
                         * @param index the voxel's index
                         * @return the corresponding voxel
                         */
                        Voxel const& getVoxel(std::size_t index) const;
                        /**
                         * Query a specific voxel
                         * @param x the voxel's x coordinate
                         * @param y the voxel's y coordinate
                         * @param z the voxel's z coordinate
                         * @return the corresponding voxel
                         */
                        Voxel const& getVoxel(std::size_t x, std::size_t y, std::size_t z) const;
                        /**
                         * Query a specific voxel
                         * @param p the voxel's coordinates
                         * @return the corresponding voxel
                         */
                        Voxel const& getVoxel(Math::Point3D<std::size_t> const& p) const;
                        /**
                         * Query a specific voxel
                         * @param index the voxel's index
                         * @return the corresponding voxel
                         */
                        Voxel& getVoxel(std::size_t index);
                        /**
                         * Query a specific voxel
                         * @param x the voxel's x coordinate
                         * @param y the voxel's y coordinate
                         * @param z the voxel's z coordinate
                         * @return the corresponding voxel
                         */
                        Voxel& getVoxel(std::size_t x, std::size_t y, std::size_t z);
                        /**
                         * Query a specific voxel
                         * @param p the voxel's coordinates
                         * @return the corresponding voxel
                         */
                        Voxel& getVoxel(Math::Point3D<std::size_t> const& p);
                        /**
                         * Find a voxel's gradient, which can be used as a normal
                         * @param x the voxel's x coordinate
                         * @param y the voxel's y coordinate
                         * @param z the voxel's z coordinate
                         * @return the corresponding voxel
                         */
                        Math::Vector3D<float> getGradient(std::size_t x, std::size_t y, std::size_t z) const;
                        /**
                         * Find a voxel's gradient, which can be used as a normal
                         * @param p the voxel's coordinates
                         * @return the corresponding voxel
                         */
                        Math::Vector3D<float> getGradient(Math::Point3D<std::size_t> const& p) const;

                    //## Setter ##//
                        /**
                         * Set the chunk's position
                         * @param p the new position
                         */
                        void setPosition(Math::Point3D<int> const& p);
                        /**
                         * Set a neighbor
                         * @param n     the new neighbor
                         * @param index the neighbor index
                         */
                        void setNeighbor(Chunk const& n, std::size_t index);
    
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
                         * Return a reference on a voxel's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Voxel& operator [](std::size_t index);
                        /**
                         * Return a const reference on a voxel's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Voxel const& operator [](std::size_t index) const;

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
                        Core::String toString() const;
            };

        }
    }

    #include "NRE_Chunk.tpp"
