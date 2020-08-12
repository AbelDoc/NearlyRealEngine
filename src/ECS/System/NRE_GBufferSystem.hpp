
    /**
     * @file NRE_GBufferSystem.hpp
     * @brief Declaration of Engine's ECS's Object : GBufferSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_ECS.hpp>
    
     #include "../Component/Renderable/NRE_Terrain.hpp"
     #include "../Component/Renderable/NRE_Water.hpp"
     #include "../Component/Renderable/NRE_Model.hpp"
    
     #include "../../Header/NRE_Shader.hpp"
     #include "../../Header/NRE_Renderer.hpp"

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
             * @class GBufferSystem
             * @brief Manage rendering with a gbuffer shader
             */
            class GBufferSystem : public System<GBufferSystem> {
                private:    //Fields
                    Camera::Camera const& camera;
                    float time;

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the GBuffer system from the application's camera
                         * @param c the application's camera
                         */
                        GBufferSystem(Camera::Camera const& c) : camera(c), time(0) {
                        }

                    //## Methods ##//
                        /**
                         * Update the system
                         */
                        void update() override {
                            using namespace Renderer;
                            using namespace Utility;
                            using namespace GL;
                            time += Time::Clock::TIMESTEP;
    
                            auto terrain = ProgramManager::get<Renderer::Terrain>();
                            auto water = ProgramManager::get<Renderer::Water>();
                            auto model = ProgramManager::get<Renderer::Model>();
                            
                            terrain->bind();
                                terrain->sendView(camera.getView());
                                Singleton<EntityManager>::get().each<ECS::Terrain>([this](Entity, ECS::Terrain& t) {
                                    if (t.mesh.canBeDrawn()) {
                                        t.mesh.draw();
                                    }
                                });
                            terrain->unbind();
                            water->bind();
                                water->sendView(camera.getView());
                                water->sendTime(time);
                                Singleton<EntityManager>::get().each<ECS::Water>([this](Entity, ECS::Water& w) {
                                    if (w.mesh.canBeDrawn()) {
                                        w.mesh.draw();
                                    }
                                });
                            water->unbind();
                            model->bind();
                                model->sendView(camera.getView());
                                Singleton<EntityManager>::get().each<ECS::Model>([this, &model](Entity, ECS::Model& m) {
                                    if (m.mesh->canBeDrawn()) {
                                        model->sendModel(m.model);
                                        m.mesh->draw();
                                    }
                                });
                            model->unbind();
                        }

            };
        }
    }
