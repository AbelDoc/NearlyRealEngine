
    /**
     * @file NRE_Material.tpp
     * @brief Implementation of Engine's GL's Object : Material
     * @author Louis ABEL
     * @date 07/11/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Material::Material(IO::File const& path) : albedo(path.getPath() + "/Albedo.png"),
                                                       normal(path.getPath() + "/Normal.png"),
                                                    roughness(path.getPath() + "/Roughness.png"),
                                                     metallic(path.getPath() + "/Metallic.png") {
            }
    
            inline Surface& Material::getAlbedo() {
                return albedo;
            }
    
            inline Surface& Material::getNormal() {
                return normal;
            }
    
            inline Surface& Material::getRoughness() {
                return roughness;
            }
    
            inline Surface& Material::getMetallic() {
                return metallic;
            }
    
            inline void Material::deallocate() {
                albedo.deallocate();
                normal.deallocate();
                metallic.deallocate();
                roughness.deallocate();
            }

        }
    }
