
    /**
     * @file NRE_ModelShader.hpp
     * @brief Declaration of Engine's Renderer's Object : ModelShader
     * @author Louis ABEL
     * @date 15/04/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../../../NRE_AbstractProgram.hpp"

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
             * @class ModelShader
             * @brief Manage a gbuffer shader to draw textured model
             */
            class ModelShader : public AbstractProgram<ModelShader> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ModelShader() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/Model.vert");
                            addStage<FragmentShader>("GBuffer/Model.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("model");
                            addUniform("view");
                            addUniform("projection");
                            addUniform("numMats");
                            for (unsigned int i = 0; i < MAX_MATERIALS; i++) {
                                Core::String base("materials[");
                                base << i;
                                addUniform(base + "].albedo");
                                addUniform(base + "].roughness");
                                addUniform(base + "].metallic");
                            }
                        }
                        /**
                         * Send the projection matrix to the shader
                         * @param m the matrix
                         */
                        void sendProjection(Math::Matrix4x4<float> const& m) const {
                            useMat4("projection", 1, &m);
                        }
                        /**
                         * Send the view matrix to the shader
                         * @param m the matrix
                         */
                        void sendView(Math::Matrix4x4<float> const& m) const {
                            useMat4("view", 1, &m);
                        }
                        /**
                         * Send the model matrix to the shader
                         * @param m the matrix
                         */
                        void sendModel(Math::Matrix4x4<float> const& m) const {
                            useMat4("model", 1, &m);
                        }

                public:     // Static
                    constexpr static const GLuint MAX_MATERIALS = 16;  /**< The maximum number of materials in a scene */
            };
        }
    }
