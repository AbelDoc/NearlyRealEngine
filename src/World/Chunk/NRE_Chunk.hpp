    
    /**
     * @file NRE_Chunk.hpp
     * @brief Declaration of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "../Voxel/NRE_VoxelsContainer.hpp"

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
            class Chunk : public Utility::Stringable<Chunk> {
                public :    // Static
                    static constexpr std::size_t SIZE_X     = 16;
                    static constexpr std::size_t SIZE_Y     = 16;
                    static constexpr std::size_t SIZE_Z     = 16;

                public :    // Iterator
                    typedef VoxelsContainer<SIZE_X, SIZE_Y, SIZE_Z> VoxelsContainer;

                private :   // Fields
                    VoxelsContainer terrain;            /**< The chunk's terrain voxels */
                    VoxelsContainer water;              /**< The chunk's waters voxels */
                    Math::Point3D<int> position;        /**< The chunk's position */

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
                         * @return the terrain's voxels container
                         */
                        VoxelsContainer& getTerrainVoxels();
                        /**
                         * @return the terrain's voxels container
                         */
                        VoxelsContainer const& getTerrainVoxels() const;
                        /**
                         * @return the water's voxels container
                         */
                        VoxelsContainer& getWaterVoxels();
                        /**
                         * @return the water's voxels container
                         */
                        VoxelsContainer const& getWaterVoxels() const;

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

        }
    }

    #include "NRE_Chunk.tpp"
