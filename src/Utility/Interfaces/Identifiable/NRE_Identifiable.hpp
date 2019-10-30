    
    /**
     * @file NRE_Identifiable.hpp
     * @brief Declaration of Engine's Utility's Interface : Identifiable
     * @author Louis ABEL
     * @date 22/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <cassert>
    #include <Utility/Interfaces/NRE_StaticInterface.hpp>
    #include <Utility/Id/NRE_Id.hpp>
    
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
             * @class Identifiable
             * @brief Describe an identifiable object
             */
            template <class T>
            class Identifiable : public StaticInterface<T, Identifiable> {
                protected :    //Fields
                    Id id;      /**< The object's id */
    
                public :       // Methods
                    //## Constructor ##//
                        /**
                         * Construct the object
                         * @param generate tell if the object create the id on load
                         */
                        Identifiable(bool generate = true) : id(0) {
                            if (generate) {
                                createId();
                            }
                        }
        
                    //## Move Constructor ##//
                        /**
                         * Move i into this
                         * @param i the identifiable to move
                         */
                        Identifiable(Identifiable && i) : id(i.id) {
                            i.id = 0;
                        }
    
                    //## Deconstructor ##//
                        /**
                         * Identifiable Deconstructor
                         */
                        ~Identifiable() {
                            deleteId();
                        }
    
                    //## Getter ##//
                        /**
                         * @return the object's id
                         */
                        Id getId() const {
                            return id;
                        }
                        
                    //## Methods ##//
                        /**
                         * Create the object's id
                         */
                        void createId() {
                            if (exist()) {
                                deleteId();
                                assert(false);
                            }
                            this->impl().createIdImpl();
                        }
                        /**
                         * Delete the object's id
                         */
                        void deleteId()  {
                            if (id != 0) {
                                this->impl().deleteIdImpl();
                                id = 0;
                            }
                        }
                        /**
                         * Delete and re-create the id
                         */
                        void regenerateId() {
                            deleteId();
                            createId();
                        }
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const {
                            return this->impl().existImpl();
                        }
    
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of i into this
                         * @param i the identifiable to move
                         * @return  the reference of himself
                         */
                        Identifiable& operator =(Identifiable && i) {
                            if (this != &i) {
                                id = i.id;
                                i.id = 0;
                            }
                            return *this;
                        }
            };
        }
    }
