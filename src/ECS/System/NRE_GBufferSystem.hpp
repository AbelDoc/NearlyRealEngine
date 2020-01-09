
    /**
     * @file NRE_GBufferSystem.hpp
     * @brief Declaration of Engine's ECS's Object : GBufferSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_ECS.hpp>
    
     #include "../Component/Renderable/NRE_Renderable.hpp"
    
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

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the GBuffer system from the application's camera
                         * @param c the application's camera
                         */
                        GBufferSystem(Camera::Camera const& c) : camera(c) {
                        }

                    //## Methods ##//
                        /**
                         * Update the system
                         */
                        void update() override {
                            Renderer::GBuffer* shader = Renderer::ProgramManager::get<Renderer::GBuffer>();
                            shader->bind();
                                Utility::Singleton<Renderer::MaterialManager>::get().getNormals().bind();
                                    Math::Matrix4x4<float> PV = camera.getProjection()  * camera.getView();
                                    Renderer::ProgramManager::get<Renderer::GBuffer>()->sendMatrix(PV);
                                    Utility::Singleton<EntityManager>::get().each<Renderable>([this](Entity, Renderable& r) {
                                        if (r.model->canBeDrawn()) {
                                            r.model->draw();
                                        }
                                    });
                                Utility::Singleton<Renderer::MaterialManager>::get().getNormals().unbind();
                            shader->unbind();
                        }

            };
        }
    }
