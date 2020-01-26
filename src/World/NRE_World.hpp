    /**
     * @file NRE_World.hpp
     * @brief Declaration of Engine's World's Object : World
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include "Chunk/NRE_Chunk.hpp"

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
             * @class World
             * @brief Manage a collections of chunks
             */
            class World {
                public :    // Iterator
                    /**< Shortcut to hide Iterator implementation */
                    typedef Chunk*          Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef const Chunk*    ConstIterator;

                public :    // Static
                    static constexpr int H_SIZE_X = 1;
                    static constexpr int H_SIZE_Z = 1;
                    static constexpr int   SIZE_Y = 3;
                    static constexpr std::size_t NB_CHUNKS = ((static_cast <std::size_t> (H_SIZE_X) * 2) + 1) * ((static_cast <std::size_t> (H_SIZE_Z) * 2) + 1) * static_cast <std::size_t> (SIZE_Y);

                private :   // Fields
                    Chunk* chunks;      /**< The world's chunks */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the default world
                         */
                        World();

                    //## Copy constructor ##//
                        /**
                         * Copy forbidden
                         * @param w the world to copy
                         */
                        World(World const& w) = delete;

                    //## Move constructor ##//
                        /**
                         * Move w into this
                         * @param w the world to move
                         */
                        World(World && w);

                    //## Deconstructor ##//
                        /**
                         * World Deconstructor
                         */
                        ~World();

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
                        Chunk& operator [](std::size_t index);
                        /**
                         * Return a const reference on a chunk's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                         Chunk const& operator [](std::size_t index) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param w the world to copy
                         * @return  the reference of himself
                         */
                        World& operator =(World const& w) = delete;
                        /**
                         * Move assignment of w into this
                         * @param w the world to move into this
                         * @return  the reference of himself
                         */
                        World& operator =(World && w);

            };

        }
    }

    #include "NRE_World.tpp"
