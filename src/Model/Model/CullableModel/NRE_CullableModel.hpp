    
    /**
     * @file NRE_CullableModel.hpp
     * @brief Declaration of Engine's Model's Object : CullableModel
     * @author Louis ABEL
     * @date 28/04/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Model/NRE_Model.hpp"
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Model
         * @brief Engine's Model module
         */
        namespace Model {
        
            template <class T, class K = Math::Frustum, class Data = void*>
            class CullableModel : public TypedModel<T> {
                private :   // Fields
                    const K* boundObject;
                    Data cacheData;
    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        CullableModel() = delete;
                        /**
                         * Construct the model with the target object
                         * @param o     the object to create the model
                         * @param bound the object to test if the model is visible
                         */
                        CullableModel(const T* o, const K* bound = nullptr);
        
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the cullable model to move
                         */
                        CullableModel(CullableModel && m) = default;
        
                    //## Deconstructor ##//
                        /**
                         * CullableModel Deconstructor
                         */
                        ~CullableModel() = default;
            
                    //## Setter ##//
                        /**
                         * Set the cullable model's bound object
                         * @param bound the new bound object
                         */
                        void setBoundObject(const K* bound);
        
                    //## Methods ##//
                        /**
                         * @return if target is in bound
                         */
                        bool inBound() const;
                        /**
                         * @return if the model can be drawn
                         */
                        bool canBeDrawn() const override;
        
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m cullable model to move into this
                         * @return  the reference of himself
                         */
                        CullableModel& operator =(CullableModel && m) = default;
            };
        }
    }

    #include "NRE_CullableModel.tpp"