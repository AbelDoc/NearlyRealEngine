
    /**
     * @file NRE_VAO.hpp
     * @brief Declaration of Engine's GL's Object : VAO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Core.hpp>

     #include "../../VBO/NRE_VBO.hpp"

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
             * @class VAO
             * @brief Manage the binding of vbo with the GPU
             */
            class VAO : public Core::Identifiable<VAO>,
                        public Core::Stringable<VAO>,
                        public Core::Uncopyable<VAO>,
                        public Core::Bindable<VAO> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VAO() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the vao to move
                         */
                        VAO(VAO && o) = default;

                    //## Deconstructor ##//
                        /**
                         * VAO Deconstructor
                         */
                        ~VAO() = default;

                    //## Methods ##//
                        /**
                         * Bind the object
                         */
                        void bind() const;
                        /**
                         * Unbind the object
                         */
                        void unbind() const;
                        /**
                         * Create the object's id
                         */
                        void createIdImpl();
                        /**
                         * Delete the object's id
                         */
                        void deleteIdImpl();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool existImpl() const;
                        /**
                         * Access a vbo with the current vao
                         * @param buffer the vbo to save
                         */
                        void access(const AbstractVBO* buffer) const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of o into this
                         * @param o the vao to move into this
                         * @return  the reference of himself
                         */
                        VAO& operator =(VAO && o) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the vao into a string
                         * @return the converted vao
                         */
                        Core::String toString() const;

            };
        }
    }

    #include "NRE_VAO.tpp"
