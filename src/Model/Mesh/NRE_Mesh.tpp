    
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
                access(getBuffer());
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
    
            inline void Mesh::access(const GL::AbstractVBO* buf) {
                vao.access(buf);
            }
            
            inline bool Mesh::canBeDrawn() const {
                return vbo->getCount() > 0;
            }
            
            inline void Mesh::draw(GL::DrawMode mode) const {
                bind();
                    vbo->draw(mode);
                unbind();
            }
    
            inline void Mesh::drawInstanced(int instance, GL::DrawMode mode) const {
                bind();
                    vbo->drawInstanced(instance, mode);
                unbind();
            }
            
            inline Utility::String Mesh::toString() const {
                Utility::String res;
                res << "Buffer : " << vbo.get() << '\n';
                res << "VAO : " << vao;
                return res;
            }
        
        }
    }