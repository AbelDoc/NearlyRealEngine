
    /**
     * @file NRE_DebugDeferredSystem.hpp
     * @brief Declaration of Engine's ECS's Object : DebugDebugDeferredSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <Header/NRE_ECS.hpp>
    
    #include "../../Header/NRE_Shader.hpp"
    #include "../../Header/NRE_GLUtils.hpp"
    #include "../../Header/NRE_Renderer.hpp"
    
    #include "NRE_FlockSystem.hpp"
    #include "NRE_GBufferSystem.hpp"
    #include "NRE_WaterSystem.hpp"
    #include "NRE_InstancedGBufferSystem.hpp"
    #include "NRE_ShadowSystem.hpp"
    #include "NRE_InstancedShadowSystem.hpp"

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
             * @class DebugDeferredSystem
             * @brief Manage debug deferred rendering
             */
            class DebugDeferredSystem : public System<DebugDeferredSystem> {
                private:    //Fields
                    Renderer::DeferredRenderer renderer;       /**< The deferred renderer object */
                    Camera::Camera const& camera;              /**< The application's camera */
                    Model::RectangleMesh screen;               /**< The screen mesh */
                    GL::SkyBox skyBox;                         /**< The skybox */

            public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the deferred system
                         * @param c          the application's camera
                         * @param screenSize the window screen size
                         * @param mapPath    the application's skybox
                         */
                        DebugDeferredSystem(Camera::Camera const& c, Math::Vector2D<unsigned int> const& screenSize, IO::File const& mapPath) : renderer(screenSize), camera(c), screen(Physics::Rectangle(Math::Point2D<float>(-1, -1), Math::Vector2D<float>(2, 2))), skyBox(mapPath) {
                            GL::setViewport(screenSize);
    
                            Utility::Singleton<SystemManager>::get().add<WaterSystem>(camera);
                            Utility::Singleton<SystemManager>::get().add<GBufferSystem>(camera);
                            Utility::Singleton<SystemManager>::get().add<InstancedGBufferSystem>(camera);
                        }
                        
                    //## Methods ##//
                        /**
                         * Configure the system, called once before any rendering or update
                         */
                        void configure() override {
                            using namespace Renderer;
                            
                            Math::Matrix4x4<float> invProjection = camera.getProjection();
                            invProjection.inverse();
                            
                            auto phong = ProgramManager::get<Phong>();
    
                            phong->bind();
                                phong->sendTexture();
                                phong->sendInvProjection(invProjection);
                            phong->unbind();
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
                                SystemManager::get<InstancedGBufferSystem>()->update();
                                SystemManager::get<WaterSystem>()->update();
                            renderer.unbind();
                        }
                        /**
                         * Perform the Phong pass
                         */
                        void renderPass() {
                            using namespace Renderer;
                            using namespace Utility;
                            using namespace GL;
                            
                            clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                            auto phong = ProgramManager::get<Phong>();
    
                            phong->bind();
                                phong->sendCamera(camera);
                                sendLight();
                                
                                bindTexture(renderer.getDepthBuffer(), 0);
                                bindTexture(renderer.getColorBuffer(0), 1);
                                bindTexture(renderer.getColorBuffer(1), 2);
                                bindTexture(renderer.getColorBuffer(2), 3);
                                bindTexture(Singleton<MaterialManager>::get().getAlbedos(), 4);
                                
                                    screen.draw();
    
                                unbindTexture(Singleton<MaterialManager>::get().getAlbedos(), 4);
                                unbindTexture(renderer.getColorBuffer(2), 3);
                                unbindTexture(renderer.getColorBuffer(1), 2);
                                unbindTexture(renderer.getColorBuffer(0), 1);
                                unbindTexture(renderer.getDepthBuffer(), 0);
    
                            phong->unbind();
                        }
                        /**
                         * Update the system
                         */
                        void update() override {
                            gBufferPass();
                            renderPass();
                        }
                        /**
                         * Send light uniform to the Phong shader
                         */
                        void sendLight() {
                            using namespace Renderer;
                            using namespace Utility;
                            
                            unsigned char nb = 0;
                            auto phong = ProgramManager::get<Phong>();
                            Singleton<EntityManager>::get().each<Light>([this, &nb, &phong](Entity, Light& l) {
                                String base("lights[");
                                base << nb;
                                phong->use3FV(base + "].position", 1, l.position.value());
                                phong->use3FV(base + "].intensities", 1, l.intensities.value());
                                nb++;
                            });
                            phong->use1I("numLights", static_cast <int> (nb));
                        }
            };
        }
    }
