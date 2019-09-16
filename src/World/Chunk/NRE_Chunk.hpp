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
             * @brief Manage a collection of cells
             */
            class Chunk {
                private :   // Fields
                    Utility::Vector<Cell> cells;     /**< The chunk's cells */
                    Math::Point3D<int> position;     /**< The chunk's position */
                    float resolution;                /**< The chunk's resolution */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        Chunk() = delete;
                        /**
                         * Construct the chunk from its position
                         * @param pos the chunk's position
                         */
                        Chunk(Math::Point3D<int> const& pos);

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
                         * @return the chunk's volume
                         */
                        std::size_t getVolume() const;
                        /**
                         * @return the chunk's voxels cloud volume
                         */
                        std::size_t getVoxelsVolume() const;
                        /**
                         * @return the chunk's voxels layer size
                         */
                        std::size_t getVoxelsLayerSize() const;
                        /**
                         * @return the chunk's voxels layer width
                         */
                        std::size_t getVoxelsLayerWidth() const;
                        /**
                         * @return the chunk's resolution
                         */
                        float getResolution() const;

                    //## Methods ##//
                        /**
                         * Change the internal container resolution
                         * @param res the new resolution
                         */
                        void changeResolution(float res);
                        /**
                         * Emplace a cell back in the chunk
                         * @param corners the cell corners
                         */
                        void emplaceBack(CellCorners corners);

                    //## Access Operator ##//
                        /**
                         * Return a reference on a chunk's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Cell& operator [](std::size_t index);
                        /**
                         * Return a const reference on a chunk's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                         Cell const& operator [](std::size_t index) const;

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

                public :    // Static
                    static constexpr float SIZE_X = 16;
                    static constexpr float SIZE_Y = 16;
                    static constexpr float SIZE_Z = 16;
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
