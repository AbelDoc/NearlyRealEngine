
    /**
     * @file NRE_VBO.hpp
     * @brief Declaration of Engine's GL's Object : VBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "NRE_AbstractVBO.hpp"

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
             * @class VBO
             * @brief Manage a layout of data
             */
            template <class Layout>
            class VBO : public AbstractVBO {
                public :    // Iterator
                    /**< Shortcut to hide Iterator implementation */
                    typedef typename Utility::Vector<Layout>::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef typename Utility::Vector<Layout>::ConstIterator    ConstIterator;
                    
                private:    //Fields
                    Utility::Vector<Layout> datas;  /**< The vertex's data */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VBO() = delete;
                        /**
                         * Construct a VBO from the buffer's streaming usage
                         * @param stream the buffer's streaming usage
                         */
                        VBO(StreamUsage stream);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the vbo to move
                         */
                        VBO(VBO && b);

                    //## Deconstructor ##//
                        /**
                         * VBO Deconstructor
                         */
                        virtual ~VBO() = default;
    
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

                    //## Getter ##//
                        /**
                         * @return the number of vertex which are not in GPU memory
                         */
                        std::size_t getDataCount() const override;
                        /**
                         * Query a buffer's data
                         * @param  index the data index
                         * @return       the corresponding data
                         */
                        Layout& getData(std::size_t index);

                    //## Methods ##//
                        /**
                         * Add a layout object in the VBO
                         * @param args layout object's construction arguments
                         * @return the data index
                         */
                        template <class ... Args>
                        std::size_t addData(Args && ... args);
                        /**
                         * Store calls for VAO managing
                         */
                        virtual void access() const override;
                        /**
                         * Reserve the attribute data's storage
                         * @param capacity the capacity to get
                         */
                        void reserve(std::size_t capacity) override;
                        /**
                         * Resize the attribute data's storage
                         * @param capacity the capacity to get
                         */
                        void resize(std::size_t capacity) override;
    
                    //## Access Operator ##//
                        /**
                         * Return a reference on a data's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Layout& operator [](std::size_t index);
                        /**
                         * Return a const reference on a data's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        Layout const& operator [](std::size_t index) const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the vbo to move into this
                         * @return  the reference of himself
                         */
                        VBO& operator =(VBO && b);

                    //## Stream Operator ##//
                        /**
                         * Convert the vbo into a string
                         * @return the converted vbo
                         */
                        Utility::String toString() const override;

                private:   // Methods
                    /**
                     * Clear the attribute data's storage
                     */
                    void clear() override;
                    /**
                     * @return the layout type's size in bytes
                     */
                    std::size_t getLayoutSize() const override;
                    /**
                     * @return the pointer to data
                     */
                    const void* getDataPointer() const override;

            };
        }
    }

    #include "NRE_VBO.tpp"
