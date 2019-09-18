
    /**
     * @file Core/Primitive/3D/NRE_Primitive3D.hpp
     * @brief Declaration of Engine's Renderer's Object : Primitive3D
     * @author Louis ABEL
     * @date 26/08/2019
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
             * @class Primitive3D
             * @brief Manage a 3D shader to draw simple 3D primitives
             */
            class Primitive3D : public AbstractProgram<Primitive3D> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Primitive3D() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Primitive/Primitive3D.vert");
                            addStage<FragmentShader>("Primitive/Primitive3D.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("MVP");
                        }
                        /**
                         * Send a mvp matrix to the shader
                         * @param m the mvp matrix
                         */
                        void sendMVP(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }
            };
        }
    }