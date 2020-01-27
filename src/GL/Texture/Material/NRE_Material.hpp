
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
            class Material : public Utility::Uncopyable<Material> {
                private:    //Fields
                    Surface albedo;         /**< The material's albedo */
                    Surface normal;         /**< The material's normal */
                    Surface roughness;      /**< The material's roughness */
                    Surface metallic;       /**< The material's metallic */
                    Surface displacement;   /**< The material's displacement */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Material() = delete;
                        /**
                         * Construct a material from it's name
                         * @param path the material file's path
                         */
                        Material(IO::File const& path);

                    //## Move-Constructor ##//
                        /**
                         * Move m into this
                         * @param m the material to move
                         */
                        Material(Material && m) = default;

                    //## Deconstructor ##//
                        /**
                         * Material Deconstructor
                         */
                        ~Material() = default;

                    //## Getter ##//
                        /**
                         * @return the material's albedo
                         */
                        Surface& getAlbedo();
                        /**
                         * @return the material's normal
                         */
                        Surface& getNormal();
                        /**
                         * @return the material's roughness
                         */
                        Surface& getRoughness();
                        /**
                         * @return the material's metallic
                         */
                        Surface& getMetallic();
                        /**
                         * @return the material's displacement
                         */
                        Surface& getDisplacement();

                    //## Methods ##//
                        /**
                         * Deallocate all surfaces
                         */
                        void deallocate();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the material to move into this
                         * @return      the reference of himself
                         */
                        Material& operator =(Material && m) = default;

            };
        }
    }
    
    #include "NRE_Material.tpp"
