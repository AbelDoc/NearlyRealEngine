
    /**
     * @file Core/SkyBox/SkyBox/NRE_SkyBox.hpp
     * @brief Declaration of Engine's Renderer's Object : SkyBox
     * @author Louis ABEL
     * @date 07/11/2018
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
             * @class SkyBox
             * @brief Manage the skybox's rendering shader
             */
            class SkyBox : public AbstractProgram<SkyBox> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        SkyBox() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("SkyBox/SkyBox.vert");
                            addStage<FragmentShader>("SkyBox/SkyBox.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("MVP");
                        }
                        /**
                         * Send the mvp matrix to the shader
                         * @param m the mvp matrix
                         */
                        void sendMVP(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }
            };
        }
    }
