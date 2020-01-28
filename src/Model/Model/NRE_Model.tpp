    
    /**
     * @file Model/NRE_Model.tpp
     * @brief Implementation of Engine's Model's Object : Model
     * @author Louis ABEL
     * @date 08/11/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            inline void Model::reserve(std::size_t capacity) {
                meshes.reserve(capacity);
            }
    
            inline void Model::addMesh(std::unique_ptr<Mesh> && mesh) {
                meshes.pushBack(std::move(mesh));
            }
    
            inline void Model::addMesh(Mesh* mesh) {
                meshes.emplaceBack(mesh);
            }
            
            inline bool Model::canBeDrawn() const {
                bool drawn = false;
                std::size_t i = 0;
                while (!drawn && i < meshes.getSize()) {
                    drawn = drawn || meshes[i++]->canBeDrawn();
                }
                return drawn;
            }
    
            inline void Model::draw(GL::DrawMode mode) const {
                for (auto& m : meshes) {
                    m->draw(mode);
                }
            }
            
        }
    }