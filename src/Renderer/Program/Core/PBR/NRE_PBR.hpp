
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
                            addUniform("texDepth");
                            addUniform("texShadow");
                            addUniform("texNormal");
                            addUniform("texTangent");
                            addUniform("texMaterials");
                            addUniform("irradianceMap");
                            addUniform("prefilterMap");
                            addUniform("brdfLUT");
                            addUniform("texAlbedos");
                            addUniform("texNormals");
                            addUniform("texRoughness");
                            addUniform("texMetallics");
                            addUniform("texDisplacements");
                            for (unsigned int i = 0; i < MAX_LIGHTS; i++) {
                                Utility::String base("lights[");
                                base << i;
                                addUniform(base + "].position");
                                addUniform(base + "].intensities");
                            }
                            addUniform("cameraV");
                            addUniform("invModelview");
                            addUniform("invProjection");
                            addUniform("lightSpace");
                            addUniform("numLights");
                        }
                        /**
                         * Send textures binding point to the shader
                         */
                        void sendTexture() const {
                            use1I("irradianceMap", 0);
                            use1I("prefilterMap", 1);
                            use1I("brdfLUT", 2);
                            use1I("texDepth", 3);
                            use1I("texNormal", 4);
                            use1I("texTangent", 5);
                            use1I("texMaterials", 6);
                            use1I("texAlbedos", 7);
                            use1I("texNormals", 8);
                            use1I("texRoughness", 9);
                            use1I("texMetallics", 10);
                            use1I("texDisplacements", 11);
                            use1I("texShadow", 12);
                        }
                        /**
                         * Send the inverse projection matrix to the shader
                         * @param m the inverse projection matrix
                         */
                        void sendInvProjection(Math::Matrix4x4<float> const& m) const {
                            useMat4("invProjection", 1, &m);
                        }
                        /**
                         * Send the light space matrix to the shader
                         * @param m the light space matrix
                         */
                        void sendLightSpace(Math::Matrix4x4<float> const& m) const {
                            useMat4("lightSpace", 1, &m);
                        }
                        /**
                         * Send the camera's position to the camera
                         * @param c the camera
                         */
                        void sendCamera(Camera::Camera const& c) const {
                            Math::Matrix4x4<float> invModelview = c.getView();
                            invModelview.inverse();
                            use3FV("cameraV", 1, c.getEye().value());
                            useMat4("invModelview", 1, &invModelview);
                        }

                public:     // Static
                    constexpr static const GLuint MAX_LIGHTS = 100;  /**< The maximum number of light in a scene */
            };
        }
    }
