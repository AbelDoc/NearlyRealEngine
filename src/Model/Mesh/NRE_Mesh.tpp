    
    /**
     * @file NRE_Mesh.tpp
     * @brief Implementation of Engine's Model's Object : Mesh
     * @author Louis ABEL
     * @date 23/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
        
            inline Mesh::Mesh(GL::AbstractVBO* buffer) : vbo(buffer) {
                vbo->allocateAndFill();
                vao.access(getBuffer());
            }
            
            inline GL::AbstractVBO* Mesh::getBuffer() {
                return vbo.get();
            }
            
            inline void Mesh::bind() const {
                vao.bind();
            }
            
            inline void Mesh::unbind() const {
                vao.unbind();
            }
            
            inline bool Mesh::draw(GL::DrawMode mode) const {
                if (vbo->getCount() > 0) {
                    bind();
                        vbo->draw(mode);
                    unbind();
                    return true;
                }
                return false;
            }
            
            inline Utility::String Mesh::toString() const {
                Utility::String res;
                res << "Buffer : " << vbo.get() << '\n';
                res << "VAO : " << vao;
                return res;
            }
        
        }
    }