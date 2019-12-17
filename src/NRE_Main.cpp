
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
            PerspectiveCamera camera;

            World::World world;
            Vector<ChunkMesh> meshes;
            
            InstancedModel spheres;
            
            Texture2D* texture;

            bool wireframeMode;

            Angle fov;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(50.0f, 70.0_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), wireframeMode(false), fov(70.0_deg) {
                    updateChunks();

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
                        fov += (event.getDelta() * degree);
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
                    
                    texture = new Texture2D("Data/Material/Mat_17/x1024/Normal.png", true);
                }
                void update() override {
                    camera.update();
                }
                void render() override {
                    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    Primitive3D* shader = ProgramManager::get<Primitive3D>();
                    shader->bind();
                        shader->sendCamera(camera);
                        texture->bind();
                        for (auto const& m : meshes) {
                            m.draw();
                        }
                        texture->unbind();
                    shader->unbind();
                    InstancedPrimitive3D* instancedShader = ProgramManager::get<InstancedPrimitive3D>();
                    instancedShader->bind();
                        instancedShader->sendCamera(camera);
                        texture->bind();
                            spheres.draw();
                        texture->unbind();
                    instancedShader->unbind();
                }
                void destroy() override {
                }
                
        private :   // Methods
                void updateChunks() {
                    Clock clock;
                    clock.update();
                    
                    meshes.reserve(World::World::NB_CHUNKS);
                    
                    for (Chunk& c : world) {
                        meshes.emplaceBack(c, camera.getFrustum());
                    }
                    std::unique_ptr<VBO<MatrixInstance>> vbo(new VBO<MatrixInstance>(GL_STREAM_DRAW));
                    vbo->allocate(10'000);

                    Sphere s(Vector3D<float>(0, 0, 0), 1);
                    std::unique_ptr<SphereMesh> mesh(new SphereMesh(s));
                    spheres.addMesh(std::move(mesh));
                    spheres.setModels(vbo);
                    for (Matrix4x4<float>& m : spheres.getMatrixes()) {
                        m.setIdentity();
                        m.translate(Vector3D<float>(std::rand() % 1000, std::rand() % 1000, 100 + std::rand() % 1000));
                        m.transpose();
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
