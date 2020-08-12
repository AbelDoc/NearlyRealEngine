
    /**
     * @file NRE_SSAOEffect.hpp
     * @brief Declaration of Engine's Renderer's Object : SSAOEffect
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <iostream>
    #include <string>

    #include "../../NRE_AbstractProgram.hpp"
    #include "../../../SSAO/NRE_SSAO.hpp"

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
             * @class SSAOEffect
             * @brief Manage the ssao effect
             */
            class SSAOEffect : public AbstractProgram<SSAOEffect> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        SSAOEffect() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("SSAO/SSAOEffect.vert");
                            addStage<FragmentShader>("SSAO/SSAOEffect.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("texPos");
                            addUniform("texNormal");
                            addUniform("texNoise");
                            addUniform("projection");
                            addUniform("normalMat");
                            addUniform("gKernel");
                        }
                        /**
                         * Send the ssao kernel
                         * @param ssao the ssao object
                         */
                        void sendKernel(SSAO const& ssao) const {
                            use3FV("gKernel", SSAO::KERNEL_SIZE, ssao.getKernel()[0].value());
                        }
                        /**
                         * Send textures binding point to the shader
                         */
                        void sendTexture() const {
                            use1I("texPos", 0);
                            use1I("texNormal", 1);
                            use1I("texNoise", 2);
                        }
                        /**
                         * Send the projection matrix to the shader
                         * @param m the projection matrix
                         */
                        void sendProjection(Math::Matrix4x4<float> const& m) const {
                            useMat4("projection", 1, &m);
                        }
                        /**
                         * Send the normal matrix to the shader
                         * @param m the normal matrix
                         */
                        void sendNormalMatrix(Math::Matrix3x3<float> const& m) const {
                            useMat3("normalMat", 1, &m);
                        }
            };
        }
    }
