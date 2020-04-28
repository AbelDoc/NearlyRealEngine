    
    /**
     * @file NRE_Mesh.tpp
     * @brief Implementation of Engine's Model's Object : Mesh
     * @author Louis ABEL
     * @date 23/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            template <class T>
            inline TypedMesh<T>::TypedMesh(T const& o) : Mesh(MeshFactory<T>::create(o)) {
            }
            
            template <class T>
            template <class ... Args>
            inline TypedMesh<T>::TypedMesh(Args && ... args) : Mesh(MeshFactory<T>::create(T(std::forward<Args>(args)...))) {
            }
            
        }
    }