
    /**
     * @file NRE_InstancedGBuffer.hpp
     * @brief Declaration of Engine's Renderer's Object : InstancedGBuffer
     * @author Louis ABEL
     * @date 24/09/2018
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
             * @class InstancedGBuffer
             * @brief Manage a gbuffer shader to draw simple 3D primitives in a buffer
             */
            class InstancedGBuffer : public AbstractProgram<InstancedGBuffer> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        InstancedGBuffer() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/InstancedGBuffer.vert");
                            addStage<FragmentShader>("GBuffer/InstancedGBuffer.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("PV");
                        }
                        /**
                         * Send a matrix to the shader
                         * @param m the matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("PV", 1, &m);
                        }
            };
        }
    }
