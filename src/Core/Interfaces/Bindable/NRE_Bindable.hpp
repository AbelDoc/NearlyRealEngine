    
    /**
     * @file NRE_Bindable.hpp
     * @brief Declaration of Engine's Core's Interface : Bindable
     * @author Louis ABEL
     * @date 21/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <Core/Interfaces/NRE_StaticInterface.hpp>
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Core
         * @brief Core's API
         */
        namespace Core {
            
            /**
             * @class Bindable
             * @brief Describe a bindable object
             */
            template <class T>
            class Bindable : public StaticInterface<Bindable<T>> {
                public:    // Methods
                    /**
                     * Bind the object
                     */
                    void bind() const {
                        this->impl().bind();
                    }
                    /**
                     * Unbind the object
                     */
                    void unbind() const {
                        this->impl().unbind();
                    }
            };
        }
    }
