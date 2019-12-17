
    /**
     * @file Core/Primitive/Instanced3D/NRE_InstancedPrimitive3D.hpp
     * @brief Declaration of Engine's Renderer's Object : InstancedPrimitive3D
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
             * @class InstancedPrimitive3D
             * @brief Manage a 3D shader to draw simple instanced 3D primitives
             */
            class InstancedPrimitive3D : public AbstractProgram<InstancedPrimitive3D> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        InstancedPrimitive3D() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Primitive/InstancedPrimitive3D.vert");
                            addStage<FragmentShader>("Primitive/InstancedPrimitive3D.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("modelview");
                            addUniform("projection");
                            addUniform("camera");
                        }
                        /**
                         * Send a mvp matrix to the shader
                         * @param m the mvp matrix
                         */
                        void sendCamera(Camera::Camera const& c) const {
                            useMat4("modelview", 1, &c.getView());
                            useMat4("projection", 1, &c.getProjection());
                            use3FV("camera", 1, c.getEye().value());
                        }
            };
        }
    }
