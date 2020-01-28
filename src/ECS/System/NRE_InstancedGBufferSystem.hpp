
    /**
     * @file NRE_GBufferSystem.hpp
     * @brief Declaration of Engine's ECS's Object : InstancedGBufferSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_ECS.hpp>
    
     #include "../Component/Renderable/NRE_InstancedRenderable.hpp"
    
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
             * @class InstancedGBufferSystem
             * @brief Manage instanced rendering with a gbuffer shader
             */
            class InstancedGBufferSystem : public System<InstancedGBufferSystem> {
                private:    //Fields
                    Camera::Camera const& camera;

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        InstancedGBufferSystem() = delete;
                        /**
                         * Construct the Instanced GBuffer system from the application's camera
                         * @param c the application's camera
                         */
                        InstancedGBufferSystem(Camera::Camera const& c) : camera(c) {
                        }

                    //## Methods ##//
                        /**
                         * Update the system
                         */
                        void update() override {
                            using namespace Renderer;
                            using namespace Utility;
                            
                            auto shader = ProgramManager::get<InstancedGBuffer>();
                            shader->bind();
                                shader->sendMatrix(camera.getProjection() * camera.getView());
                                Singleton<EntityManager>::get().each<InstancedRenderable>([this](Entity, InstancedRenderable& r) {
                                    if (r.model->canBeDrawn()) {
                                        r.model->draw();
                                    }
                                });
                            shader->unbind();
                        }

            };
        }
    }
