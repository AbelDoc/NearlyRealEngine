
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
        private :   // Field
            VAO vao;
            VBO<PrimitiveVertex> vbo;
            PerspectiveCamera camera;

            bool wireframeMode;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vbo(GL_STATIC_DRAW), camera(50.0f, 70.0f, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), wireframeMode(false) {

                    int shift = 0;
                    for (float i = 0.125f; i <= 4; i *= 2) {
                        Chunk chunk({static_cast <int> (Chunk::SIZE_X) * shift++, 0, 0});
                        ChunkFactory::createSphere(chunk, i, 6.5f);
                        ChunkPolygonizer::polygonize(chunk, vbo);
                    }

                    std::cout << "Vertex size : " << vbo.getDataCount() << std::endl;

                    vbo.allocateAndFill();
                    vao.access(&vbo);

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
                        } else if (event.isCode(KeyCode::R)) {
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
                        shader->sendMVP(static_cast <PerspectiveCamera const&> (camera).getProjection() * camera.getView());
                        vao.bind();
                            vbo.draw();
                        vao.unbind();
                    shader->unbind();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
