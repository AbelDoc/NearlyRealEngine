    
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
    
            inline bool Model::draw(GL::DrawMode mode) const {
                bool drawn = true;
                for (auto& m : meshes) {
                    drawn = drawn && m->draw(mode);
                }
                return drawn;
            }
            
        }
    }