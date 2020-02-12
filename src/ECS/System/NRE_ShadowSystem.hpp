
    /**
     * @file NRE_ShadowSystem.hpp
     * @brief Declaration of Engine's ECS's Object : ShadowSystem
     * @author Louis ABEL
     * @date 30/10/2018
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
             * @class ShadowSystem
             * @brief Manage rendering with a shadow shader
             */
            class ShadowSystem : public System<ShadowSystem> {
                private:    //Fields
                    Camera::Camera* lightCamera;   /**< The shadow's camera */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ShadowSystem() = default;

                    //## Methods ##//
                        /**
                         * Shadow's camera setter
                         * @param l the new shadow's camera
                         */
                        void setLight(Camera::Camera& l) {
                            lightCamera = &l;
                        }
                        /**
                         * Update the system
                         */
                        void update() override {
                            using namespace Renderer;
                            using namespace Utility;
    
                            auto shader = ProgramManager::get<Shadow>();
                            shader->bind();
                                shader->sendMatrix(lightCamera->getProjection() * lightCamera->getView());
                                Singleton<EntityManager>::get().each<Renderable>([this](Entity, Renderable& r) {
                                    r.model->draw();
                                });
                            shader->unbind();
                        }

            };
        }
    }