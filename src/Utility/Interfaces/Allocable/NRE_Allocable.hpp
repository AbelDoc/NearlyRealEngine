    
    /**
     * @file NRE_Bindable.hpp
     * @brief Declaration of Engine's Utility's Interface : Allocable
     * @author Louis ABEL
     * @date 21/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <cassert>
    #include <Utility/Interfaces/NRE_StaticInterface.hpp>

    #include <iostream>
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Utility
         * @brief Utility's API
         */
        namespace Utility {
            
            /**
             * @class Allocable
             * @brief Describe an allocable object which manage some resources
             */
            template <class T>
            class Allocable : public StaticInterface<Allocable<T>> {
                private :   // Field
                    bool allocated; /**< The objet's allocation state */
                    
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Allocable() : allocated(false) {
                        }
    
                    //## Copy Constructor ##//
                        /**
                         * Copy a into this
                         * @param a the allocable to copy
                         */
                        Allocable(Allocable const& a) = default;
    
                    //## Move Constructor ##//
                        /**
                         * Move a into this
                         * @param a the allocable to move
                         */
                        Allocable(Allocable && a) : allocated(a.allocated) {
                            a.allocated = false;
                        }
    
                    //## Deconstructor ##//
                        ~Allocable() {
                            if (isAllocated()) {
                                deallocate();
                            }
                        }
    
                    //## Methods ##//
                        /**
                         * @return the object's allocation state
                         */
                        bool isAllocated() const {
                            return allocated;
                        }
                        /**
                         * Allocate the object's resources
                         */
                        void allocate() {
                            if (isAllocated()) {
                                deallocate();
                                assert(false);
                            }
                            this->impl().allocateImpl();
                            allocated = true;
                        }
                        /**
                         * Deallocate the object's resources
                         */
                        void deallocate() {
                            this->impl().deallocateImpl();
                            allocated = false;
                        }
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of a into this
                         * @param a the allocable to copy
                         * @return  the reference of himself
                         */
                        Allocable& operator =(Allocable const& a) = default;
                        /**
                         * Move assignment of a into this
                         * @param a the allocable to move into this
                         * @return  the reference of himself
                         */
                        Allocable& operator =(Allocable && a) {
                            if (this != &a) {
                                allocated = a.allocated;
                                a.allocated = false;
                            }
                            return *this;
                        }
            };
        }
    }
