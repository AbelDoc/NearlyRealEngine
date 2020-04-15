
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
        
            Model::Model ship;
            World::World world;
            Vector<ChunkMesh*> chunks;
            Vector<WaterChunkMesh*> waters;
        
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(90.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 300.0f), Vector3D<float>(0, 0, 0)), ship("Data/Model/Ship/Ship.obj") {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                }

            //## Methods ##//
                void create() override {
                    NRE::System::System::get().setRelativeMode(true);
                    NRE::System::System::get().showCursor(false);
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
    
                    chunks.reserve(World::World::NB_CHUNKS);
                    waters.reserve(World::World::NB_CHUNKS);
                    for (WaterChunk& c : world) {
                        Entity r = Singleton<EntityManager>::get().create();
                        chunks.emplaceBack(new ChunkMesh(c.getParent(), camera.getFrustum()));
                        waters.emplaceBack(new WaterChunkMesh(c, camera.getFrustum()));
                        r.assign<ECS::Terrain>(chunks.getLast());
                        r.assign<ECS::Water>(waters.getLast());
                    }
                    
                    Entity l1 = Singleton<EntityManager>::get().create();
                    Entity l2 = Singleton<EntityManager>::get().create();
                    Entity l3 = Singleton<EntityManager>::get().create();
                    l1.assign<Light>(Vector3D<float>(-10, 10, 15), Vector3D<float>(10, 0, 0));
                    l2.assign<Light>(Vector3D<float>(-10, 10, 5), Vector3D<float>(0, 10, 0));
                    l3.assign<Light>(Vector3D<float>(-10, 10, 0), Vector3D<float>(200, 200, 200));
                    
                    Entity s = Singleton<EntityManager>::get().create();
                    s.assign<NRE::ECS::Model>(&ship);
                    s.getComponent<NRE::ECS::Model>()->model.translate(Vector3D<float>(-10, 5, 10));
                    s.getComponent<NRE::ECS::Model>()->model.rotate(90_deg, Vector3D<float>(0, 1, 0));
    
                    Singleton<SystemManager>::get().add<DeferredSystem>(camera, Vector2D<unsigned int>(SCREEN_W, SCREEN_H), "Data/SkyBox/Space_2K.hdr");
                    Singleton<SystemManager>::get().configure();
                }
                void update() override {
                    camera.update();
                }
                void render() override {
                    Singleton<SystemManager>::get().getSystem<DeferredSystem>()->update();
                }
                void destroy() override {
                    for (ChunkMesh* mesh : chunks) {
                        delete mesh;
                    }
                    for (WaterChunkMesh* mesh : waters) {
                        delete mesh;
                    }
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
