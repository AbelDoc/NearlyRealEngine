    
    /**
     * @file NRE_MaterialManager.hpp
     * @brief Declaration of Engine's Renderer's Object : MaterialManager
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Core.hpp>
    #include <Header/NRE_Math.hpp>

    #include "../../GL/Texture/Material/NRE_Material.hpp"
    #include "../../GL/Texture/Material/Array/NRE_MaterialArray.hpp"
    
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
            class MaterialManager : Core::Singleton<MaterialManager> {
                friend class Core::Singleton<MaterialManager>;
                public :    // Iterator
                    /**< Shortcut to hide Iterator implementation */
                    typedef typename Core::Vector<GL::Material>::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef typename Core::Vector<GL::Material>::ConstIterator    ConstIterator;
                
                private:    //Fields
                    Core::Vector<GL::Material> textures; /**< The materials textures */
                    GL::MaterialArray materials;            /**< The materials array */
                    int currentLayer;                       /**< The materials array current layer */
                
                public:    // Methods
                    //## Getter ##//
                        /**
                         * @return the number of stored materials
                         */
                        std::size_t getNbMaterials() const;
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
    
                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first material
                         */
                        Iterator begin();
                        /**
                         * @return a const iterator on the first material
                         */
                        ConstIterator begin() const;
                        /**
                         * @return a const iterator on the first material
                         */
                        ConstIterator cbegin() const;
                        /**
                         * @return an iterator on the end of the container
                         */
                        Iterator end();
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator end() const;
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator cend() const;
    
                    //## Methods ##//
                        /**
                         * Add a material to the manager
                         * @param m the material to add
                         */
                        void add(GL::Material && m);
                    
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
