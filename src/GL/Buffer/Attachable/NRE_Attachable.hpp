
    /**
     * @file NRE_Attachable.hpp
     * @brief Declaration of Engine's GL's Object : Attachable
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Core.hpp>

     #include "../../../Header/NRE_GL.hpp"
     #include "../../../Header/NRE_Utility.hpp"

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
            class Attachable : public Core::Allocable<Attachable>,
                               public Core::Bindable<Attachable>,
                               public Core::Uncopyable<Attachable>,
                               public Core::Stringable<Attachable> {
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Attachable() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move a into this
                         * @param a the attachable object to move
                         */
                        Attachable(Attachable && a) = default;

                    //## Deconstructor ##//
                        /**
                         * Attachable Deconstructor
                         */
                        virtual ~Attachable() = default;

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
                         * Allocate the object
                         */
                        void allocateImpl();
                        /**
                         * Deallocate the object
                         */
                        void deallocateImpl();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of a into this
                         * @param a the attachable object to move into this
                         * @return  the reference of himself
                         */
                        Attachable& operator =(Attachable && a) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the attachable into a string
                         * @return the converted attachable
                         */
                        virtual Core::String toString() const = 0;
    
                    using Allocable<Attachable>::allocate;
            };
        }
    }

    #include "NRE_Attachable.tpp"
