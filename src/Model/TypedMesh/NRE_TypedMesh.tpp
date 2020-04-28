    
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
            inline TypedMesh<T>::TypedMesh(GL::AbstractVBO* buffer) : Mesh(buffer) {
            }
            
            template <class T>
            inline TypedMesh<T>::TypedMesh(const T* o) : Mesh(MeshFactory<T>::create(*o)), target(o) {
            }
            
            template <class T>
            template <class ... Args>
            inline TypedMesh<T>::TypedMesh(Args && ... args) : Mesh(MeshFactory<T>::create(T(std::forward<Args>(args)...))), target(nullptr) {
            }
            
            template <class T>
            inline const T* TypedMesh<T>::getTarget() const {
                return target;
            }
            
            template <class T>
            inline void TypedMesh<T>::setTarget(const T* t) {
                target = t;
            }
            
        }
    }