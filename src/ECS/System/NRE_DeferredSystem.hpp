
    /**
     * @file NRE_DeferredSystem.hpp
     * @brief Declaration of Engine's ECS's Object : DeferredSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <Header/NRE_ECS.hpp>
    
    #include "../../Header/NRE_Shader.hpp"
    #include "../../Header/NRE_Renderer.hpp"
    
    #include "NRE_FlockSystem.hpp"
    #include "NRE_GBufferSystem.hpp"
    #include "NRE_InstancedGBufferSystem.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace ECS
         * @brief Engine's ECS module
         */
        namespace ECS {
            
            /**
             * @class DeferredSystem
             * @brief Manage deferred rendering
             */
            class DeferredSystem : public System<DeferredSystem> {
                private:    //Fields
                    Renderer::DeferredRenderer renderer;   /**< The deferred renderer object */
                    Camera::Camera const& camera;          /**< The application's camera */
                    Model::RectangleMesh screen;           /**< The screen mesh */
                    Renderer::SSAO ssao;                   /**< The ssao object */
                    GL::SkyBox skyBox;                     /**< The skybox */

            public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the deferred system
                         * @param c          the application's camera
                         * @param screenSize the window screen size
                         * @param mapPath    the application's skybox
                         */
                        DeferredSystem(Camera::Camera const& c, Math::Vector2D<unsigned int> const& screenSize, IO::File const& mapPath) : renderer(screenSize), camera(c), screen(Physics::Rectangle(Math::Point2D<float>(-1, -1), Math::Vector2D<float>(2, 2))), skyBox(mapPath) {
                            glViewport(0, 0, screenSize.getW(), screenSize.getH());
                        }
                        
                    //## Methods ##//
                        /**
                         * Configure the system, called once before any rendering or update
                         */
                        void configure() override {
                            Math::Matrix4x4<float> invProjection = camera.getProjection();
                            invProjection.inverse();
                            
                            auto pbr = Renderer::ProgramManager::get<Renderer::PBR>();
                            auto ssaoEffect = Renderer::ProgramManager::get<Renderer::SSAOEffect>();
    
                            pbr->bind();
                                pbr->sendTexture();
                                pbr->sendInvProjection(invProjection);
                            pbr->unbind();
                            ssaoEffect->bind();
                                ssaoEffect->sendKernel(ssao);
                                ssaoEffect->sendTexture();
                                ssaoEffect->sendProjection(camera.getProjection());
                                ssaoEffect->sendInvProjection(invProjection);
                            ssaoEffect->unbind();
                        }
                        /**
                         * Perform the GBuffer pass
                         */
                        void gBufferPass() {
                            renderer.bind();
                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
                                glDrawBuffers(3, buffers);

                                Math::Matrix4x4<float> MVP = camera.getProjection() * Math::Matrix4x4<float>(Math::Matrix3x3<float>(camera.getView()));
                                glDepthFunc(GL_LEQUAL);
                                    Renderer::ProgramManager::get<Renderer::SkyBox>()->bind();
                                    Renderer::ProgramManager::get<Renderer::SkyBox>()->sendMVP(MVP);
                                        skyBox.getMap().bind();
                                            skyBox.getMesh().draw();
                                        skyBox.getMap().unbind();
                                    Renderer::ProgramManager::get<Renderer::SkyBox>()->unbind();
                                glDepthFunc(GL_LESS);

                                SystemManager::get<GBufferSystem>()->update();
                                SystemManager::get<InstancedGBufferSystem>()->update();
                            renderer.unbind();
                        }
                        /**
                         * Perform the SSAO pass
                         */
                        void SSAOPass() {
                            renderer.bind();
                                glDepthMask(false);
                                glColorMask(false, false, false, true);
                    
                                GLenum buffers[] = {GL_COLOR_ATTACHMENT2};
                                glDrawBuffers(1, buffers);
                    
                                Renderer::ProgramManager::get<Renderer::SSAOEffect>()->bind();
                                    glActiveTexture(GL_TEXTURE0);
                                        renderer.getDepthBuffer()->bind();
                                    glActiveTexture(GL_TEXTURE1);
                                        renderer.getColorBuffer(0)->bind();
                                    glActiveTexture(GL_TEXTURE2);
                                        ssao.getNoise().bind();
                        
                                    screen.draw();
                        
                                    glActiveTexture(GL_TEXTURE2);
                                        ssao.getNoise().unbind();
                                    glActiveTexture(GL_TEXTURE1);
                                        renderer.getColorBuffer(0)->bind();
                                    glActiveTexture(GL_TEXTURE0);
                                        renderer.getDepthBuffer()->bind();
                                Renderer::ProgramManager::get<Renderer::SSAOEffect>()->unbind();
                    
                                glColorMask(true, true, true, true);
                                glDepthMask(true);
                            renderer.unbind();
                        }
                        /**
                         * Perform the PBR pass
                         */
                        void PBRPass() {
                            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                            auto pbr = Renderer::ProgramManager::get<Renderer::PBR>();
                            
                            pbr->bind();
                                pbr->sendCamera(camera);
                                sendLight();

                                glActiveTexture(GL_TEXTURE0);
                                    skyBox.getIrradiance().bind();
                                glActiveTexture(GL_TEXTURE1);
                                    skyBox.getPrefilter().bind();
                                glActiveTexture(GL_TEXTURE2);
                                    skyBox.getBRDFLUT().bind();
                                glActiveTexture(GL_TEXTURE3);
                                    renderer.getDepthBuffer()->bind();
                                glActiveTexture(GL_TEXTURE4);
                                    renderer.getColorBuffer(0)->bind();
                                glActiveTexture(GL_TEXTURE5);
                                    renderer.getColorBuffer(1)->bind();
                                glActiveTexture(GL_TEXTURE6);
                                    renderer.getColorBuffer(2)->bind();
                                glActiveTexture(GL_TEXTURE7);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getAlbedos().bind();
                                glActiveTexture(GL_TEXTURE8);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getNormals().bind();
                                glActiveTexture(GL_TEXTURE9);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getRoughness().bind();
                                glActiveTexture(GL_TEXTURE10);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getMetallics().bind();
                                glActiveTexture(GL_TEXTURE11);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getDisplacements().bind();
                                
                                    screen.draw();
                                    
                                glActiveTexture(GL_TEXTURE11);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getDisplacements().unbind();
                                glActiveTexture(GL_TEXTURE10);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getMetallics().unbind();
                                glActiveTexture(GL_TEXTURE9);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getRoughness().unbind();
                                glActiveTexture(GL_TEXTURE8);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getNormals().unbind();
                                glActiveTexture(GL_TEXTURE7);
                                    Utility::Singleton<Renderer::MaterialManager>::get().getAlbedos().unbind();
                                glActiveTexture(GL_TEXTURE6);
                                    renderer.getColorBuffer(2)->unbind();
                                glActiveTexture(GL_TEXTURE5);
                                    renderer.getColorBuffer(1)->unbind();
                                glActiveTexture(GL_TEXTURE4);
                                    renderer.getColorBuffer(0)->unbind();
                                glActiveTexture(GL_TEXTURE3);
                                    renderer.getDepthBuffer()->unbind();
                                glActiveTexture(GL_TEXTURE2);
                                    skyBox.getBRDFLUT().unbind();
                                glActiveTexture(GL_TEXTURE1);
                                    skyBox.getPrefilter().unbind();
                                glActiveTexture(GL_TEXTURE0);
                                    skyBox.getIrradiance().unbind();
    
                            pbr->unbind();
                        }
                        /**
                         * Update the system
                         */
                        void update() override {
                            gBufferPass();
                            SSAOPass();
                            PBRPass();
                        }
                        /**
                         * Send light uniform to the PBR shader
                         */
                        void sendLight() {
                            unsigned char nb = 0;
                            auto pbr = Renderer::ProgramManager::get<Renderer::PBR>();
                            Utility::Singleton<EntityManager>::get().each<Light>([this, &nb, &pbr](Entity, Light& l) {
                                Utility::String base("lights[");
                                base << nb;
                                pbr->use3FV(base + "].position", 1, l.position.value());
                                pbr->use3FV(base + "].intensities", 1, l.intensities.value());
                                nb++;
                            });
                            pbr->use1I("numLights", static_cast <int> (nb));
                        }
            };
        }
    }
