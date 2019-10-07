
    /**
     * @file Core/Debug/Normal/NRE_DebugNormal.hpp
     * @brief Declaration of Engine's Renderer's Object : DebugNormal
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../../../NRE_AbstractProgram.hpp"
    #include "../../../../../Header/NRE_Camera.hpp"

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
             * @class DebugNormal
             * @brief Manage a 3D shader to draw simple 3D primitives
             */
            class DebugNormal : public AbstractProgram<DebugNormal> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        DebugNormal() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Debug/DebugNormal.vert");
                            addStage<GeometryShader>("Debug/DebugNormal.geom");
                            addStage<FragmentShader>("Debug/DebugNormal.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("modelview");
                            addUniform("projection");
                        }
                        /**
                         * Send a mvp matrix to the shader
                         * @param m the mvp matrix
                         */
                        void sendCamera(Camera::Camera const& c) const {
                            useMat4("modelview", 1, &c.getView());
                            useMat4("projection", 1, &c.getProjection());
                        }
            };
        }
    }
