
    /**
     * @file NRE_MaterialArray.hpp
     * @brief Declaration of Engine's GL's Object : MaterialArray
     * @author Louis ABEL
     * @date 31/01/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <iostream>
    #include <string>

    #include "../NRE_Material.hpp"
    #include "../../Texture2DArray/NRE_Texture2DArray.hpp"

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
             * @class MaterialArray
             * @brief Represent an array of materials
             */
            class MaterialArray {
                private:    //Fields
                    Texture2DArray albedos;         /**< The material's albedo texture array */
                    Texture2DArray normals;         /**< The material's normal texture array */
                    Texture2DArray roughness;       /**< The material's roughness texture array */
                    Texture2DArray metallics;       /**< The material's metallic texture array */
                    Texture2DArray displacements;   /**< The material's displacement texture array */
                    int nbMaterials;                /**< The number of materials */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        MaterialArray() = delete;
                        /**
                         * Construct the material array and allocate it
                         * @param nbLayers the number of layers
                         */
                        MaterialArray(int nbLayers);

                    //## Move-Constructor ##//
                        /**
                         * Move a into this, leaving a empty
                         * @param a the material array to move
                         */
                        MaterialArray(MaterialArray && a) = default;

                    //## Deconstructor ##//
                        /**
                         * MaterialArray Deconstructor
                         */
                        ~MaterialArray() = default;

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
                        /**
                         * @return the number of materials
                         */
                        int getNbMaterials() const;

                    //## Methods ##//
                        /**
                         * Allocate all arrays
                         * @param nbLayers the number of layers
                         */
                        void allocate(int nbLayers);
                        /**
                         * Send a material to the GPU
                         * @param material the material to send
                         * @param layer    the material's layer
                         */
                        void sendMaterial(Material& material, int layer);

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of a into this, leaving a empty
                         * @param a the material array to move into this
                         * @return      the reference of himself
                         */
                        MaterialArray& operator =(MaterialArray && a) = default;
                        
                public :    // Static
                    static int constexpr MAX_RESOLUTION = 256;
            };
        }
    }
    
    #include "NRE_MaterialArray.tpp"
