
    /**
     * @file NRE_Main.cpp
     * @brief Test of NearlyRealEngine
     * @author Louis ABEL
     * @date 06/04/2019
     * @copyright CC-BY-NC-SA
     */

    #include "Header/NRE_Core.hpp"
    
    using namespace NRE;
    using namespace NRE::System;
    using namespace NRE::Math;
    using namespace NRE::Event;
    using namespace NRE::Time;
    using namespace NRE::Renderer;
    using namespace NRE::Graphics;
    using namespace NRE::Camera;
    using namespace NRE::Utility;
    using namespace NRE::Model;
    using namespace NRE::GL;
    using namespace NRE::ECS;
    using namespace NRE::Physics;
    using namespace NRE::IO;
    using namespace NRE::World;
    
    class DevApplication : public Application {
        public :    // Static
            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;
            
        private :   // Field
            PerspectiveCamera camera;
        
            World::World world;
            Vector<Model::Model> models;
            Vector<Model::Model> waters;
            
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(90.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 300.0f), Vector3D<float>(-100, 20, 0)) {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                }

            //## Methods ##//
                void create() override {
                    NRE::System::System::get().setRelativeMode(true);
                    addHandler<KeyEvent>([&](KeyEvent& event) {
                        if (event.isCode(KeyCode::Z)) {
                            camera.moveFront();
                        } else if (event.isCode(KeyCode::S)) {
                            camera.moveBack();
                        } else if (event.isCode(KeyCode::Q)) {
                            camera.moveLeft();
                        } else if (event.isCode(KeyCode::D)) {
                            camera.moveRight();
                        } else if (event.isCode(KeyCode::LEFT_SHIFT)) {
                            camera.moveDown();
                        } else if (event.isCode(KeyCode::SPACE)) {
                            camera.moveUp();
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
    
                    models.reserve(World::World::NB_CHUNKS);
                    waters.reserve(World::World::NB_CHUNKS);
                    for (WaterChunk& c : world) {
                        Entity r = Singleton<EntityManager>::get().create();
                        models.emplaceBack();
                        waters.emplaceBack();
                        models.getLast().reserve(1);
                        waters.getLast().reserve(1);
                        models.getLast().addMesh(new ChunkMesh(c.getParent(), camera.getFrustum()));
                        waters.getLast().addMesh(new WaterChunkMesh(c, camera.getFrustum()));
                        r.assign<Renderable>(&models.getLast());
                        r.assign<WaterSurface>(&waters.getLast());
                    }
                    
                    Entity l = Singleton<EntityManager>::get().create();
                    l.assign<Light>(Vector3D<float>(-100, 20, 10), Vector3D<float>(0.9, 0.8, 0.6));
                    
    
                    Singleton<SystemManager>::get().add<DebugDeferredSystem>(camera, Vector2D<unsigned int>(SCREEN_W, SCREEN_H), "Data/SkyBox/Space_2K.hdr");
    
                    Singleton<SystemManager>::get().configure();
                }
                void update() override {
                    camera.update();
                }
                void render() override {
                    Singleton<SystemManager>::get().getSystem<DebugDeferredSystem>()->update();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
