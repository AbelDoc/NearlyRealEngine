    
    /**
     * @file NRE_VoxelsContainer.hpp
     * @brief Declaration of Engine's World's Object : VoxelsContainer
     * @author Louis ABEL
     * @date 20/07/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Utility.hpp>

    #include "../NRE_Voxel.hpp"
    
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
                    typedef Utility::Array<Voxel, VOXELS_VOLUME> InternalContainer;
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
    
                    //## Deconstructor ##//
                        /**
                         * VoxelsContainer Deconstructor
                         */
                        ~VoxelsContainer() = default;
    
                    //## Getter ##//
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
                        Voxel& operator [](std::size_t index);
                        /**
                         * Return a const reference on a voxel
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Voxel const& operator [](std::size_t index) const;
    
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
                         * Convert the voxels container into a string
                         * @return the converted voxels container
                         */
                        Utility::String toString() const;
            };
        }
    }
    
    #include "NRE_VoxelsContainer.tpp"