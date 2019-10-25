    
    /**
     * @file NRE_CullableMesh.tpp
     * @brief Implementation of Engine's Model's Object : CullableMesh
     * @author Louis ABEL
     * @date 25/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            template <class T, class K, class Data>
            CullableMesh<T, K, Data>::CullableMesh(T& o) : Mesh<T>(o), target(o) {
                o.add(this);
                update(nullptr, nullptr);
            }
            
            template <class T, class K, class Data>
            CullableMesh<T, K, Data>::CullableMesh(CullableMesh && m) : Mesh<T>(std::move(m)), target(m.target), cacheData(std::move(m.cacheData)) {
            }
        
            template <class T, class K, class Data>
            bool CullableMesh<T, K, Data>::draw(K const& boundObject, GL::DrawMode mode) const {
                if (inBound(boundObject)) {
                    return Mesh<T>::draw(mode);
                }
                return false;
            }
    
            template <class T, class K, class Data>
            CullableMesh<T, K, Data>& CullableMesh<T, K, Data>::operator=(CullableMesh && m) {
                if (this != &m) {
                    Mesh<T>::operator=(std::move(m));
                    target = m.target;
                    cacheData = std::move(m.cacheData);
                }
                return *this;
            }
            
        }
    }