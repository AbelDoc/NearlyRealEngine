
    /**
     * @file NRE_GBufferSystem.hpp
     * @brief Declaration of Engine's ECS's Object : GBufferSystem
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_ECS.hpp>
    
     #include "../Component/Renderable/NRE_WaterSurface.hpp"
    
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
             * @class WaterSystem
             * @brief Manage rendering with a water shader
             */
            class WaterSystem : public System<WaterSystem> {
                private:    //Fields
                    Camera::Camera const& camera;
                    float time;

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the Water system from the application's camera
                         * @param c the application's camera
                         */
                        WaterSystem(Camera::Camera const& c) : camera(c), time(0) {
                        }

                    //## Methods ##//
                        /**
                         * Update the system
                         */
                        void update() override {
                            using namespace Renderer;
                            using namespace Utility;
                            time += Time::Clock::TIMESTEP;
                            
                            auto shader = ProgramManager::get<Water>();
                            shader->bind();
                                shader->sendMatrix(camera.getProjection()  * camera.getView());
                                shader->sendTime(time);
                                Singleton<EntityManager>::get().each<WaterSurface>([this](Entity, WaterSurface& r) {
                                    if (r.model->canBeDrawn()) {
                                        r.model->draw();
                                    }
                                });
                            shader->unbind();
                        }

            };
        }
    }
