    
    /**
     * @file NRE_MaterialManager.hpp
     * @brief Declaration of Engine's Renderer's Object : MaterialManager
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Utility.hpp>
    #include <Header/NRE_Math.hpp>
    
    #include "../../Header/NRE_Texture.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Renderer
         * @brief Engine's Renderer module
         */
        namespace Renderer {
            
            /**
             * @class MaterialManager
             * @brief Manage the collections of materials
             */
            class MaterialManager : Utility::Singleton<MaterialManager> {
                friend class Utility::Singleton<MaterialManager>;
                
                private:    //Fields
                    Utility::Vector<GL::Material> textures; /**< The materials textures */
                    GL::MaterialArray materials;            /**< The materials array */
                
                public:    // Methods
                    //## Getter ##//
                        /**
                         * Albedos getter
                         * @return the albedo texture array
                         */
                        GL::Texture2DArray const& getAlbedos() const;
                        /**
                         * Normals getter
                         * @return the normal texture array
                         */
                        GL::Texture2DArray const& getNormals() const;
                        /**
                         * Roughness getter
                         * @return the roughness texture array
                         */
                        GL::Texture2DArray const& getRoughness() const;
                        /**
                         * Metallics getter
                         * @return the metallic texture array
                         */
                        GL::Texture2DArray const& getMetallics() const;
                
                private:   // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        MaterialManager();
                        
                        //## Deconstructor ##//
                        /**
                         * MaterialManager Deconstructor
                         */
                        ~MaterialManager() = default;
                
                public:     // Static
                    static constexpr std::size_t RESOLUTION = 1024;    /**< The material resolution */
                    
            };
        }
    }
    
    #include "NRE_MaterialManager.tpp"
