
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
    using namespace NRE::GL;
    using namespace NRE::World;
    using namespace std::chrono_literals;

    class DevApplication : public Application {
        public :    // Static
            static constexpr int SIMULTANEOUS_W = 1;
            static constexpr int SIMULTANEOUS_H = 1;

            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;

            static constexpr int VIEWPORT_W = SCREEN_W / SIMULTANEOUS_W;
            static constexpr int VIEWPORT_H = SCREEN_H / SIMULTANEOUS_H;

        private :   // Field
            VAO* vaos;
            IBO<PrimitiveVertex>* ibos;
            PerspectiveCamera camera;

            World::World world;

            bool wireframeMode;
            bool linear;

            Angle fov;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vaos(new VAO[SIMULTANEOUS_H * SIMULTANEOUS_W]), ibos(new IBO<PrimitiveVertex>[SIMULTANEOUS_H * SIMULTANEOUS_W]{GL_STATIC_DRAW}), camera(50.0f, 70.0_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), wireframeMode(false), linear(true), fov(70.0_deg) {
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
                        } else if (event.isCode(KeyCode::L)) {
                            linear = !linear;
                            updateChunks();
                            return true;
                        }
                        return false;
                    });

                    addHandler<WheelMotionEvent>([&](WheelMotionEvent& event) {
                        fov += (event.getDelta() * degree);
                        if (fov < 1.0_deg) {
                            fov = 1.0_deg;
                        }
                        if (fov >= 80_deg) {
                            fov = 80.0_deg;
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
                }
                void render() override {
                    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    Primitive3D* shader = ProgramManager::get<Primitive3D>();
                    shader->bind();
                        shader->sendCamera(camera);
                        std::size_t index = 0;
                        for (int i = 0; i < SIMULTANEOUS_H; i++) {
                            for (int j = 0; j < SIMULTANEOUS_W; j++) {
                                auto& ibo = ibos[index];
                                auto& vao = vaos[index++];
                                glViewport(j * VIEWPORT_W, i * VIEWPORT_H, VIEWPORT_W, VIEWPORT_H);
                                vao.bind();
                                    ibo.draw();
                                vao.unbind();
                            }
                        }
                    shader->unbind();
                }
                void destroy() override {
                    delete[] ibos;
                    delete[] vaos;
                }
                void updateChunks() {
                    Clock clock;
                    clock.update();
                    std::size_t index = 0;
                    for (int i = 0; i < SIMULTANEOUS_H; i++) {
                        for (int j = 0; j < SIMULTANEOUS_W; j++) {
                            auto& ibo = ibos[index];
                            auto& vao = vaos[index];

                            for (Chunk& c : world) {
                                ChunkPolygonizer::polygonize(c, ibo, 0.0f, ChunkPolygonizer::LEVELS[index], linear);
                            }

                            std::cout << "Chunks update :" << std::endl;
                            std::cout << "\tResolution : " << ChunkPolygonizer::LEVELS[index] << std::endl;
                            std::cout << "\tVertex count : " << ibo.getDataCount() << std::endl;
                            std::cout << "\tIndex count : " << ibo.getIndexCount() << std::endl;
                            index++;

                            ibo.allocateAndFill();
                            vao.access(&ibo);
                        }
                    }
                    clock.update();
                    std::cout << "Time taken for update : " << clock.getDelta() << std::endl;
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
