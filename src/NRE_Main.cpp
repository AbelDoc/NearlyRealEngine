
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
            float shipSpeed;
            Angle shipRoll;
            Vector3D<float> shipPosition;
            Matrix4x4<float>* shipModel;
            
            World::World world;
            Vector<ChunkModel> chunks;
            
            bool attach;
        
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(90.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 300.0f), Vector3D<float>(0, 0, 0)), ship("Data/Model/Ship/Ship.obj"), shipSpeed(10.0f), shipRoll(0_deg), shipPosition(-10, 5, 10), attach(true) {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
                    /*glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);*/
                }

            //## Methods ##//
                void create() override {
                    NRE::System::System::get().setRelativeMode(true);
                    NRE::System::System::get().showCursor(false);
                    addHandler<KeyEvent>([&](KeyEvent& event) {
                        if (event.isCode(KeyCode::Z)) {
                            if (attach) {
                                shipPosition += camera.getForward() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveFront();
                            }
                        } else if (event.isCode(KeyCode::S)) {
                            if (attach) {
                                shipPosition -= camera.getForward() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveBack();
                            }
                        } else if (event.isCode(KeyCode::Q)) {
                            if (attach) {
                                shipPosition -= camera.getRight() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveLeft();
                            }
                        } else if (event.isCode(KeyCode::D)) {
                            if (attach) {
                                shipPosition += camera.getRight() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveRight();
                            }
                        } else if (event.isCode(KeyCode::LEFT_SHIFT)) {
                            if (attach) {
                                shipPosition -= camera.getUp() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveDown();
                            }
                        } else if (event.isCode(KeyCode::SPACE)) {
                            if (attach) {
                                shipPosition += camera.getUp() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveUp();
                            }
                        } else if (event.isCode(KeyCode::A)) {
                            if (attach) {
                                shipRoll -= 5.0f * Math::degree;
                            }
                        } else if (event.isCode(KeyCode::E)) {
                            if (attach) {
                                shipRoll += 5.0f * Math::degree;
                            }
                        } else if (event.isCode(KeyCode::T)) {
                            attach = !attach;
                            return true;
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
    
                    chunks.reserve(World::World::NB_CHUNKS);
                    for (Chunk& c : world) {
                        Entity r = Singleton<EntityManager>::get().create();
                        chunks.emplaceBack(c, &camera.getFrustum());
                        r.assign<ECS::Terrain>(chunks.getLast().get(0));
                        r.assign<ECS::Water>(chunks.getLast().get(1));
                    }
                    
                    Entity l1 = Singleton<EntityManager>::get().create();
                    Entity l2 = Singleton<EntityManager>::get().create();
                    Entity l3 = Singleton<EntityManager>::get().create();
                    l3.assign<Light>(Vector3D<float>(-10, 10, 0), Vector3D<float>(200, 200, 200));
                    
                    Entity s = Singleton<EntityManager>::get().create();
                    s.assign<NRE::ECS::Model>(&ship);
                    shipModel = &s.getComponent<NRE::ECS::Model>()->model;
    
                    Singleton<SystemManager>::get().add<DeferredSystem>(camera, Vector2D<unsigned int>(SCREEN_W, SCREEN_H), "Data/SkyBox/Space_2K.hdr");
                    Singleton<SystemManager>::get().configure();
                }
                void update() override {
                    camera.update();
                    if (attach) {
                        camera.setEye(shipPosition - 20 * camera.getForward() + 5 * camera.getUp());
                        shipModel->setIdentity();
                        shipModel->translate(shipPosition);
                        shipModel->rotate(camera.getYaw(), Vector3D<float>(0, -1, 0));
                        shipModel->rotate(camera.getPitch(), Vector3D<float>(0, 0, 1));
                        shipModel->rotate(shipRoll, Vector3D<float>(1, 0, 0));
                    }
                }
                void render() override {
                    Singleton<SystemManager>::get().getSystem<DeferredSystem>()->update();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
