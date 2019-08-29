
    /**
     * @file NRE_Attachable.hpp
     * @brief Declaration of Engine's GL's Object : Attachable
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Utility.hpp>

     #include "../../../Header/NRE_GL.hpp"

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
             * @pure Attachable
             * @brief Describe an attachable object
             */
            class Attachable {
                protected :   // Fields
                    Id id;              /**< The attachable id */

                private :    // Fields
                    bool allocated;     /**< Tell if the attachable is allocated */

                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Attachable();

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param a the attachable object to copy
                         */
                        Attachable(Attachable const& a) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move a into this
                         * @param a the attachable object to move
                         */
                        Attachable(Attachable && a);

                    //## Deconstructor ##//
                        /**
                         * Attachable Deconstructor
                         */
                        virtual ~Attachable();

                    //## Getter ##//
                        /**
                         * @return if the attachable is allocated
                         */
                        bool isAllocated() const;
                        /**
                         * @return the attachable id
                         */
                        Id getId() const;

                    //## Methods ##//
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         */
                        virtual void attach(AttachPoint target) const = 0;
                        /**
                         * Bind the object
                         */
                        virtual void bind() const = 0;
                        /**
                         * Unbind the object
                         */
                        virtual void unbind() const = 0;
                        /**
                         * Create the object's id
                         */
                        virtual void createId() = 0;
                        /**
                         * Delete the object's id
                         */
                        virtual void deleteId() = 0;
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        virtual bool exist() const = 0;
                        /**
                         * Allocate the object
                         */
                        virtual void allocate();
                        /**
                         * Deallocate the object
                         */
                        void deallocate();

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param a the attachable object to copy
                         * @return  the reference of himself
                         */
                        Attachable& operator =(Attachable const& a) = delete;
                        /**
                         * Move assignment of a into this
                         * @param a the attachable object to move into this
                         * @return  the reference of himself
                         */
                        Attachable& operator =(Attachable && a);

                    //## Stream Operator ##//
                        /**
                         * Convert the attachable into a string
                         * @return the converted attachable
                         */
                        virtual Utility::String toString() const = 0;

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, Attachable const& o);
        }
    }

    #include "NRE_Attachable.tpp"
