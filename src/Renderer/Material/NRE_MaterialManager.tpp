
    /**
     * @file NRE_MaterialManager.hpp
     * @brief Implementation of Engine's Renderer's Object : MaterialManager
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline MaterialManager::MaterialManager() : materials(20), currentLayer(0) {
            }
            
            inline std::size_t MaterialManager::getNbMaterials() const {
                return textures.getSize();
            }

            inline GL::Texture2DArray const& MaterialManager::getAlbedos() const {
                return materials.getAlbedos();
            }
    
            inline GL::Texture2DArray const& MaterialManager::getNormals() const {
                return materials.getNormals();
            }
    
            inline GL::Texture2DArray const& MaterialManager::getRoughness() const {
                return materials.getRoughness();
            }
    
            inline GL::Texture2DArray const& MaterialManager::getMetallics() const {
                return materials.getMetallics();
            }
    
            inline typename MaterialManager::Iterator MaterialManager::begin() {
                return textures.begin();
            }
    
            inline typename MaterialManager::ConstIterator MaterialManager::begin() const {
                return textures.begin();
            }
    
            inline typename MaterialManager::ConstIterator MaterialManager::cbegin() const {
                return textures.cbegin();
            }
    
            inline typename MaterialManager::Iterator MaterialManager::end() {
                return textures.end();
            }
    
            inline typename MaterialManager::ConstIterator MaterialManager::end() const {
                return textures.end();
            }
    
            inline typename MaterialManager::ConstIterator MaterialManager::cend() const {
                return textures.cend();
            }
            
            inline void MaterialManager::add(GL::Material && m) {
                assert(textures.getCapacity() != static_cast <std::size_t> (currentLayer));
                materials.sendMaterial(m, currentLayer++);
                m.deallocate();
                textures.emplaceBack(std::move(m));
            }
    
        }
    }
