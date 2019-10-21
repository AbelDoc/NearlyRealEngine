    
    /**
     * @file NRE_Bindable.hpp
     * @brief Declaration of Engine's Utility's Interface : Bindable
     * @author Louis ABEL
     * @date 21/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <Utility/Interfaces/NRE_StaticInterface.hpp>
    
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
             * @class Bindable
             * @brief Describe a bindable object
             */
            template <class T>
            class Bindable : public StaticInterface<T, Bindable> {
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
