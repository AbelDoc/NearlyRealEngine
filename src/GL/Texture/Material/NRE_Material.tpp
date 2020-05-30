
    /**
     * @file NRE_Material.tpp
     * @brief Implementation of Engine's GL's Object : Material
     * @author Louis ABEL
     * @date 07/11/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Material::Material(Math::Vector3D<float> const& color, float r, float m, IO::File const& colorMap, IO::File const& nMap, IO::File const& rMap, IO::File const& mMap) : albedo(color), roughness(r), metallic(m), albedoMap(nullptr), normalMap(nullptr), roughnessMap(nullptr), metallicMap(nullptr) {
                loadMaps(colorMap, nMap, rMap, mMap);
            }
    
            inline Material::Material(Math::Vector3D<float> const& color, float r, float m) : albedo(color), roughness(r), metallic(m), albedoMap(nullptr), normalMap(nullptr), roughnessMap(nullptr), metallicMap(nullptr) {
            }
            
            inline Material::Material(Material && m) : albedo(m.albedo), roughness(m.roughness), metallic(m.metallic), albedoMap(m.albedoMap), normalMap(m.normalMap), roughnessMap(m.roughnessMap), metallicMap(m.metallicMap) {
                m.albedoMap = nullptr;
                m.normalMap = nullptr;
                m.roughnessMap = nullptr;
                m.metallicMap = nullptr;
            }
            
            inline Material::~Material() {
                delete albedoMap;
                delete normalMap;
                delete roughnessMap;
                delete metallicMap;
            }
            
            inline Math::Vector3D<float> const& Material::getAlbedo() const {
                return albedo;
            }
    
            inline float Material::getRoughness() const {
                return roughness;
            }
    
            inline float Material::getMetallic() const {
                return metallic;
            }
            
            inline bool Material::hasAlbedoMap() const {
                return albedoMap != nullptr;
            }
    
            inline bool Material::hasNormalMap() const {
                return normalMap != nullptr;
            }
    
            inline bool Material::hasRoughnessMap() const {
                return roughnessMap != nullptr;
            }
    
            inline bool Material::hasMetallicMap() const {
                return metallicMap != nullptr;
            }
    
            inline Surface* Material::getAlbedoMap() {
                return albedoMap;
            }
    
            inline Surface* Material::getNormalMap() {
                return normalMap;
            }
    
            inline Surface* Material::getRoughnessMap() {
                return roughnessMap;
            }
    
            inline Surface* Material::getMetallicMap() {
                return metallicMap;
            }
    
            inline void Material::deallocate() {
                if (albedoMap) {
                    albedoMap->deallocate();
                }
                if (normalMap) {
                    normalMap->deallocate();
                }
                if (metallicMap) {
                    metallicMap->deallocate();
                }
                if (roughnessMap) {
                    roughnessMap->deallocate();
                }
            }
            
            inline Material& Material::operator =(Material && m) {
                if (this != &m) {
                    albedo = m.albedo;
                    roughness = m.roughness;
                    metallic = m.metallic;
                    albedoMap = m.albedoMap;
                    normalMap = m.normalMap;
                    roughnessMap = m.roughnessMap;
                    metallicMap = m.metallicMap;
                    m.albedoMap = nullptr;
                    m.normalMap = nullptr;
                    m.roughnessMap = nullptr;
                    m.metallicMap = nullptr;
                }
                return *this;
            }
            
            inline void Material::loadMaps(IO::File const& colorMap, IO::File const& nMap, IO::File const& rMap, IO::File const& mMap) {
                if (colorMap.exist()) {
                    albedoMap = new Surface(colorMap);
                }
                if (nMap.exist()) {
                    normalMap = new Surface(nMap);
                }
                if (rMap.exist()) {
                    roughnessMap = new Surface(rMap);
                }
                if (mMap.exist()) {
                    metallicMap = new Surface(mMap);
                }
            }

        }
    }
