
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
                            addUniform("MVP");
                            addUniform("texAlbedos");
                            addUniform("texNormals");
                            addUniform("texRoughness");
                            addUniform("texMetallics");
                        }
                        /**
                         * Send textures binding point to the shader
                         */
                        void sendTexture() const {
                            use1I("texAlbedos", 0);
                            use1I("texNormals", 1);
                            use1I("texRoughness", 2);
                            use1I("texMetallics", 3);
                        }
                        /**
                         * Send a matrix to the shader
                         * @param m the matrix
                         */
                        void sendMatrix(Math::Matrix4x4<float> const& m) const {
                            useMat4("MVP", 1, &m);
                        }
            };
        }
    }
