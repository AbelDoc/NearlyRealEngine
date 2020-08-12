
    /**
     * @file NRE_Terrain.hpp
     * @brief Declaration of Engine's Renderer's Object : Terrain
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
             * @class Terrain
             * @brief Manage a gbuffer shader to draw triplanar terrain
             */
            class Terrain : public AbstractProgram<Terrain> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Terrain() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("GBuffer/Terrain.vert");
                            addStage<FragmentShader>("GBuffer/Terrain.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                            addUniform("projection");
                            addUniform("view");
                            addUniform("numMats");
                            for (unsigned int i = 0; i < MAX_MATERIALS; i++) {
                                Utility::String base("materials[");
                                base << i;
                                addUniform(base + "].albedo");
                                addUniform(base + "].roughness");
                                addUniform(base + "].metallic");
                            }
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

                public:     // Static
                    constexpr static const GLuint MAX_MATERIALS = 100;  /**< The maximum number of materials in a scene */
            };
        }
    }
