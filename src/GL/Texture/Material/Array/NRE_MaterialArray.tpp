
    /**
     * @file NRE_MaterialArray.tpp
     * @brief Implementation of Engine's GL's Object : MaterialArray
     * @author Louis ABEL
     * @date 31/01/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {
    
            inline MaterialArray::MaterialArray(int nbLayers) {
                allocate(nbLayers);
            }
    
            inline Texture2DArray const& MaterialArray::getAlbedos() const {
                return albedos;
            }
    
            inline Texture2DArray const& MaterialArray::getNormals() const {
                return normals;
            }
    
            inline Texture2DArray const& MaterialArray::getRoughness() const {
                return roughness;
            }
    
            inline Texture2DArray const& MaterialArray::getMetallics() const {
                return metallics;
            }
    
            inline int MaterialArray::getNbMaterials() const {
                return nbMaterials;
            }
    
            inline void MaterialArray::allocate(int nbLayers) {
                albedos.allocate(nbLayers, Surface(Math::Vector2D<GLsizei>(MAX_RESOLUTION, MAX_RESOLUTION), GL_RGBA, GL_RGBA));
                normals.allocate(nbLayers, Surface(Math::Vector2D<GLsizei>(MAX_RESOLUTION, MAX_RESOLUTION), GL_RGBA, GL_RGBA));
                roughness.allocate(nbLayers, Surface(Math::Vector2D<GLsizei>(MAX_RESOLUTION, MAX_RESOLUTION), GL_RGBA, GL_RGBA));
                metallics.allocate(nbLayers, Surface(Math::Vector2D<GLsizei>(MAX_RESOLUTION, MAX_RESOLUTION), GL_RGBA, GL_RGBA));
                albedos.bind();
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
                albedos.unbind();
                normals.bind();
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
                normals.unbind();
                roughness.bind();
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
                roughness.unbind();
                metallics.bind();
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
                metallics.unbind();
                nbMaterials = nbLayers;
            }
    
            inline void MaterialArray::sendMaterial(Material& material, int layer) {
                assert(layer < nbMaterials);
                if (material.hasAlbedoMap()) {
                    albedos.sendTexture(*material.getAlbedoMap(), layer);
                }
                if (material.hasNormalMap()) {
                    normals.sendTexture(*material.getNormalMap(), layer);
                }
                if (material.hasRoughnessMap()) {
                    roughness.sendTexture(*material.getRoughnessMap(), layer);
                }
                if (material.hasMetallicMap()) {
                    metallics.sendTexture(*material.getMetallicMap(), layer);
                }
            }

        }
    }
