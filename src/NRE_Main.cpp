
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
    using namespace NRE::Data;
    
    class DevApplication : public Application {
        public :    // Static
            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;
            
        private :   // Field
            PerspectiveCamera camera;
        
            Model::Model ship;
            float shipSpeed;
            
            Angle yaw;
            Angle pitch;
            Angle roll;
            Point3D<float> position;
            Vector3D<float> forward;
            Vector3D<float> right;
            Vector3D<float> up;
            
            Matrix4x4<float>* shipModel;
            
            World::World world;
            Vector<ChunkModel> chunks;
            
            bool attach;
        
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(10.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 300.0f), Vector3D<float>(0, 0, 0)), ship("Data/Model/Ship/Ship.obj"), shipSpeed(10.0f), yaw(0_deg), pitch(0_deg), roll(0_deg), position(-10, 5, 10), attach(true) {
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
                            if (attach) {
                                position += camera.getForward() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveFront();
                            }
                        } else if (event.isCode(KeyCode::S)) {
                            if (!attach) {
                                camera.moveBack();
                            }
                        } else if (event.isCode(KeyCode::Q)) {
                            if (attach) {
                                yaw -= shipSpeed * Time::Clock::TIMESTEP * Math::degree;
                            } else {
                                camera.moveLeft();
                            }
                        } else if (event.isCode(KeyCode::D)) {
                            if (attach) {
                                yaw += shipSpeed * Time::Clock::TIMESTEP * Math::degree;
                            } else {
                                camera.moveRight();
                            }
                        } else if (event.isCode(KeyCode::LEFT_SHIFT)) {
                            if (attach) {
                                position -= camera.getUp() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveDown();
                            }
                        } else if (event.isCode(KeyCode::SPACE)) {
                            if (attach) {
                                position += camera.getUp() * shipSpeed * Time::Clock::TIMESTEP;
                            } else {
                                camera.moveUp();
                            }
                        } else if (event.isCode(KeyCode::T)) {
                            attach = !attach;
                            return true;
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        if (attach) {
                            roll  += static_cast <float> (event.getMotion().getX()) * Math::degree * 0.1f;
                            pitch -= static_cast <float> (event.getMotion().getY()) * Math::degree * 0.1f;
                        } else {
                            camera.turn(event.getMotion());
                        }
                        return true;
                    });
    
                    chunks.reserve(World::World::NB_CHUNKS);
                    for (Chunk const& c : world) {
                        Entity r = Singleton<EntityManager>::get().create();
                        chunks.emplaceBack(&c);
                        auto& terrain = chunks.getLast().get<ChunkMesh>(0);
                        auto& water = chunks.getLast().get<ChunkMesh>(1);
                        terrain.setBoundObject(&camera.getFrustum());
                        water.setBoundObject(&camera.getFrustum());
                        r.assign<ECS::Terrain>(terrain);
                        r.assign<ECS::Water>(water);
                    }
                    
                    Entity l = Singleton<EntityManager>::get().create();
                    l.assign<Light>(Vector3D<float>(-10, 10, 0), Vector3D<float>(200, 200, 200));
                    
                    Entity s = Singleton<EntityManager>::get().create();
                    s.assign<NRE::ECS::Model>(&ship);
                    shipModel = &s.getComponent<NRE::ECS::Model>()->model;
    
                    Singleton<SystemManager>::get().add<DeferredSystem>(camera, Vector2D<unsigned int>(SCREEN_W, SCREEN_H), "Data/SkyBox/Space_2K.hdr");
                    Singleton<SystemManager>::get().configure();
                }
                void update() override {
                    if (attach) {
                        float tmp = static_cast <float> (cos(pitch));
                        forward.setX(tmp * static_cast <float> (cos(yaw)));
                        forward.setY(      static_cast <float> (sin(pitch)));
                        forward.setZ(tmp * static_cast <float> (sin(yaw)));
                        forward.normalize();
    
                        right = forward ^ Vector3D<float>(0, 1, 0);
                        right.normalize();
    
                        up = right ^ forward;
                        
                        camera.setEye(position - 20 * forward + 5 * up);
                        camera.setPitch(pitch);
                        camera.setYaw(yaw);
                        camera.update();
                        shipModel->setIdentity();
                        shipModel->translate(position);
                        shipModel->rotate(roll, forward);
                    } else {
                        camera.update();
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
