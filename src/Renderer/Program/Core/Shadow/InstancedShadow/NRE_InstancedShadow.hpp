
    /**
     * @file NRE_InstancedShadow.hpp
     * @brief Declaration of Engine's Renderer's Object : InstancedShadow
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
             * @class InstancedShadow
             * @brief Manage the shadow's instanced rendering shader
             */
            class InstancedShadow : public AbstractProgram<InstancedShadow> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        InstancedShadow() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Shadow/InstancedShadow.vert");
                            addStage<FragmentShader>("Shadow/InstancedShadow.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("lightPV");
                        }
                        /**
                         * Send the projection view matrix to the shader
                         * @param m the projection view matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("lightPV", 1, &m);
                        }
            };
        }
    }
