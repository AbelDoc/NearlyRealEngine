    
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
            inline CullableMesh<T, K, Data>::CullableMesh(GL::AbstractVBO* buffer, const K* bound) : TypedMesh<T>(buffer), boundObject(bound) {
            }
            
            template <class T, class K, class Data>
            inline CullableMesh<T, K, Data>::CullableMesh(const T* o, const K* bound) : TypedMesh<T>(o), boundObject(bound) {
            }
            
            template <class T, class K, class Data>
            inline void CullableMesh<T, K, Data>::setBoundObject(const K* bound) {
                boundObject = bound;
            }
            
            template <class T, class K, class Data>
            inline bool CullableMesh<T, K, Data>::canBeDrawn() const {
                return Mesh::canBeDrawn() && inBound();
            }
            
        }
    }