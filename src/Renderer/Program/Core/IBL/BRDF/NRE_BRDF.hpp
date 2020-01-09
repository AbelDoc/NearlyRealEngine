
    /**
     * @file NRE_BRDF.hpp
     * @brief Declaration of Engine's Renderer's Object : BRDF
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
             * @class BRDF
             * @brief Manage a shader to compute BRDF LUT texture
             */
            class BRDF : public AbstractProgram<BRDF> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        BRDF() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("IBL/BRDF.vert");
                            addStage<FragmentShader>("IBL/BRDF.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                        }
            };
        }
    }
