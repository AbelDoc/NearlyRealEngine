
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
    using namespace NRE::Physics;
    using namespace NRE::IO;
    using namespace NRE::World;
    using namespace std::chrono_literals;

    class DevApplication : public Application {
        public :    // Static
            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;

        private :   // Field
            Angle fov;
            PerspectiveCamera camera;
            InstancedModel<ColoredMatrixInstance> spheres;

            bool wireframeMode;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), fov(70_deg), camera(50.0f, fov, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), spheres(10'000, GL_STREAM_DRAW), wireframeMode(false) {
                    updateData();

                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                }

            //## Methods ##//
                void create() override {
                    Singleton<System::System>::get().setRelativeMode(true);
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
                        } else if (event.isCode(KeyCode::P)) {
                            wireframeMode = !wireframeMode;
                            if (wireframeMode) {
                                polygonMode(GL_FRONT, GL_LINE);
                            } else {
                                polygonMode(GL_FRONT, GL_FILL);
                            }
                            return true;
                        }
                        return false;
                    });

                    addHandler<WheelMotionEvent>([&](WheelMotionEvent& event) {
                        fov -= (event.getDelta() * degree);
                        if (fov < 1.0_deg) {
                            fov = 1.0_deg;
                        }
                        if (fov >= 89.9_deg) {
                            fov = 89.9_deg;
                        }
                        camera.setFov(fov);
                        return true;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
                }
                void update() override {
                    camera.update();
                    for (ColoredMatrixInstance& m : spheres) {
                        float dist = static_cast <float> (m.color.norm());
                        Vector4D<float> c4 = m.matrix.getL4();
                        c4.setY(c4.getY() - dist);
                        if (c4.getY() < 0) {
                            c4.setY(400);
                        }
                        m.matrix.setL4(c4);
                    }
                    spheres.update();
                }
                void render() override {
                    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    InstancedPrimitive3D* instancedShader = ProgramManager::get<InstancedPrimitive3D>();
                    instancedShader->bind();
                        instancedShader->sendCamera(camera);
                        spheres.draw();
                    instancedShader->unbind();
                }
                void destroy() override {
                }
                
        private :   // Methods
                void updateData() {
                    Clock clock;
                    clock.update();
                    
                    Sphere s(Vector3D<float>(0, 0, 0), 1);
                    spheres.addMesh(std::unique_ptr<SphereMesh>(new SphereMesh(s)));
                    
                    for (ColoredMatrixInstance& m : spheres) {
                        m.color = Vector4D<float>(static_cast <float> (std::rand() % 1000) / 1000, static_cast <float> (std::rand() % 1000) / 1000, static_cast <float> (std::rand() % 1000) / 1000, 1);
                        m.matrix.setIdentity();
                        m.matrix.translate(Vector3D<float>(-200 + std::rand() % 400, std::rand() % 400, -200 + std::rand() % 400));
                        m.matrix.transpose();
                    }
                    spheres.update();
    
                    clock.update();
                    std::cout << "Time taken for update : " << clock.getDelta() << std::endl;
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
