
    /**
     * @file NRE_Material.hpp
     * @brief Declaration of Engine's GL's Object : Material
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../Surface/NRE_Surface.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace GL
         * @brief Engine's GL module
         */
        namespace GL {

            /**
             * @class Material
             * @brief Describe a PBR material
             */
            class Material : public Core::Uncopyable<Material> {
                private:    //Fields
                    Math::Vector3D<float> albedo;   /**< The material's albedo */
                    float roughness;                /**< The material's roughness */
                    float metallic;                 /**< The material's metallic */
                    Surface* albedoMap;             /**< The material's albedo map */
                    Surface* normalMap;             /**< The material's normal map */
                    Surface* roughnessMap;          /**< The material's roughness map */
                    Surface* metallicMap;           /**< The material's metallic map */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Material() = delete;
                        /**
                         * Construct a material from it's path and values
                         * @param color    the material's albedo
                         * @param r        the material's roughness factor
                         * @param m        the material's metallic factor
                         * @param colorMap the material's albedo map's path
                         * @param nMap     the material's normal map's path
                         * @param rMap     the material's roughness map's path
                         * @param mMap     the material's metallic map's path
                         */
                        Material(Math::Vector3D<float> const& color, float r, float m, IO::File const& colorMap, IO::File const& nMap, IO::File const& rMap, IO::File const& mMap);
                        /**
                         * Construct a material from its values
                         * @param color the material's albedo
                         * @param r     the material's roughness factor
                         * @param m     the material's metallic factor
                         */
                        Material(Math::Vector3D<float> const& color, float r, float m);

                    //## Move-Constructor ##//
                        /**
                         * Move m into this
                         * @param m the material to move
                         */
                        Material(Material && m);

                    //## Deconstructor ##//
                        /**
                         * Material Deconstructor
                         */
                        ~Material();

                    //## Getter ##//
                        /**
                         * @return the material's albedo
                         */
                        Math::Vector3D<float> const& getAlbedo() const;
                        /**
                         * @return the material's roughness
                         */
                        float getRoughness() const;
                        /**
                         * @return the material's metallic
                         */
                        float getMetallic() const;
                        /**
                         * @return if the material has an albedo map
                         */
                        bool hasAlbedoMap() const;
                        /**
                         * @return if the material has a normal map
                         */
                        bool hasNormalMap() const;
                        /**
                         * @return if the material has a roughness map
                         */
                        bool hasRoughnessMap() const;
                        /**
                         * @return if the material has a metallic map
                         */
                        bool hasMetallicMap() const;
                        /**
                         * @return the material's albedo map
                         */
                        Surface* getAlbedoMap();
                        /**
                         * @return the material's normal map
                         */
                        Surface* getNormalMap();
                        /**
                         * @return the material's roughness map
                         */
                        Surface* getRoughnessMap();
                        /**
                         * @return the material's metallic map
                         */
                        Surface* getMetallicMap();

                    //## Methods ##//
                        /**
                         * Deallocate all surfaces if necessary
                         */
                        void deallocate();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the material to move into this
                         * @return  the reference of himself
                         */
                        Material& operator =(Material && m);
                        
                private :   // Methods
                    /**
                     * Load all material's maps
                     * @param colorMap the material's albedo map's path
                     * @param nMap     the material's normal map's path
                     * @param rMap     the material's roughness map's path
                     * @param mMap     the material's metallic map's path
                     */
                    void loadMaps(IO::File const& colorMap, IO::File const& nMap, IO::File const& rMap, IO::File const& mMap);
            };
        }
    }
    
    #include "NRE_Material.tpp"
