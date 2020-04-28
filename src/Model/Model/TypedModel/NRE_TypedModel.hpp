    
    /**
     * @file NRE_TypedModel.hpp
     * @brief Declaration of Engine's Model's Object : TypedModel
     * @author Louis ABEL
     * @date 27/04/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../NRE_Model.hpp"
    
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
    
            template<class> class ModelFactory;
        
            /**
             * @class TypedModel
             * @brief Manage the creation of model from a given object, simplifying the process
             */
            template <class T>
            class TypedModel : public Model {
                private : // Fields
                    const T* target;      /**< The typed object */
    
                public :    // Methods
                    //## Constructor ##//
                    /**
                     * No default constructor
                     */
                    TypedModel() = delete;
                    /**
                     * Construct a model from the object to render
                     * @param o the object to construct the model
                     */
                    TypedModel(const T* o);
                    /**
                     * Construct a model from the object to render
                     * @param args the parameters to construct the model objets
                     */
                    template <class ... Args>
                    TypedModel(Args && ... args);
    
                //## Move Constructor ##//
                    /**
                     * Move m into this
                     * @param m the typed model to move
                     */
                    TypedModel(TypedModel && m) = default;
    
                //## Deconstructor ##//
                    /**
                     * TypedModel Deconstructor
                     */
                    ~TypedModel() = default;
    
                //## Getter ##//
                    /**
                     * @return the model's typed object
                     */
                    const T* getTarget() const;
    
                //## Setter ##//
                    /**
                     * Set the model's typed object
                     * @param t the new object
                     */
                    void setTarget(const T* t);
        
                //## Assignment Operator ##//
                    /**
                     * Move assignment of m into this
                     * @param m the typed model to move into this
                     * @return  the reference of himself
                     */
                    TypedModel& operator =(TypedModel && b) = default;
            };
        }
    }

    #include "NRE_TypedModel.tpp"