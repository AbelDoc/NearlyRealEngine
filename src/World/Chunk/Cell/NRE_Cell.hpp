/**
     * @file NRE_Cell.hpp
     * @brief Declaration of Engine's World's Object : Cell
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

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

            typedef std::uint8_t CellCorners;

            /**
             * @class Cell
             * @brief Represent a cell used to create surface from marching cubes algorithms
             */
            class Cell {
                private :   // Fields
                    CellCorners corners;    /**< Represent the cell corners */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct a cell with given corners
                         * @param cs the cell corners, empty by default
                         */
                        Cell(CellCorners cs = 0b00000000);

                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the cell to copy
                         */
                         Cell(Cell const& c) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the cell to move
                         */
                        Cell(Cell && c) = default;

                    //## Getter ##//
                        /**
                         * @return the cell's weight
                         */
                        CellCorners getWeight() const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the cell to copy
                         * @return  the reference of himself
                         */
                        Cell& operator =(Cell const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the cell to move into this
                         * @return  the reference of himself
                         */
                        Cell& operator =(Cell && c) = default;

                    //## Conversion operator ##//
                        /**
                         * @return the cell's weight
                         */
                        operator CellCorners() const;

                    //## Stream Operator ##//
                        /**
                         * Convert the cell into a string
                         * @return the converted cell
                         */
                        Utility::String toString() const;

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, Cell const& o);

        }
    }

    #include "NRE_Cell.tpp"
