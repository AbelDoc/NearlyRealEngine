
    /**
     * @file NRE_VoxelShader.hpp
     * @brief Declaration of Engine's Renderer's Object : VoxelShader
     * @author Louis ABEL
     * @date 15/04/2020
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
             * @class VoxelShader
             * @brief Manage a gbuffer shader to draw triplanar terrain
             */
            class VoxelShader : public AbstractProgram<VoxelShader> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VoxelShader() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/Voxel.vert");
                            addStage<FragmentShader>("GBuffer/Voxel.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("projection");
                            addUniform("view");
                        }
                        /**
                         * Send the projection matrix to the shader
                         * @param m the matrix
                         */
                        void sendProjection(Math::Matrix4x4<float> const& m) const {
                            useMat4("projection", 1, &m);
                        }
                        /**
                         * Send the view matrix to the shader
                         * @param m the matrix
                         */
                        void sendView(Math::Matrix4x4<float> const& m) const {
                            useMat4("view", 1, &m);
                        }
            };
        }
    }
