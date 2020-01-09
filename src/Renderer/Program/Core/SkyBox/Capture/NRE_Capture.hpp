
    /**
     * @file NRE_Capture.hpp
     * @brief Declaration of Engine's Renderer's Object : Capture
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
             * @class Capture
             * @brief Manage a capture shader to capture an equirectangular map into a cubemap
             */
            class Capture : public AbstractProgram<Capture> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Capture() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("SkyBox/Capture.vert");
                            addStage<FragmentShader>("SkyBox/Capture.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("modelview");
                        }
                        /**
                         * Send a modelview matrix to the shader
                         * @param m the modelview matrix
                         */
                        void sendModelview(Math::Matrix4x4<float> const& m) const {
                            useMat4("modelview", 1, &m);
                        }
            };
        }
    }
