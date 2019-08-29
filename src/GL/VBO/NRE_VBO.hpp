
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

                    //## Getter ##//
                        /**
                         * @return the number of vertex
                         */
                        std::size_t getDataCount() const override;

                    //## Methods ##//
                        /**
                         * Add a layout object in the VBO
                         * @param args layout object's construction arguments
                         */
                        template <class ... Args>
                        void addData(Args && ... args);
                        /**
                         * Store calls for VAO managing
                         */
                        virtual void access() const override;
                        /**
                         * Reserve the attribute data's storage
                         * @param capacity the capacity to get
                         */
                        void reserve(std::size_t capacity) override;

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
