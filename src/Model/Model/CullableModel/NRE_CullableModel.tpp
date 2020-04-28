    
    /**
     * @file NRE_CullableModel.tpp
     * @brief Implementation of Engine's Model's Object : CullableModel
     * @author Louis ABEL
     * @date 28/04/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            template <class T, class K, class Data>
            inline CullableModel<T, K, Data>::CullableModel(const T* o, const K* bound) : TypedModel<T>(o), boundObject(bound) {
            }
            
            
            template <class T, class K, class Data>
            inline void CullableModel<T, K, Data>::setBoundObject(const K* bound) {
                boundObject = bound;
            }
            
            template <class T, class K, class Data>
            inline bool CullableModel<T, K, Data>::canBeDrawn() const {
                return inBound() && Model::canBeDrawn();
            }
            
        }
    }