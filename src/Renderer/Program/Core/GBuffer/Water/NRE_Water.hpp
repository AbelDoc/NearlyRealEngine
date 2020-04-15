
    /**
     * @file NRE_Water.hpp
     * @brief Declaration of Engine's Renderer's Object : Water
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
             * @class Water
             * @brief Manage a water shader to draw fluid in a buffer
             */
            class Water : public AbstractProgram<Water> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Water() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/Water.vert");
                            addStage<FragmentShader>("GBuffer/Water.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("MVP");
                            addUniform("time");
                        }
                        /**
                         * Send a matrix to the shader
                         * @param m the matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }
                        /**
                         * Send the time to the shader
                         * @param t the time
                         */
                        void sendTime(float t) const {
                            use1F("time", t);
                        }
            };
        }
    }
