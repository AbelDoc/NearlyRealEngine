
    /**
     * @file NRE_Shadow.hpp
     * @brief Declaration of Engine's Renderer's Object : Shadow
     * @author Louis ABEL
     * @date 10/02/2020
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
             * @class Shadow
             * @brief Manage the shadow's rendering shader
             */
            class Shadow : public AbstractProgram<Shadow> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Shadow() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Shadow/Shadow.vert");
                            addStage<FragmentShader>("Shadow/Shadow.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("lightMVP");
                        }
                        /**
                         * Send the mvp matrix to the shader
                         * @param m the mvp matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("lightMVP", 1, &m);
                        }
            };
        }
    }
