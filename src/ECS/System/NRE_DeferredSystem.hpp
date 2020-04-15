
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
    #include "../../Header/NRE_GLUtils.hpp"
    #include "../../Header/NRE_Renderer.hpp"
    #include "../../Header/NRE_Physics.hpp"
    
    #include "NRE_GBufferSystem.hpp"
    #include "NRE_ShadowSystem.hpp"

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
                    Renderer::DeferredRenderer renderer;       /**< The deferred renderer object */
                    Camera::Camera const& camera;              /**< The application's camera */
                    Camera::OrthographicCamera light;          /**< The light's camera */
                    NRE::Model::RectangleMesh screen;               /**< The screen mesh */
                    Renderer::SSAO ssao;                       /**< The ssao object */
                    GL::SkyBox skyBox;                         /**< The skybox */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the deferred system
                         * @param c          the application's camera
                         * @param screenSize the window screen size
                         * @param mapPath    the application's skybox
                         */
                        DeferredSystem(Camera::Camera const& c, Math::Vector2D<unsigned int> const& screenSize, IO::File const& mapPath) : renderer(screenSize), camera(c), light(0, Math::Vector3D<float>(-64, 0, 0), Math::Vector2D<float>(256), Math::Vector2D<float>(0.1, 300.0f), 0 * Math::degree, -20 * Math::degree), screen(Physics::Rectangle(Math::Point2D<float>(-1, -1), Math::Vector2D<float>(2, 2))), skyBox(mapPath) {
                            GL::setViewport(screenSize);
    
                            Utility::Singleton<SystemManager>::get().add<GBufferSystem>(camera);
                            Utility::Singleton<SystemManager>::get().add<ShadowSystem>();
                        }
                        
                    //## Methods ##//
                        /**
                         * Configure the system, called once before any rendering or update
                         */
                        void configure() override {
                            using namespace Renderer;
                            
                            Math::Matrix4x4<float> invProjection = camera.getProjection();
                            invProjection.inverse();
                            
                            auto pbr = ProgramManager::get<PBR>();
                            auto ssaoEffect = ProgramManager::get<SSAOEffect>();
                            auto terrain = ProgramManager::get<Renderer::Terrain>();
                            auto model = ProgramManager::get<Renderer::Model>();
    
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
    
                            terrain->bind();
                                terrain->sendTexture();
                            terrain->unbind();
    
                            model->bind();
                                model->sendTexture();
                            model->unbind();
    
                            SystemManager::get<ShadowSystem>()->setLight(light);
                        }
                        /**
                         * Perform the GBuffer pass
                         */
                        void gBufferPass() {
                            using namespace Math;
                            using namespace Renderer;
                            using namespace GL;
                            
                            renderer.bind();
                                clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                setDrawTargets(GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2);
                                
                                auto shader = ProgramManager::get<Renderer::SkyBox>();

                                Matrix4x4<float> MVP = camera.getProjection() * Matrix4x4<float>(Matrix3x3<float>(camera.getView()));
                                setDepthFunction(GL_LEQUAL);
                                    shader->bind();
                                    shader->sendMVP(MVP);
                                        skyBox.getMap().bind();
                                            skyBox.getMesh().draw();
                                        skyBox.getMap().unbind();
                                    shader->unbind();
                                setDepthFunction(GL_LESS);

                                SystemManager::get<GBufferSystem>()->update();
                            renderer.unbind();
                        }
                        /**
                         * Perform the SSAO pass
                         */
                        void SSAOPass() {
                            using namespace Renderer;
                            using namespace GL;
                            
                            renderer.bind();
                                setDepthMask(false);
                                setColorMask(false, false, true, false);
                    
                                setDrawTargets(GL_COLOR_ATTACHMENT2);
                    
                                ProgramManager::get<SSAOEffect>()->bind();
                                    bindTexture(renderer.getDepthBuffer(),  0);
                                    bindTexture(renderer.getColorBuffer(1), 1);
                                    bindTexture(ssao.getNoise(), 2);
                        
                                    screen.draw();
                                    
                                    unbindTexture(ssao.getNoise(), 2);
                                    unbindTexture(renderer.getColorBuffer(1), 1);
                                    unbindTexture(renderer.getDepthBuffer(),  0);
                                ProgramManager::get<SSAOEffect>()->unbind();
    
                                setColorMask(true, true, true, true);
                                setDepthMask(true);
                            renderer.unbind();
                        }
                        /**
                         * Perform the Shadow pass
                         */
                        void shadowPass() {
                            light.update();
                            renderer.getShadowBuffer().bind();
                                GL::setViewport(Math::Vector2D<int>(512, 512));
                                GL::clear(GL_DEPTH_BUFFER_BIT);
                                glDisable(GL_CULL_FACE);
    
                                    SystemManager::get<ShadowSystem>()->update();
                                glEnable(GL_CULL_FACE);
                                GL::setViewport(renderer.getSize());
                            renderer.getShadowBuffer().unbind();
                        }
                        /**
                         * Perform the PBR pass
                         */
                        void PBRPass() {
                            using namespace Renderer;
                            using namespace Utility;
                            using namespace GL;
                            
                            clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                            auto pbr = ProgramManager::get<PBR>();
                            
                            pbr->bind();
                                pbr->sendCamera(camera);
                                pbr->sendLightSpace(light.getProjection() * light.getView());
                                sendLight();
                                
                                bindTexture(skyBox.getIrradiance(), 0);
                                bindTexture(skyBox.getPrefilter(), 1);
                                bindTexture(skyBox.getBRDFLUT(), 2);
                                bindTexture(renderer.getDepthBuffer(), 3);
                                bindTexture(renderer.getColorBuffer(0), 4);
                                bindTexture(renderer.getColorBuffer(1), 5);
                                bindTexture(renderer.getColorBuffer(2), 6);
                                bindTexture(renderer.getShadowMap(), 7);
                                
                                    screen.draw();
    
                                unbindTexture(renderer.getShadowMap(), 7);
                                unbindTexture(renderer.getColorBuffer(2), 6);
                                unbindTexture(renderer.getColorBuffer(1), 5);
                                unbindTexture(renderer.getColorBuffer(0), 4);
                                unbindTexture(renderer.getDepthBuffer(), 3);
                                unbindTexture(skyBox.getBRDFLUT(), 2);
                                unbindTexture(skyBox.getPrefilter(), 1);
                                unbindTexture(skyBox.getIrradiance(), 0);
    
                            pbr->unbind();
                        }
                        /**
                         * Update the system
                         */
                        void update() override {
                            gBufferPass();
                            SSAOPass();
                            //shadowPass();
                            PBRPass();
                        }
                        /**
                         * Send light uniform to the PBR shader
                         */
                        void sendLight() {
                            using namespace Renderer;
                            using namespace Utility;
                            
                            unsigned char nb = 0;
                            auto pbr = ProgramManager::get<PBR>();
                            Singleton<EntityManager>::get().each<Light>([this, &nb, &pbr](Entity, Light& l) {
                                String base("lights[");
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
