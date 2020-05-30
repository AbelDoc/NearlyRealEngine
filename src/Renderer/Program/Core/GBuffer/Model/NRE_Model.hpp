
    /**
     * @file NRE_Model.hpp
     * @brief Declaration of Engine's Renderer's Object : Model
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
             * @class Model
             * @brief Manage a gbuffer shader to draw textured model
             */
            class Model : public AbstractProgram<Model> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Model() {
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
                            addUniform("MVP");
                            addUniform("numMats");
                            for (unsigned int i = 0; i < MAX_MATERIALS; i++) {
                                Utility::String base("materials[");
                                base << i;
                                addUniform(base + "].albedo");
                                addUniform(base + "].roughness");
                                addUniform(base + "].metallic");
                            }
                        }
                        /**
                         * Send a matrix to the shader
                         * @param m the matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }

                public:     // Static
                    constexpr static const GLuint MAX_MATERIALS = 100;  /**< The maximum number of materials in a scene */
            };
        }
    }
