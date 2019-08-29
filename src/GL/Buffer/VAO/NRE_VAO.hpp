
    /**
     * @file NRE_VAO.hpp
     * @brief Declaration of Engine's GL's Object : VAO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Utility.hpp>

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
            class VAO {
                protected :   // Fields
                    Id id;              /**< The frame buffer id */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VAO();

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param o the vao to copy
                         */
                        VAO(VAO const& o) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move o into this
                         * @param o the vao to move
                         */
                        VAO(VAO && o);

                    //## Deconstructor ##//
                        /**
                         * VAO Deconstructor
                         */
                        ~VAO();

                    //## Getter ##//
                        /**
                         * @return the vao id
                         */
                        Id getId() const;

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
                        void createId();
                        /**
                         * Delete the object's id
                         */
                        void deleteId();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const;
                        /**
                         * Access a vbo with the current vao
                         * @param buffer the vbo to save
                         */
                        void access(const AbstractVBO* buffer) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param o the vao to copy
                         * @return  the reference of himself
                         */
                        VAO& operator =(VAO const& o) = delete;
                        /**
                         * Move assignment of o into this
                         * @param o the vao to move into this
                         * @return  the reference of himself
                         */
                        VAO& operator =(VAO && o);

                    //## Stream Operator ##//
                        /**
                         * Convert the vao into a string
                         * @return the converted vao
                         */
                        Utility::String toString() const;

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, VAO const& o);
        }
    }

    #include "NRE_VAO.tpp"
