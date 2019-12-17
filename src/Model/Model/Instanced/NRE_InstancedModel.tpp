    
    /**
     * @file NRE_InstancedModel.tpp
     * @brief Implementation of Engine's Model's Object : InstancedModel
     * @author Louis ABEL
     * @date 28/11/2018
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            Utility::Vector<Math::Matrix4x4<float>>& InstancedModel::getMatrixes() {
                return matrixes;
            }
            
            void InstancedModel::setModels(std::unique_ptr<GL::VBO<GL::MatrixInstance>>& matrix) {
                models = std::move(matrix);
                for (auto& m : meshes) {
                    m->access(models.get());
                }
                matrixes.clear();
                matrixes.resize(models->getCount());
            }
            
            void InstancedModel::updateModels(const void* data, std::size_t size, GLintptr offset) {
                models->update(data, size, offset);
            }
            
            void InstancedModel::orphanModels() {
                models->orphan();
            }
            
            bool InstancedModel::draw(GL::DrawMode mode) const {
                bool drawn = true;
                for (auto& m : meshes) {
                    drawn = drawn && m->drawInstanced(static_cast <int> (matrixes.getSize()), mode);
                }
                return drawn;
            }
            
            void InstancedModel::update() {
                models->update(matrixes[0].value(), matrixes.getSize());
            }
            
        }
    }
