
    /**
     * @file NRE_Prefilter.hpp
     * @brief Declaration of Engine's Renderer's Object : Prefilter
     * @author Louis ABEL
     * @date 06/11/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <iostream>
    #include <string>

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
             * @class Prefilter
             * @brief Manage a specific shader to compute prefilter map
             */
            class Prefilter : public AbstractProgram<Prefilter> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Prefilter() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("IBL/Prefilter.vert");
                            addStage<FragmentShader>("IBL/Prefilter.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("modelview");
                            addUniform("roughness");
                        }
                        /**
                         * Send a modelview matrix to the shader
                         * @param m the modelview matrix
                         */
                        void sendModelview(Math::Matrix4x4<float> const& m) const {
                            useMat4("modelview", 1, &m);
                        }
                        /**
                         * Send the roughness value to the shader
                         * @param value the roughness value
                         */
                        void sendRoughness(float value) {
                            use1F("roughness", value);
                        }
            };
        }
    }
