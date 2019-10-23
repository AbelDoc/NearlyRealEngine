    
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
            inline Mesh<T>::Mesh(T const& o) : vbo(MeshFactory<T>::create(o)) {
                vbo->allocateAndFill();
                vao.access(getBuffer());
            }
            
            template <class T>
            inline GL::AbstractVBO* Mesh<T>::getBuffer() {
                return vbo.get();
            }
            
            template <class T>
            inline void Mesh<T>::bind() const {
                vao.bind();
            }
            
            template <class T>
            inline void Mesh<T>::unbind() const {
                vao.unbind();
            }
            
            template <class T>
            inline void Mesh<T>::draw(GL::DrawMode mode) const {
                bind();
                    vbo->draw(mode);
                unbind();
            }
            
            template <class T>
            inline Utility::String Mesh<T>::toString() const {
                Utility::String res;
                res << "Buffer : " << *getBuffer() << '\n';
                res << "VAO : " << vao;
                return res;
            }
        
        }
    }