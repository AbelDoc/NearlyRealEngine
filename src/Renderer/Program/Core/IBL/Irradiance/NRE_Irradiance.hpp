
    /**
     * @file NRE_Irradiance.hpp
     * @brief Declaration of Engine's Renderer's Object : Irradiance
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
             * @class Irradiance
             * @brief Manage a specific shader to compute irradiance map
             */
            class Irradiance : public AbstractProgram<Irradiance> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Irradiance() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("IBL/Irradiance.vert");
                            addStage<FragmentShader>("IBL/Irradiance.frag");
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
