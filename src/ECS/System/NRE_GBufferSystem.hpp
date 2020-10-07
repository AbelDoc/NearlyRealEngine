
    /**
     * @file NRE_GBufferSystem.hpp
     * @brief Declaration of Engine's ECS's Object : GBufferSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_ECS.hpp>
    
     #include "../Component/Renderable/NRE_VoxelRenderable.hpp"
     #include "../Component/Renderable/NRE_ModelRenderable.hpp"
    
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
                            using namespace Core;
                            using namespace GL;
                            time += Time::Clock::TIMESTEP;
    
                            auto voxel = ProgramManager::get<VoxelShader>();
                            auto model = ProgramManager::get<ModelShader>();
    
                            voxel->bind();
                                voxel->sendView(camera.getView());
                                Singleton<EntityManager>::get().each<VoxelRenderable>([this](Entity, VoxelRenderable& t) {
                                    if (t.mesh.canBeDrawn()) {
                                        t.mesh.draw();
                                    }
                                });
                            voxel->unbind();
                            model->bind();
                                model->sendView(camera.getView());
                                Singleton<EntityManager>::get().each<ModelRenderable>([this, &model](Entity, ModelRenderable& m) {
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
