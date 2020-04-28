    
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
            inline CullableMesh<T, K, Data>::CullableMesh(T& o, const K* bound) : TypedMesh<T>(o), target(o), boundObject(bound) {
            }
            
            template <class T, class K, class Data>
            inline CullableMesh<T, K, Data>::CullableMesh(CullableMesh && m) : TypedMesh<T>(std::move(static_cast <TypedMesh<T> &&> (m))), target(m.target), boundObject(m.boundObject), cacheData(std::move(m.cacheData)) {
            }
            
            template <class T, class K, class Data>
            inline void CullableMesh<T, K, Data>::setBoundObject(const K* bound) {
                boundObject = bound;
            }
            
            template <class T, class K, class Data>
            inline bool CullableMesh<T, K, Data>::canBeDrawn() const {
                return Mesh::canBeDrawn() && inBound();
            }
    
            template <class T, class K, class Data>
            inline CullableMesh<T, K, Data>& CullableMesh<T, K, Data>::operator=(CullableMesh && m) {
                if (this != &m) {
                    TypedMesh<T>::operator=(std::move(m));
                    target = m.target;
                    boundObject = m.boundObject;
                    cacheData = std::move(m.cacheData);
                }
                return *this;
            }
            
        }
    }