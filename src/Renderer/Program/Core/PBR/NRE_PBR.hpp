
    /**
     * @file NRE_PBR.hpp
     * @brief Declaration of Engine's Renderer's Object : PBR
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../../NRE_AbstractProgram.hpp"
     #include "../../../../Header/NRE_Camera.hpp"

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
             * @class PBR
             * @brief Manage the PBR shader from the deferred rendering system
             */
            class PBR : public AbstractProgram<PBR> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        PBR() {
                            load();
                        }

                    //## Deconstructor ##//
                        /**
                         * PBR Deconstructor
                         */
                        ~PBR() = default;

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        virtual void addStages() override {
                            addStage<VertexShader>("PBR/PBR.vert");
                            addStage<FragmentShader>("PBR/PBR.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("texPos");
                            addUniform("texColor");
                            addUniform("texNormal");
                            addUniform("texMaterial");
                            addUniform("irradianceMap");
                            addUniform("prefilterMap");
                            addUniform("brdfLUT");
                            for (unsigned int i = 0; i < MAX_LIGHTS; i++) {
                                Utility::String base("lights[");
                                base << i;
                                addUniform(base + "].position");
                                addUniform(base + "].intensities");
                            }
                            addUniform("cameraV");
                            addUniform("invView");
                            addUniform("numLights");
                        }
                        /**
                         * Send textures binding point to the shader
                         */
                        void sendTexture() const {
                            use1I("irradianceMap", 0);
                            use1I("prefilterMap", 1);
                            use1I("brdfLUT", 2);
                            use1I("texPos", 3);
                            use1I("texColor", 4);
                            use1I("texNormal", 5);
                            use1I("texMaterial", 6);
                        }
                        /**
                         * Send the camera's position to the camera
                         * @param c the camera
                         */
                        void sendCamera(Camera::Camera const& c) const {
                            Math::Matrix4x4<float> invView = c.getView();
                            invView.inverse();
                            use3FV("cameraV", 1, c.getEye().value());
                            useMat4("invView", 1, &invView);
                        }

                public:     // Static
                    constexpr static const GLuint MAX_LIGHTS = 100;  /**< The maximum number of light in a scene */
            };
        }
    }
