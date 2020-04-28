    
    /**
     * @file NRE_TypedModel.tpp
     * @brief Implementation of Engine's Model's Object : TypedModel
     * @author Louis ABEL
     * @date 29/11/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
    
            template <class T>
            inline TypedModel<T>::TypedModel(T const& o) : Model(ModelFactory<T>::create(o)) {
            }
    
            template <class T>
            template <class ... Args>
            inline TypedModel<T>::TypedModel(Args && ... args) : Model(ModelFactory<T>::create(T(std::forward<Args>(args)...))) {
            }
    
        }
    }