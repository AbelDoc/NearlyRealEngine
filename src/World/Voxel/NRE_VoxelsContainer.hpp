    
    /**
     * @file NRE_Chunk.hpp
     * @brief Declaration of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Utility.hpp>
    
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
             * @class VoxelsContainer
             * @brief Manage a collection of voxels
             */
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            class VoxelsContainer : public Utility::Stringable<VoxelsContainer<SizeX, SizeY, SizeZ>> {
                public :    // Static
                    static constexpr std::size_t SIZE_X     = SizeX;
                    static constexpr std::size_t SIZE_Y     = SizeY;
                    static constexpr std::size_t SIZE_Z     = SizeZ;
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
                    typedef Utility::Array<float, VOXELS_VOLUME> InternalContainer;
                    typedef Utility::Array<const VoxelsContainer*, NEIGHBOR_SIDE_NUM> NeighborsContainer;
                    /**< Shortcut to hide Iterator implementation */
                    typedef typename InternalContainer::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef typename InternalContainer::ConstIterator    ConstIterator;
                    
                private :   // Fields
                    InternalContainer voxels;        /**< The voxels collection */
                    NeighborsContainer neighbors;    /**< The collection's neighbors */
                
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the container
                         */
                        VoxelsContainer() = default;
        
                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the container to copy
                         */
                        VoxelsContainer(VoxelsContainer const& c) = default;
        
                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the container to move
                         */
                        VoxelsContainer(VoxelsContainer && c) = default;
    
                    //## Getter ##//
                        /**
                         * Query a specific voxel
                         * @param index the voxel's index
                         * @return the corresponding voxel
                         */
                        float getVoxel(std::size_t index) const;
                        /**
                         * Query a specific voxel
                         * @param x the voxel's x coordinate
                         * @param y the voxel's y coordinate
                         * @param z the voxel's z coordinate
                         * @return the corresponding voxel
                         */
                        float getVoxel(std::size_t x, std::size_t y, std::size_t z) const;
                        /**
                         * Query a specific voxel
                         * @param p the voxel's coordinates
                         * @return the corresponding voxel
                         */
                        float getVoxel(Math::Point3D<std::size_t> const& p) const;
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
                         * Set a voxel's value
                         * @param index the voxel's index
                         * @param v     the voxel's value
                         */
                        void setVoxel(std::size_t index, float v);
                        /**
                         * Set a voxel's value
                         * @param x the voxel's x coordinate
                         * @param y the voxel's y coordinate
                         * @param z the voxel's z coordinate
                         * @param v the voxel's value
                         */
                        void setVoxel(std::size_t x, std::size_t y, std::size_t z, float v);
                        /**
                         * Set a voxel's value
                         * @param p the voxel's coordinates
                         * @param v the voxel's value
                         */
                        void setVoxel(Math::Point3D<std::size_t> const& p, float v);
                        /**
                         * Set a neighbor
                         * @param n     the new neighbor
                         * @param index the neighbor index
                         */
                        void setNeighbor(VoxelsContainer const& n, std::size_t index);
    
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
                         * Return a reference on a voxel
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        float& operator [](std::size_t index);
                        /**
                         * Return a const reference on a voxel
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        float const& operator [](std::size_t index) const;
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the container to copy
                         * @return  the reference of himself
                         */
                        VoxelsContainer& operator =(VoxelsContainer const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the container to move into this
                         * @return  the reference of himself
                         */
                        VoxelsContainer& operator =(VoxelsContainer && c) = default;
        
                    //## Stream Operator ##//
                        /**
                         * Convert the chunk into a string
                         * @return the converted chunk
                         */
                        Utility::String toString() const;
            };
        }
    }
    
    #include "NRE_VoxelsContainer.tpp"