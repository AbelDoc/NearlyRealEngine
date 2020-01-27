
    /**
     * @file NRE_MaterialManager.hpp
     * @brief Implementation of Engine's Renderer's Object : MaterialManager
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline MaterialManager::MaterialManager() : materials(3) {
                textures.emplaceBack("Data/Material/Mat_1/x2048");
                textures.emplaceBack("Data/Material/Mat_2/x2048");
                textures.emplaceBack("Data/Material/Mat_3/x2048");
                
                int i = 0;
                for (GL::Material& m : textures) {
                    materials.sendMaterial(m, i++);
                    m.deallocate();
                }
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
    
            inline GL::Texture2DArray const& MaterialManager::getDisplacements() const {
                return materials.getDisplacements();
            }


        }
    }
