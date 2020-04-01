    
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
                         * @return the albedo texture array
                         */
                        GL::Texture2DArray const& getAlbedos() const;
                        /**
                         * @return the normal texture array
                         */
                        GL::Texture2DArray const& getNormals() const;
                        /**
                         * @return the roughness texture array
                         */
                        GL::Texture2DArray const& getRoughness() const;
                        /**
                         * @return the metallic texture array
                         */
                        GL::Texture2DArray const& getMetallics() const;
                        /**
                         * @return the displacement texture array
                         */
                        GL::Texture2DArray const& getDisplacements() const;
                
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
            };
        }
    }
    
    #include "NRE_MaterialManager.tpp"
