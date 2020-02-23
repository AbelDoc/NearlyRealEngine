
    /**
     * @file NRE_Phong.hpp
     * @brief Declaration of Engine's Renderer's Object : Phong
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
             * @class Phong
             * @brief Manage the Phong shader from the deferred rendering system
             */
            class Phong : public AbstractProgram<Phong> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Phong() {
                            load();
                        }

                    //## Deconstructor ##//
                        /**
                         * Phong Deconstructor
                         */
                        ~Phong() = default;

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        virtual void addStages() override {
                            addStage<VertexShader>("Phong/Phong.vert");
                            addStage<FragmentShader>("Phong/Phong.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("texDepth");
                            addUniform("texNormal");
                            addUniform("texTangent");
                            addUniform("texMaterials");
                            addUniform("texAlbedos");
                            for (unsigned int i = 0; i < MAX_LIGHTS; i++) {
                                Utility::String base("lights[");
                                base << i;
                                addUniform(base + "].position");
                                addUniform(base + "].intensities");
                            }
                            addUniform("cameraV");
                            addUniform("invModelview");
                            addUniform("invProjection");
                            addUniform("numLights");
                        }
                        /**
                         * Send textures binding point to the shader
                         */
                        void sendTexture() const {
                            use1I("texDepth", 0);
                            use1I("texNormal", 1);
                            use1I("texTangent", 2);
                            use1I("texMaterials", 3);
                            use1I("texAlbedos", 4);
                        }
                        /**
                         * Send the inverse projection matrix to the shader
                         * @param m the inverse projection matrix
                         */
                        void sendInvProjection(Math::Matrix4x4<float> const& m) const {
                            useMat4("invProjection", 1, &m);
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
