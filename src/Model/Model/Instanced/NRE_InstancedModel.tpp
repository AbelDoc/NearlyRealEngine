    
    /**
     * @file NRE_InstancedModel.tpp
     * @brief Implementation of Engine's Model's Object : InstancedModel
     * @author Louis ABEL
     * @date 28/11/2018
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
    
            template <class InstanceLayout>
            inline InstancedModel<InstanceLayout>::InstancedModel(std::size_t nbInstance, GL::StreamUsage stream) : models(stream) {
                models.allocate(nbInstance);
                models.resize(nbInstance);
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::Iterator InstancedModel<InstanceLayout>::begin() {
                return models.begin();
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::ConstIterator InstancedModel<InstanceLayout>::begin() const {
                return models.begin();
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::ConstIterator InstancedModel<InstanceLayout>::cbegin() const {
                return models.cbegin();
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::Iterator InstancedModel<InstanceLayout>::end() {
                return models.end();
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::ConstIterator InstancedModel<InstanceLayout>::end() const {
                return models.end();
            }
    
            template <class InstanceLayout>
            inline typename InstancedModel<InstanceLayout>::ConstIterator InstancedModel<InstanceLayout>::cend() const {
                return models.cend();
            }
    
            template <class InstanceLayout>
            inline void InstancedModel<InstanceLayout>::addMesh(std::unique_ptr<Mesh> && mesh) {
                Model::addMesh(std::move(mesh));
                meshes.getLast()->access(&models);
            }
    
            template <class InstanceLayout>
            inline void InstancedModel<InstanceLayout>::addMesh(Mesh* mesh) {
                Model::addMesh(mesh);
                meshes.getLast()->access(&models);
            }
    
            template <class InstanceLayout>
            inline void InstancedModel<InstanceLayout>::draw(GL::DrawMode mode) const {
                for (auto& m : meshes) {
                    m->drawInstanced(static_cast <int> (models.getCount()), mode);
                }
            }
    
            template <class InstanceLayout>
            inline void InstancedModel<InstanceLayout>::update() {
                models.update();
            }
    
            template <class InstanceLayout>
            inline InstanceLayout& InstancedModel<InstanceLayout>::operator [](std::size_t index) {
                return models[index];
            }
    
            template <class InstanceLayout>
            inline InstanceLayout const& InstancedModel<InstanceLayout>::operator [](std::size_t index) const {
                return models[index];
            }
            
        }
    }
