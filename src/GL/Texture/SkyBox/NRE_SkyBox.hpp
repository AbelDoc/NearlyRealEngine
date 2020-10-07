
    /**
     * @file Texture/SkyBox/NRE_SkyBox.hpp
     * @brief Declaration of Engine's GL's Object : SkyBox
     * @author Louis ABEL
     * @date 06/11/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <memory>

    #include "../../FBO/NRE_FBO.hpp"
    #include "../Texture2D/NRE_Texture2D.hpp"
    #include "../../Buffer/Attachable/Texture/CubeMap/NRE_CubeMap.hpp"
    #include "../../Buffer/Attachable/RenderBuffer/NRE_RenderBuffer.hpp"
    
    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_IO.hpp>
    
    #include "../../../Header/NRE_Shader.hpp"
    #include "../../../Header/NRE_Camera.hpp"
    #include "../../../Header/NRE_Physics.hpp"
    
    #include <Header/NRE_Core.hpp>

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
             * @class SkyBox
             * @brief Manage a skybox for environment mapping
             */
            class SkyBox : public Core::Uncopyable<SkyBox> {
                private:    //Fields
                    CubeMap map;                        /**< The skybox's base texture */
                    CubeMap irradiance;                 /**< The skybox's irradiance texture */
                    CubeMap prefilter;                  /**< The skybox's prefilter texture */
                    Texture2D brdfLUT;                  /**< The skybox's BRDF texture */
                    Model::CubeMesh mesh;               /**< The skybox mesh */

            public:    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        SkyBox() = delete;
                        /**
                         * Construct a skybox from it's
                         * @param file the skybox's texture path
                         */
                        SkyBox(IO::File const& file);

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the skybox to move
                         */
                        SkyBox(SkyBox && s) = default;

                    //## Deconstructor ##//
                        /**
                         * SkyBox Deconstructor
                         */
                        ~SkyBox() = default;

                    //## Getter ##//
                        /**
                         * @return the prefilter texture
                         */
                        CubeMap const& getPrefilter() const;
                        /**
                         * @return the prefilter texture
                         */
                        CubeMap const& getIrradiance() const;
                        /**
                         * @return the map texture
                         */
                        CubeMap const& getMap() const;
                        /**
                         * @return the brdf texture
                         */
                        Texture2D const& getBRDFLUT() const;
                        /**
                         * @return the skybox mesh
                         */
                        Model::CubeMesh const& getMesh() const;

                    //## Methods ##//
                        /**
                         * Allocate the skybox
                         */
                        void allocate();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of s into this
                         * @param s the skybox to move into this
                         * @return      the reference of himself
                         */
                        SkyBox& operator =(SkyBox && s) = default;
                        
                private :   // Methods
                    /**
                     * Capture the hdr texture into a cubemap and compute prefilter, irradiance and brdf texture
                     * @param file the skybox's texture path
                     */
                    void capture(IO::File const& file);

                public:     // Static
                    static constexpr GLuint SIZE = 2048;   /**< The skybox resolution */
            };
        }
    }
    
    #include "NRE_SkyBox.tpp"
