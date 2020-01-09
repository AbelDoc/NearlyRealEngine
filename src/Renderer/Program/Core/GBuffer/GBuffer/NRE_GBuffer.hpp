
    /**
     * @file NRE_GBuffer.hpp
     * @brief Declaration of Engine's Renderer's Object : GBuffer
     * @author Louis ABEL
     * @date 24/09/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "NRE_AbstractProgram.hpp"

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
             * @class GBuffer
             * @brief Manage a gbuffer shader to draw simple 3D primitives in a buffer
             */
            class GBuffer : public AbstractProgram<GBuffer> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        GBuffer() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/GBuffer.vert");
                            addStage<FragmentShader>("GBuffer/GBuffer.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("MVP");
                        }
                        /**
                         * Send a matrix to the shader
                         * @param m the matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }
            };
        }
    }
